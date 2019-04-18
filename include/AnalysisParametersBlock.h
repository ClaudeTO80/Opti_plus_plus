#pragma once
#include "AnalysisParameters.h"
#include "AnalysisSample.h"
#include "AnalysisObjectives.h"
#include "AnalysisConstraints.h"
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
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value);
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, std::vector<double> values);
		
		const std::vector<std::shared_ptr<AnalysisParameter>>& getParameters();
		bool setObjective(std::string name, double value,int index);
		bool setConstraint(std::string name, double value, int index);
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
		AnalysisConstraints constr_;
		SamplesSet samples_;
		SamplesSet samplesObjs_;
		SamplesSet samplesConstr_;
	};
}