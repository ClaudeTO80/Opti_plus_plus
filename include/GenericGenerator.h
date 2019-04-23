#pragma once
#include "AnalysisOptions.h"
#include <string>
#include <vector>
#include <memory>

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

	protected:
		std::vector<std::vector<double>> matrix_;
		GeneratorOptions genopts_;
	};
}
