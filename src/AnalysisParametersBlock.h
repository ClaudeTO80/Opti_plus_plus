#pragma once
#include "AnalysisParameters.h"
#include "AnalysisSample.h"
#include "AnalysisObjectives.h"

namespace AnalysisGenerator
{
	class AnalysisParametersBlock
	{
	public:
		std::shared_ptr<Sample> getSample(int i)
		{
			return samples_.get(i);
		}

		bool addSample(std::shared_ptr<Sample> sample)
		{
			return samples_.add(sample);
		}

		bool addSamples(const std::vector<std::shared_ptr<Sample>>& samples)
		{
			std::for_each(samples.begin(), samples.end(), [&](const std::shared_ptr<Sample>& curr)
			{
				samples_.add(curr);
			});

			return true;
		}

		bool addParameter(std::shared_ptr<AnalysisParameter> param)
		{
			return params_.addParameter(param).get();
		}

		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub)
		{
			return params_.addParameter(name, lb,ub);
		}

		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values)
		{
			return params_.addParameter(name, values);
		}

		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim)
		{
			return params_.addParameter(name, lb, ub, dim);
		}

		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim)
		{
			return params_.addParameter(name, values, dim);
		}

		std::shared_ptr<AnalysisObjective> addObjective(std::string name, AnalysisObjective::ObjDir dir)
		{
			return objs_.addObjective(name, dir);
		}

		const std::vector<std::shared_ptr<AnalysisParameter>>& getParameters() { return params_.getParameters(); }

		const double getValue(std::string name,int pos)
		{
			int index=params_.findElement(name);
			samples_.get(pos)->values_[index];
		}

		size_t getNumSamples() { return samples_.dim(); }

	private:
		AnalysisParameters params_;
		AnalysisObjectives objs_;
		SamplesSet samples_;
	};
}