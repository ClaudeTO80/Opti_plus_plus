#pragma once
#include "STLHeaders.h"
#include "AnalysisParametersBlock.h"
#include "AnalysisOptions.h"

namespace AnalysisGenerator
{
	class Generator
	{
	public:

		bool dumpMatrix(std::ostream& os,
			bool headers = true,
			std::string separator = " ");

		bool dumpMatrix(const std::string& fileName,
			bool headers = true,
			std::ios_base::openmode mode = std::ios_base::out,
			std::string separator = " ");

		bool setOption(std::string name, std::string value)
		{
			return genopts_.setOption(name, value);
		}

		const std::vector<std::vector<double>>& getMatrix() { return matrix_; }
		virtual bool generate() = 0;
		virtual void setOptions() = 0;
		std::shared_ptr<AnalysisParametersBlock> getBlock() { return block_; }
	protected:
		std::vector<std::vector<double>> matrix_;
		GeneratorOptions genopts_;
		std::shared_ptr<AnalysisParametersBlock> block_;
	};
}
