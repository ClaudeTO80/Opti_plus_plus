#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace AnalysisGenerator
{
	class AnalysisParametersBlock;
	class AnalysisParameters;

	class AnalysisParameter
	{
	public:
		

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

		friend class AnalysisParameters;
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

	class AnalysisParameters
	{
	public:
				
		
	private:
		friend class AnalysisParametersBlock;
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim);
		
		bool addParameter(std::shared_ptr<AnalysisParameter> param)
		{
			if (params_.find(param->name()) == params_.end())
			{
				paramsVect_.push_back(param);
				params_.insert(std::make_pair(param->name(), param));
			}
		}

		void toScalar(std::vector<double>& lb,
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

					for (int j = 0; j < dim; ++j)
					{
						lb.push_back(curr->lb());
						ub.push_back(curr->ub());
						names.push_back(curr->name() + "[" + std::to_string(j) + "]");
					}
				}

			});
		}

		std::shared_ptr<AnalysisParameter> getParameter(int index);
		std::shared_ptr<AnalysisParameter> getParameter(std::string name);

		std::vector<std::shared_ptr<AnalysisParameter>> paramsVect_;
		std::map<std::string, std::shared_ptr<AnalysisParameter>> params_;
	};
}

