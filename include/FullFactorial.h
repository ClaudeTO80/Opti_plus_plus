#pragma once
#include "STLHeaders.h"
#include "DoeGenerator.h"
#include "AnalysisOptions.h"

namespace AnalysisGenerator
{
	class FullFactorialOptions : public GeneratorOptions
	{
	public:
		FullFactorialOptions() {}
		
	};

	class FullFactorial : public DoeGenerator
	{
	public:
		FullFactorial(std::shared_ptr<AnalysisParametersBlock>& block): DoeGenerator(block) 
		{
			setOptions();
		}

		bool generate() override;
		bool generateIndicesMatrix();
		
		void dumpIndicesMatrix(std::ostream& os, std::string separator = " ");
		void dumpIndicesMatrix(const std::string& fileName, std::ios_base::openmode mode = std::ios_base::out, std::string separator = " ");
		void setOptions() override 
		{
			auto params = block_->getParameters();

			for (auto& curr : params)
				if (curr->values().empty())
				{
					genopts_.addOption(curr->name(), 10);
				}
		}
		
	private:
		std::vector<std::vector<int>> matrixIndices_;
		std::vector<int> levels_;
		//std::shared_ptr<FullFactorialOptions> ffopts_;

		void setLevels(const std::vector<int>& levels);
		

	}; 
}