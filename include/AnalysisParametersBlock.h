#pragma once
#include "AnalysisParameters.h"
#include "AnalysisSample.h"
#include "AnalysisObjectives.h"
#include "AnalysisConstraints.h"
#include "AnGenUtils.h"
#include <memory>
#include <iostream>
#include <fstream>

namespace AnalysisGenerator
{
	#define OPTIPP_DUMP_FEAS	0x00000001
	#define OPTIPP_DUMP_PARETO	0x00000002

	class AnalysisParametersBlock
	{
	public:
		static std::shared_ptr<AnalysisParametersBlock> create()
		{
			auto temp = new AnalysisParametersBlock();
			std::shared_ptr<AnalysisParametersBlock> ptr;
			ptr.reset(temp);

			return ptr;
		}

		std::shared_ptr<Sample> getSample(int i);
		std::shared_ptr<Sample> getSampleObjectives(int i);
		std::shared_ptr<Sample> getSampleConstraints(int i);
		double getSampleConstraints(int indSample, int indConstr);
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
		const std::vector<std::shared_ptr<AnalysisObjective>>& getObjectives();
		const std::vector<std::shared_ptr<AnalysisConstraint>>& getConstraints();
		bool setObjective(std::string name, double value,int index);
		bool setConstraint(std::string name, double value, int index);
		const double getValue(std::string name,int pos);
		size_t getNumSamples();
		bool addSample(const std::vector<double>& value);
		unsigned int addSamples(const std::vector<std::vector<double>>& values);
		bool dumpSamples(	const std::string& fileName,
							int opts = OPTIPP_DUMP_FEAS | OPTIPP_DUMP_PARETO ,
							bool headers = true,
							std::ios_base::openmode mode = std::ios_base::out,
							std::string separator = " ");

		void setConstraintSatisfied(int indSample, int indConstr, bool value)
		{
			if (indSample>=(int)satisfied_.size() ||
				indConstr>= (int)satisfied_[indSample].size())
				satisfied_[indSample][indConstr]=value;
			return;
		}

		void setSampleFeasibile(int indSample, bool value)
		{
			if (indSample >= (int)feasibile_.size())
				feasibile_[indSample] = value;
			return;
		}

		void evalParetoFront()
		{
			paretoSols_.clear();
			int numSamples = (int)samples_.dim();
			int numObjs = (int)objs_.dim();

			for (int i = 0; i < numSamples; ++i)
			{
				auto currSampleObjs = samplesObjs_.get(i);
				bool isPareto = true;
				for (int j = 0; j < numSamples; ++j)
				{
					if (i == j)
						continue;

					auto tempSampleObjs= samplesObjs_.get(j);
					
					for (int k = 0; k < numObjs; ++k)
					{
						auto currObj = objs_.get(k);
						if (currObj->dir() == AnalysisObjective::MIN_)
						{
							if (currSampleObjs->values_[k] > tempSampleObjs->values_[k])
							{
								isPareto = false;
								break;
							}
						}

						if (currObj->dir() == AnalysisObjective::MAX_)
						{
							if (currSampleObjs->values_[k] < tempSampleObjs->values_[k])
							{
								isPareto = false;
								break;
							}
						}
					}

					if (!isPareto)
						break;
				}

				if (isPareto)
					paretoSols_.push_back(i);
			}
		}
		
		void evalCorrCoeff()
		{
			int numSamples = (int)samples_.dim();
			int numParams = (int)params_.dim();
			int numObjs = (int)objs_.dim();
			int numConstr = (int)constr_.dim();
			corrCoeff_.clear();
			corrCoeff_.resize(numParams);

			for (int j = 0; j < numParams; ++j)
			{

				std::vector<double>currParamCoeffs;
				currParamCoeffs.resize(numObjs + numConstr);
				std::vector<double>currParamValues;
				currParamValues.resize(numSamples);

				for (int i = 0; i < numSamples; ++i)
				{
					auto currSample = samples_.get(i);
					currParamValues[i] = currSample->values_[j];
				}

				int pos = 0;
				/*std::vector<double> currResValues;
				currResValues.resize(numObjs+numConstr);
				corrCoeff_[j] = currParamValues;*/
				for (int k = 0; k < numObjs; ++k)
				{
					std::vector<double>currObjValues;
					currObjValues.resize(numSamples);

					for (int i = 0; i < numSamples; ++i)
					{
						auto currObjSamples = samplesObjs_.get(i);
						currObjValues[i] = currObjSamples->values_[k];
					}

					currParamCoeffs[pos] = Utils::StatisticTools::CorrCoeff(currParamValues, currObjValues);
					++pos;
				}

				for (int k = 0; k < numConstr; ++k)
				{
					std::vector<double>currConstrValues;
					currConstrValues.resize(numSamples);

					for (int i = 0; i < numSamples; ++i)
					{
						auto currConstrSamples = samplesConstr_.get(i);
						currConstrValues[i] = currConstrSamples->values_[k];
					}

					currParamCoeffs[pos] = Utils::StatisticTools::CorrCoeff(currParamValues, currConstrValues);
					++pos;
				}

				corrCoeff_[j] = currParamCoeffs;
			}

			int dim =(int) corrCoeff_[0].size();

			for (int j = 0; j < dim; ++j)
			{
				double tot = 0;
				for (int i = 0; i < numParams; ++i)
					tot += abs(corrCoeff_[i][j]);

				for (int i = 0; i < numParams; ++i)
					corrCoeff_[i][j]/=tot;
			}

		}
		
		std::shared_ptr<AnalysisParametersBlock> clone()
		{
			auto output = create();
			output->params_ = params_.clone();
			output->objs_ = objs_.clone();
			output->constr_ = constr_.clone();
			return output;
		}

	private:

		AnalysisParametersBlock() {}
		AnalysisParameters params_;
		AnalysisObjectives objs_;
		AnalysisConstraints constr_;
		SamplesSet samples_;
		SamplesSet samplesObjs_;
		SamplesSet samplesConstr_;
		std::vector<std::vector<bool>> satisfied_;
		std::vector<bool> feasibile_;
		std::vector<bool> paretoSols_;
		std::vector<std::vector<double>> corrCoeff_;
	};
}