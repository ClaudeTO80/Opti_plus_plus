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

		bool setObjective(std::string name, double value,int index)
		{
			auto pos=objs_.getIndex(name);

			if (pos == -1)
				return false;

			auto sample = samplesObjs_.get(index);
			return sample->setValue(value, pos);
		}

		const double getValue(std::string name,int pos)
		{
			int index=params_.findElement(name);

			if (index < 0)
				return -1e30;

			auto sample = samples_.get(pos);
			if (!sample.get())
				return -1e30;

			if (index >= sample->values_.size())
				return -1e30;

			return sample->values_[index];
		}

		size_t getNumSamples() { return samples_.dim(); }

		bool addSample(const std::vector<double>& value) 
		{ 
			auto temp = new Sample(value);
			std::shared_ptr<Sample> tt;
			tt.reset(temp);
			auto ret=samples_.add(tt);

			if (ret)
			{
				std::vector<double> currObjs;
				currObjs.reserve(objs_.dim());

				for (int i = 0; i < objs_.dim(); ++i)
				{
					auto dir = objs_.get(i)->dir();
					if (dir == AnalysisObjective::MIN_)
						currObjs.push_back(1e30);

					if (dir == AnalysisObjective::MAX_ || dir == AnalysisObjective::TARGET_)
						currObjs.push_back(-1e30);
				}

				/*auto temp = new Sample(currObjs);
				std::shared_ptr<Sample> tt(new Sample(currObjs));
				tt.reset(temp);*/
				samplesObjs_.add(std::shared_ptr<Sample>(new Sample(currObjs)));
			}
			return ret;
		}

		unsigned int addSamples(const std::vector<std::vector<double>>& values)
		{ 
			unsigned int num= 0;
			samples_.capacity(values.size());
			samplesObjs_.capacity(values.size());
			std::for_each(values.begin(), values.end(), [&](const std::vector<double>& value)
			{
				num += (int)addSample(value);
			});

			return num;
		}

		bool dumpSamples(const std::string& fileName,
			bool headers = true,
			std::ios_base::openmode mode = std::ios_base::out,
			std::string separator = " ")
		{
			std::ofstream ofs(fileName, mode);

			if (!ofs.is_open())
				return false;

			int numSamples = (int)samples_.dim();
			/*auto params = params_.getParameters();*/
			auto params = params_.getParameters();
			int numVars = (int)params.size();

			auto objs = objs_.getObjectives();
			int numObjs = (int)objs.size();

			if (headers)
			{
				for (auto& param: params)
					ofs << param->name() << separator;

				for (auto& param : objs)
					ofs << param->name() << separator;

				ofs << std::endl;
			}

			for (int i = 0; i < numSamples; ++i)
			{
				auto currSample = samples_.get(i);
				for (int j = 0; j < numVars; ++j)
					ofs << currSample->values_[j] << separator;
				
				auto currObj = samplesObjs_.get(i);
				for (int j = 0; j < numObjs; ++j)
					ofs << currObj->values_[j] << separator;

				ofs << std::endl;
			}

			return true;
		}


	public:
		AnalysisParameters params_;
		AnalysisObjectives objs_;
		SamplesSet samples_;
		SamplesSet samplesObjs_;
	};
}