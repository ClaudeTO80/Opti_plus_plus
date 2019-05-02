#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

namespace AnalysisGenerator
{
	class AnalysisParametersBlock;
	class AnalysisParameterCreator;

	/**
	@brief Class representing a parameter used for analysis
	@details This class represent a single parametr used for analysis. Each parameter has a name 
	(member @ref name_). Than it is possible to give bounds for parameter's values (members @ref lb_ and @ref ub_)
	or a set of allowed values (member @ref values_). Last feature of a parameter is being scalar or vectorial 
	(one dimensional array). Such characteristic is defined via member @ref dim_. It exposes only member methods 
	devoted to information retriving. All constructors and setting method are private and accessible only by class 
	@ref AnalysisParameter which handles a set of AnalysisParameter instances
	@since 0.1.0
	*/
	class AnalysisParameter
	{
	public:
		
		enum varianceType {ABSOLUTE_,PERCENTAGE_};

		//int numDiscr() { return numDiscr_; };
		//void numDiscr(int value) { numDiscr_ = value; };
		/**
		@brief Returns if parameter is vectorial or not
		@details Returns if parameter is vectorial or not. Internally it checks if member @ref dim_ is greater than zero.
		If true 1 is returned, 0 otherwise
		@return ret: 1 if parameter is vectorial (i.e. @ref dim_ is greater than zero), 0 otherwise
		@since 0.1.0
		*/
		bool isArray() { return dim_ > 0; }
		
		/**
		@brief Returns if parameter is scalar or not
		@details Returns if parameter is scalar or not. Internally it checks if member @ref dim_ is equal to zero.
		If true 1 is returned, 0 otherwise
		@return ret: 1 if parameter is scalar (i.e. @ref dim_ is equal to zero), 0 otherwise
		@since 0.1.0
		*/
		bool isScalar() { return dim_ == 0; }
		
		/**
		@brief Returns lower bound of parameter
		@details Returns lower bound of parameter
		@return lb: lower bound of parameter
		@since 0.1.0
		*/
		double lb() { return lb_; }
		
		/**
		@brief Returns upper bound of parameter
		@details Returns upper bound of parameter
		@return lb: upper bound of parameter
		@since 0.1.0
		*/
		double ub() { return ub_; }
		
		/**
		@brief Returns allowed values of parameter
		@details Returns allowed values of parameter. If size of vector @ref values_ is greater than zero it means that
		parameter has fixed allowed values. In such case lower and upper bounds are neglected
		@return values: allowed values of parameter
		@since 0.1.0
		*/
		std::vector<double> values() { return values_; }
		
		/**
		@brief Returns name of parameter
		@details Returns name of parameter. It must be a string with at least 1 character
		@return name: name of parameter
		@since 0.1.0
		*/
		std::string name() { return name_; }
		
		/**
		@brief Returns number of elements belonging to array parameter 
		@details If parameter is vectorial, it returns a non-zero dimension of array. If scalar 0 is returned
		@return size: number of elements belonging to array parameter
		@since 0.1.0
		*/
		int size() { return dim_; }

		void variance(double value, varianceType type) 
		{
			variance_ = value;
			vartype_ = type;
		}

		double variance() { return variance_; }
		varianceType varType() { return vartype_; }
		
	private:

		friend class AnalysisParameterCreator;
		AnalysisParameter() {}
		AnalysisParameter(std::string name, double lb, double ub);
		AnalysisParameter(std::string name, const std::vector<double>& values);
		AnalysisParameter(std::string name, double lb, double ub, int dim);
		AnalysisParameter(std::string name, const std::vector<double>& values, int dim);
		const std::vector<double> createValues(double lb, double ub, double step );
		const std::vector<double> createValues(double lb, double ub, int numElems);
		bool setBounds(double lb, double ub);
		bool setValues(double lb, double ub, double step );
		bool setValues(double lb, double ub, int numElems);
		bool setValues(const std::vector<double>& values);
		bool appendValues(double lb, double ub, double step );
		bool appendValues(double lb, double ub, int numElems);
		bool appendValues(const std::vector<double>& values);
		std::string name_{ "" };		/**< Name of parameter. It must be a non empty string @since 0.1.0*/
		std::vector<double> values_;    /**< Allowed values of parameter. If empty, lower and upper bpunds must be defined. Otherwise bounds values are neglected. @since 0.1.0*/
		double lb_{ 0 };      			/**< Lower bound of parameter @since 0.1.0*/
		double ub_{ 0 };      			/**< Upper bound of parameter @since 0.1.0*/
		int dim_{ 0 };                  /**< Number of element belonging to vectorial parameter @since 0.1.0*/
		//int numDiscr_{ 2 };             /**< Detailed description after the member */
		double variance_{ 0 };
		varianceType vartype_{ ABSOLUTE_ };
	};

	class AnalysisParameterCreator
	{
	public:
		static std::shared_ptr<AnalysisParameter> createParameter(const std::string& name, double lb, double ub)
		{
			if (name.empty() || lb >= ub)
				return {};

			else
				return std::shared_ptr<AnalysisParameter>(new AnalysisParameter(name, lb, ub));
		}
				
		static std::shared_ptr<AnalysisParameter> createParameter(const std::string& name, const std::vector<double>& values)
		{
			if (name.empty() || values.empty())
				return {};

			return std::shared_ptr<AnalysisParameter>(new AnalysisParameter(name, values));
		}

		static std::shared_ptr<AnalysisParameter> createParameter(const std::string& name, double lb, double ub, int dim)
		{
			if (name.empty() || lb >= ub || dim <=0)
				return {};

			return std::shared_ptr<AnalysisParameter>(new AnalysisParameter(name, lb, ub));
		}

		static std::shared_ptr<AnalysisParameter> createParameter(const std::string& name, const std::vector<double>& values, int dim)
		{
			if (name.empty() || values.empty() || dim <= 0)
				return {};

			return std::shared_ptr<AnalysisParameter>(new AnalysisParameter(name, values, dim));
		}

		static std::shared_ptr<AnalysisParameter> createParameter(const std::shared_ptr<AnalysisParameter>& src)
		{
			return createParameter(src.get());
		}

		static std::shared_ptr<AnalysisParameter> createParameter(const AnalysisParameter* src)
		{
			AnalysisParameter* param = new AnalysisParameter();
			param->name_ = src->name_;
			param->lb_ = src->lb_;
			param->ub_ = src->ub_;
			param->dim_ = src->dim_;
			param->values_.reserve(src->values_.size());
			param->values_.assign(src->values_.begin(), src->values_.end());
			param->variance_ = src->variance_;
			param->vartype_ = src->vartype_;
			return std::shared_ptr<AnalysisParameter>(param);
		}
	};

	class AnalysisParameters
	{
	public:
				
		AnalysisParameters() {}
		AnalysisParameters clone()
		{
			AnalysisParameters output;
			std::for_each(paramsVect_.begin(), paramsVect_.end(), [&](const std::shared_ptr<AnalysisParameter>& curr)
			{
				auto temp = AnalysisParameterCreator::createParameter(curr);
				output.addParameter(temp);
			});

			return output;
		}

	private:
		
		friend class AnalysisParametersBlock;
		std::shared_ptr<AnalysisParameter> addParameter(std::shared_ptr<AnalysisParameter>& param);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim);
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim);
				
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
		const std::vector<std::shared_ptr<AnalysisParameter>>& getParameters() { return paramsVect_; }
		const int findElement(std::string name)
		{
			auto temp = pos_.find(name);

			if (temp == pos_.end())
				return -1;

			else
				return temp->second;
		}
		size_t dim()
		{
			return paramsVect_.size();
		}

		std::vector<std::shared_ptr<AnalysisParameter>> paramsVect_;
		std::map<std::string, std::shared_ptr<AnalysisParameter>> params_;
		std::map<std::string, int> pos_;
		

	};
}

