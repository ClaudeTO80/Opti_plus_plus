#include "Model.h"
#include "AnalysisConstraints.h"

using namespace std;
using namespace AnalysisGenerator;

Model::Model() {};

Model::Model(std::shared_ptr<Generator>& generator) : generator_(generator) {}
void Model::setGenerator(std::shared_ptr<Generator>& generator)
{
	generator_ = generator;
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
	block_->addSamples(mat);
	auto dim = block_->getNumSamples();

	for (int i = 0; i < (int)dim; ++i)
	{
		auto ret = objf_(block_, i);

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

			if (objf_(block_, i) && postFeas_)
				postFeas_(block_, i);
		}
	}

	return;
}

void Model::dumpSamples(const std::string& filename,int opts)
{
	block_->dumpSamples(filename);
	return;
}

void Model::setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf) { objf_ = objf; }

