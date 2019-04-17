#pragma once
#include "AnalysisParametersBlock.h"
#include "GenericGenerator.h"
#include <functional>
#include <iostream>

namespace AnalysisGenerator
{
	class Model
	{

	public:
		Model() {};
		Model(std::shared_ptr<Generator>& generator) : generator_(generator) {}
		void setGenerator(std::shared_ptr<Generator>& generator)
		{
			generator_=generator;
			return;
		}

		void setBlock(std::shared_ptr<AnalysisParametersBlock>& block)
		{
			block_ = block;
			return;
		}


		void run()
		{
			generator_->generate();
			auto mat=generator_->getMatrix();
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

		void dumpSamples(const std::string& filename)
		{
			block_->dumpSamples(filename);
			return;
		}

		void setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf) {objf_ = objf;}
	private:
		std::shared_ptr<AnalysisParametersBlock> block_;
		std::shared_ptr<Generator> generator_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> preFeas_{nullptr};
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> postFeas_{ nullptr };
	};
}