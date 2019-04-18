#pragma once
#include "Model.h"

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

	for (int i = 0; i < dim; ++i)
	{
		if (!preFeas_ || preFeas_(block_, i))
		{
			if (objf_(block_, i) && postFeas_)
				postFeas_(block_, i);
		}
	}

	return;
}

void Model::dumpSamples(const std::string& filename)
{
	block_->dumpSamples(filename);
	return;
}

void Model::setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf) { objf_ = objf; }

