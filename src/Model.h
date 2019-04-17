#pragma once
#include "AnalysisParametersBlock.h"
#include <functional>

namespace AnalysisGenerator
{
	class Model
	{

	public:
		Model() {};
		Model(const std::shared_ptr<Generator>& generator) : generator_(generator) {}
		void setGenerator(const std::shared_ptr<Generator>& generator)
		{
			generator_=generator;
			return;
		}

		void run()
		{
			generator_->generate();
			auto mat=generator_->getMatrix();

			auto dim = block_->getNumSamples();

			for (int i = 0; i < dim; ++i)
			{
				if (preFeas_ && preFeas_(block_, i))
				{
					if (objf_(block_, i) && postFeas_)
						postFeas_(block_, i);
				}
			}
		}

		void setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf) {objf_ = objf;}
	private:
		std::shared_ptr<AnalysisParametersBlock> block_;
		std::shared_ptr<Generator> generator_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> preFeas_{nullopt};
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> postFeas_{ nullopt };
	};
}