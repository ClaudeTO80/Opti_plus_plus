#pragma once
#include <vector>
#include "DoeGenerator.h"
#include "AnalysisOptions.h"

namespace AnalysisGenerator
{
	class FullFactorialOptions : GeneratorOptions
	{
	public:
		FullFactorialOptions() {}
		void setNumDiscr(std::string name, int num)
		{
			discr_.insert(std::make_pair(name, num));
		}

		std::map<std::string, int> discr_;
	};

	class FullFactorial : public DoeGenerator
	{
	public:
		FullFactorial(const std::vector<std::pair<double, double>>& bounds) :DoeGenerator(bounds) {}
		FullFactorial(): DoeGenerator() {}
		bool generate() override;
		bool generateIndicesMatrix();
		void setLevels(const std::vector<int>& levels);
		void dumpIndicesMatrix(std::ostream& os, std::string separator = " ");
		void dumpIndicesMatrix(const std::string& fileName, std::ios_base::openmode mode = std::ios_base::out, std::string separator = " ");
	private:
		std::vector<std::vector<int>> matrixIndices_;
		std::vector<int> levels_;

	}; 
}