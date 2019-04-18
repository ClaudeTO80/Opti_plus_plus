#pragma once
#include "AnalysisParameters.h"
#include "AnalysisSample.h"
#include "AnalysisObjectives.h"
#include <iostream>
#include <fstream>

namespace AnalysisGenerator
{
	class AnalysisParametersBlock
	{
	public:
		std::shared_ptr<Sample> getSample(int i);
		bool addSample(std::shared_ptr<Sample> sample);
		bool addSamples(const std::vector<std::shared_ptr<Sample>>& samples);
		bool addParameter(std::shared_ptr<AnalysisParameter> param);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim);
		std::shared_ptr<AnalysisObjective> addObjective(std::string name, AnalysisObjective::ObjDir dir);
		const std::vector<std::shared_ptr<AnalysisParameter>>& getParameters();
		bool setObjective(std::string name, double value,int index);
		const double getValue(std::string name,int pos);
		size_t getNumSamples();
		bool addSample(const std::vector<double>& value);
		unsigned int addSamples(const std::vector<std::vector<double>>& values);
		bool dumpSamples(const std::string& fileName,
			bool headers = true,
			std::ios_base::openmode mode = std::ios_base::out,
			std::string separator = " ");

	public:
		AnalysisParameters params_;
		AnalysisObjectives objs_;
		SamplesSet samples_;
		SamplesSet samplesObjs_;
	};
}