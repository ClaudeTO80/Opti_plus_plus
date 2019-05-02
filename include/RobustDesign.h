#pragma once
#include "AnalysisGenerator.h"
#include "AnalysisOptions.h"
#include <vector>

namespace AnalysisGenerator
{
	class RobustDesignOptions : public GeneratorOptions
	{
	public:
		RobustDesignOptions() {
			addOption("numSamples", 10);
			addOption("variances", 1);
		}
	};

	class RobustDesignGenerator : public Generator
	{
	public:
		RobustDesignGenerator(	const std::vector<double>& input,
								const std::vector<double>& var,
								int samples) :
								basicSample_(input),
								variance_(var),
								numSamples_(samples){}

		virtual bool generate() override;
		virtual void setOptions() override
		{
				
		}

	private:
		std::vector<std::vector<double>> basicSamples_;
		std::vector<double> basicSample_;
		//std::vector<std::vector<double>> output_;
		std::vector<double> variance_;
		int numSamples_;
	};
}
