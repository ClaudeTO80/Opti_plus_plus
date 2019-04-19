#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

namespace AnalysisGenerator
{
	class AnalysisParametersBlock;
	class AnalysisObjectiveCreator;

	/**
	@brief 
	@details
	@since 0.1.0
	*/
	class AnalysisConstraint
	{
	public:
		enum ConstrType {LB_=0,UB_,DB_,AV_};
		/**
		@brief Returns name of objective
		@details Returns name of objective. It must be a string with at least 1 character
		@return name: name of objective
		@since 0.1.0
		*/
		std::string name();
		
		ConstrType type();
		double lb();
		double ub();
		std::vector<double> values();
		bool isSatisfed(double value)
		{
			switch (type_)
			{
			case AnalysisGenerator::AnalysisConstraint::LB_:
				return value >= lb_;
				break;
			case AnalysisGenerator::AnalysisConstraint::UB_:
				return value <= ub_;
				break;
			case AnalysisGenerator::AnalysisConstraint::DB_:
				return  value >= lb_ && value <= ub_;
				break;
			case AnalysisGenerator::AnalysisConstraint::AV_:
				return std::find(av_.begin(), av_.end(), value) != av_.end();
				break;
			default:
				break;
			}
		}

	private:

		friend class AnalysisConstraintCreator;
		AnalysisConstraint(std::string name, double lb, double ub);
		AnalysisConstraint(std::string name, ConstrType type,double value);
		AnalysisConstraint(std::string name, std::vector<double> values);
		std::string name_{ "" };		/**< Name of constraint. It must be a non empty string @since 0.1.0*/
		double lb_{ 0 };
		double ub_{ 0 };
		std::vector<double> av_;
		ConstrType type_{DB_ };			/**< Direction of constraint. @since 0.1.0*/
	};

	class AnalysisConstraintCreator
	{
	public:
		static std::shared_ptr<AnalysisConstraint> createConstraint(std::string name, double lb, double ub);
		static std::shared_ptr<AnalysisConstraint> createConstraint(std::string name, AnalysisConstraint::ConstrType type, double value);
		static std::shared_ptr<AnalysisConstraint> createConstraint(std::string name, std::vector<double> values);
	
	};

	class AnalysisConstraints
	{
	public:
				
		AnalysisConstraints();
		size_t dim();

		std::string getName(int index);

		std::shared_ptr<AnalysisConstraint> get(int index);
		int getIndex(std::string name);

		const std::vector<std::shared_ptr<AnalysisConstraint>>& getConstraints();
	private:
		
		friend class AnalysisParametersBlock;

		void addConstraint(std::shared_ptr<AnalysisConstraint>& constr);

		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, double lb, double ub);
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value);
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, std::vector<double> values);

		const int findElement(std::string name);

		std::vector<std::shared_ptr<AnalysisConstraint>> constrVect_;
		std::map<std::string, std::shared_ptr<AnalysisConstraint>> constr_;
		std::map<std::string, int> pos_;

	};
}

