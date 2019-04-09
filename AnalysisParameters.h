#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace AnalysisGenerator
{
	class AnalysisParameter
	{
	public:
		friend class AnalysisParameters;

		int numDiscr() { return numDiscr_; };
		void numDiscr(int value) { numDiscr_ = value; };
		bool isArray() { return dim_ > 0; }
		bool isScalar() { return dim_ == 0; }
		double lb() { return lb_; }
		double ub() { return ub_; }
		std::vector<double> values() { return values_; }
		std::string name() { return name_; }
		int size() { return dim_; }

	private:
		AnalysisParameter() {}
		AnalysisParameter(std::string name, double lb, double ub);
		AnalysisParameter(std::string name, const std::vector<double>& values);
		AnalysisParameter(std::string name, double lb, double ub, int dim);
		AnalysisParameter(std::string name, const std::vector<double>& values, int dim);

		std::string name_{ "" };
		std::vector<double> values_;
		double lb_{ 0 }, ub_{ 0 };
		int dim_{ 0 };
		int numDiscr_{ 2 };
	};


	class Sample
	{
	public:
		Sample(const std::vector<double>& values)
		{
			values_.assign(values.begin(), values.end());
			return;
		}

	private:
		std::vector<double> values_;
	};

	class SamplesSet
	{
	public:
		bool add(std::shared_ptr<Sample> sample, int pos)
		{
			if (pos >= numElems_)
				samples_.resize(pos);

			samples_.insert(std::begin(samples_) + pos, sample);

			return true;
		}

		bool add(std::shared_ptr<Sample> sample)
		{
			samples_.push_back(sample);
			return true;
		}

		std::shared_ptr<Sample> get(int i)
		{
			if (i >= numElems_)
				return std::make_shared<Sample>();
			else
				return samples_[i];
		}

	private:
		std::vector<std::shared_ptr<Sample>> samples_;
		int numElems_{ 0 };

	};

	class AnalysisParameters
	{
	public:
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim);
		
		bool addParameter(std::shared_ptr<AnalysisParameter> param)
		{
			if (params_.find(param->name()) == params_.end())
			{
				paramsVect_.push_back(param);
				params_.insert(std::make_pair(param->name(),param));
			}
		}

		std::shared_ptr<AnalysisParameter> getParameter(int index);
		std::shared_ptr<AnalysisParameter> getParameter(std::string name);
		
		void toScalar(	std::vector<double>& lb,
						std::vector<double>& ub,
						std::vector<std::vector<double>>& allowed,
						std::vector<std::string>& names)
		{

			std::for_each(std::begin(paramsVect_), std::end(paramsVect_), [&](std::shared_ptr<AnalysisParameter>& curr)
			{
				if (curr->isScalar())
				{
					lb.push_back(curr->lb());
					ub.push_back(curr->ub());
					names.push_back(curr->name());
				}

				if (curr->isArray())
				{
					int dim = curr->size();

					for(int j=0;j<dim;++j)
					{
						lb.push_back(curr->lb());
						ub.push_back(curr->ub());
						names.push_back(curr->name()+"["+std::to_string(j)+"]");
					}
				}

			});
		}

	private:
		std::vector<std::shared_ptr<AnalysisParameter>> paramsVect_;
		std::map<std::string, std::shared_ptr<AnalysisParameter>> params_;
	};

	class Model
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
			std::for_each(samples.begin(), samples.end(), [&](std::shared_ptr<Sample>& curr) 
			{
				samples_.add(curr);
			});

			return true;
		}

		bool addParameter(std::shared_ptr<AnalysisParameter> param)
		{
			return params_.addParameter(param);
		}

	private:
		AnalysisParameters params_;
		SamplesSet samples_;
	};
	
	
}

