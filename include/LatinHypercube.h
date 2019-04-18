#pragma once
#include <vector>
#include <memory>
#include "DoeGenerator.h"
#include "AnalysisOptions.h"

namespace AnalysisGenerator
{
	class LatinHypercubeOptions : GeneratorOptions
	{
	public:
		LatinHypercubeOptions() {
			addOption("numSamples", 10);
		}
	};

	class LatinHypercube : public DoeGenerator
	{
	public:
		//LatinHypercube(const std::vector<std::pair<double, double>>& bounds) :DoeGenerator(bounds) {}
		LatinHypercube(std::shared_ptr<AnalysisParametersBlock>& block) :DoeGenerator(block)
		{
			setOptions();
		}

		bool generate() override;
		bool generateIndicesMatrix();
		void setNumSamples(int numSamples);
		void dumpIndicesMatrix(	std::ostream& os, 
								bool headers = true, 
								std::string separator = " ");
		void dumpIndicesMatrix(	const std::string& fileName, 
								bool headers = true, 
								std::ios_base::openmode mode = std::ios_base::out, 
								std::string separator = " ");
		void setOptions()
		{
			genopts_.addOption("numSamples", 1000);
			return;
		}
	private:
		std::vector<std::vector<int>> matrixIndices_;
		int numSamples_;

	};
}