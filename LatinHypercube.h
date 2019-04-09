#pragma once
#include <vector>
#include "DoeGenerator.h"
#include "AnalysisOptions.h"

namespace AnalysisGenerator
{
	class LatinHypercubeOptions : GeneratorOptions
	{
	public:
		enum Options { NumSamples_ = 0 };
		LatinHypercubeOptions() {
			addOption(NumSamples_, 10);
		}
	};

	class LatinHypercube : public DoeGenerator
	{
	public:
		LatinHypercube(const std::vector<std::pair<double, double>>& bounds) :DoeGenerator(bounds) {}
		LatinHypercube() :DoeGenerator() {}
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
	private:
		std::vector<std::vector<int>> matrixIndices_;
		int numSamples_;

	};
}