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
		Model();
		Model(std::shared_ptr<Generator>& generator);
		void setGenerator(std::shared_ptr<Generator>& generator);
		void setBlock(std::shared_ptr<AnalysisParametersBlock>& block);
		void run();
		void dumpSamples(const std::string& filename, int opts);
		void setObjf(std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf);
		void evalCorrCoeff()
		{
			block_->evalCorrCoeff();
		}

	private:
		std::shared_ptr<AnalysisParametersBlock> block_;
		std::shared_ptr<Generator> generator_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> objf_;
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> preFeas_{nullptr};
		std::function<bool(std::shared_ptr<AnalysisParametersBlock>&, int)> postFeas_{ nullptr };
	};
}