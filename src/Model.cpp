#include "Model.h"
#include "AnalysisConstraints.h"
#include "RobustDesign.h"

using namespace std;
using namespace AnalysisGenerator;

Model::Model() {};

Model::Model(std::shared_ptr<Generator>& generator) : generator_(generator) 
{
	auto temp = generator_->getBlock();
	setBlock(temp);
	return;
}

void Model::setGenerator(std::shared_ptr<Generator>& generator)
{
	generator_ = generator;
	auto temp = generator_->getBlock();
	setBlock(temp);
	return;
}

void Model::setBlock(std::shared_ptr<AnalysisParametersBlock>& block)
{
	block_ = block;
	return;
}

void Model::run()
{
	generator_->generate();
	auto mat = generator_->getMatrix();

	if (robustDesign_)
	{
		auto objs = block_->getObjectives();
		for_each(objs.begin(), objs.end(), [&](const shared_ptr<AnalysisObjective>&curr)
		{
			block_->addObjective(string("mean_").append(curr->name()), curr->dir());
			block_->addObjective(string("stdvar_").append(curr->name()), AnalysisObjective::ObjDir::MIN_);
		});
	}

	block_->addSamples(mat);
	auto dim = block_->getNumSamples();

	for (int i = 0; i < (int)dim; ++i)
	{
		cout << "Starting evaluation of solution " << i + 1 << " of " << dim << endl;
		auto ret = objf_(block_, i);

		if (robustDesign_)
		{
			vector<double> variances;
			auto params=block_->getParameters();
			variances.reserve(params.size());
			for_each(params.begin(), params.end(), [&](const shared_ptr<AnalysisParameter>& curr)
			{
				if (curr->varType() == AnalysisParameter::ABSOLUTE_)
					variances.push_back(curr->variance());
				else if (curr->varType() == AnalysisParameter::PERCENTAGE_)
					variances.push_back(curr->variance() * block_->getValue(curr->name(), i) / 100);
			});

			RobustDesignGenerator rdg(block_->getSample(i)->getValues(),variances,numSamples_);
			rdg.generate();
			auto rdgMatrix = rdg.getMatrix();
			auto tempBlock = block_->clone();
			vector<vector<double>> objs;
			objs.resize(tempBlock->getObjectives().size());

			for_each(objs.begin(), objs.end(), [&](vector<double>& curr) 
			{
				curr.resize(numSamples_+1);
			});

			tempBlock->addSamples(rdgMatrix);
			auto allBasicObjs = block_->getSampleObjectives(i);
			for (int k = 0; k < (int)objs.size()/3; ++k)
				objs[k][0] = allBasicObjs->getValues()[k];

			for (int j = 1; j <= numSamples_; ++j)
			{
				auto ret = objf_(tempBlock, j);

				if (ret)
				{
					auto allObjs = tempBlock->getSampleObjectives(j);

					for (int k = 0; k < (int)objs.size() / 3; ++k)
						objs[k][j] = allObjs->getValues()[k];
				}
			}

			int pos = (int)objs.size() / 3;
			for (int k = 0; k < pos; ++k)
			{
				auto currName = tempBlock->getObjectives()[k]->name();
				block_->setObjective(string("mean_").append(currName), Utils::StatisticTools::mean(objs[k]), i);
				block_->setObjective(string("stdvar_").append(currName), Utils::StatisticTools::stdVariance(objs[k]), i);
			}

		}

		if (ret)
		{
			vector<shared_ptr<AnalysisConstraint>> constr = block_->getConstraints();
			auto sampleConstr = block_->getSampleConstraints(i);
			int numConstr=(int)constr.size();

			for (int j = 0; j < numConstr; ++j)
			{
				auto ret = constr[j]->isSatisfed(block_->getSampleConstraints(i, j));
				block_->setConstraintSatisfied(i, j, ret);
				if (!ret)
					block_->setSampleFeasibile(i,false);
			}

			/*if (objf_(block_, i) && postFeas_)
				postFeas_(block_, i);*/


		}
	}

	return;
}

void Model::dumpSamples(const std::string& filename,int opts=0)
{
	block_->dumpSamples(filename,opts);
	return;
}

void Model::setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf) { objf_ = objf; }

