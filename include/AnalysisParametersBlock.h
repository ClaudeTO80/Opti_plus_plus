#pragma once
#include "STLHeaders.h"
#include "AnalysisParameters.h"
#include "AnalysisSample.h"
#include "AnalysisObjectives.h"
#include "AnalysisConstraints.h"
#include "AnGenUtils.h"

namespace AnalysisGenerator
{
	#define OPTIPP_DUMP_FEAS	0x00000001
	#define OPTIPP_DUMP_PARETO	0x00000002

	/**
	A self-consistent data storage with all information required for problem definition and samples management.
	In order to have a complete data set there are a set of information:
	 - definition of all parameters (member data @ref params_)
	 - definition of all objectives (member data @ref objs_)
	 - definition of all constraints (member data @ref constr_)
	 - definition of all created analysis samples (member data @ref samples_)
	 - values of all objectives for all create analysis samples (member data @ref samplesObjs_)
	 - values of all constraints for all create analysis samples (member data @ref samplesConstr_)
	 - information for all constraints values in @ref samplesConstr_ if they are satisfied or broken (member data @ref satisfied_)
	 - information for all samples in @ref samples_ if they are feasible or unfeasible (member data @ref feasibile_)
	 - information for all samples in @ref samples_ if they are belong to Pareto front (member data @ref paretoSols_)
	 - correlation coefficients which define how all parameters in @ref params_ (input) are correlated with all objective in 
	 @ref objs_ and constraints in @ref constr_ (member data @ref corrCoeff_)

	 Explicit constructors are not available, but it is possible getting shared pointer to object instances via member functions
	 @ref create (which is also static) and @ref clone (useful to copy data and use them as backup or inner processes 
	 like robust design)
	 @since 0.1.0.0
	*/
	class AnalysisParametersBlock
	{
	public:

		/**
		@brief Creation of a shared pointer of a new instance
		@details Static method which creates a new smart pointer. It is the only way to make a new instance of class. All 
		member data are created and defined empty.
		@return block_ptr: shared pointer of new instance
		@since 0.1.0.0
		*/
		static std::shared_ptr<AnalysisParametersBlock> create();

		/**
		@brief Returns an analysis sample
		@details Returns analysis sample whose index is defined by parameter @ref i.
		@param i: index of required sample
		@return sample_ptr: shared pointer to required sample.
		@since 0.1.0.0
		*/
		std::shared_ptr<Sample> getSample(int i);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<Sample> getSampleObjectives(int i);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<Sample> getSampleConstraints(int i);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		double getSampleConstraints(int indSample, int indConstr);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool addSample(std::shared_ptr<Sample> sample);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool addSamples(const std::vector<std::shared_ptr<Sample>>& samples);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool addParameter(std::shared_ptr<AnalysisParameter> param);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub, int dim);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, const std::vector<double>& values, int dim);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisObjective> addObjective(std::string name, AnalysisObjective::ObjDir dir);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, double lb, double ub);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisConstraint> addConstraint(std::string name, std::vector<double> values);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		
		const std::vector<std::shared_ptr<AnalysisParameter>>& getParameters();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		const std::vector<std::shared_ptr<AnalysisObjective>>& getObjectives();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		const std::vector<std::shared_ptr<AnalysisConstraint>>& getConstraints();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool setObjective(std::string name, double value,int index);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool setConstraint(std::string name, double value, int index);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		const double getValue(std::string name,int pos);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		size_t getNumSamples();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool addSample(const std::vector<double>& value);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		unsigned int addSamples(const std::vector<std::vector<double>>& values);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		bool dumpSamples(	const std::string& fileName,
							int opts = OPTIPP_DUMP_FEAS | OPTIPP_DUMP_PARETO ,
							bool headers = true,
							std::ios_base::openmode mode = std::ios_base::out,
							std::string separator = " ");

		/**
		@brief
		@details
		@since 0.1.0.0
		*/

		void setConstraintSatisfied(int indSample, int indConstr, bool value);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		void setSampleFeasibile(int indSample, bool value);

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		void evalParetoFront();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		void evalCorrCoeff();

		/**
		@brief
		@details
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParametersBlock> clone();

	private:

		AnalysisParametersBlock() {}

		/**
		Instance of @ref AnalysisParameters class. Keeps information about all parameters.
		@since 0.1.0.0
		*/
		AnalysisParameters params_;

		/**
		Instance of @ref AnalysisObjectives class. Keeps information about all objectives.
		@since 0.1.0.0
		*/
		AnalysisObjectives objs_;

		/**
		Instance of @ref AnalysisConstraints class. Keeps information about all constriants.
		@since 0.1.0.0
		*/
		AnalysisConstraints constr_;

		/**
		Instance of @ref SamplesSet class. Keeps information about all created samples.
		@since 0.1.0.0
		*/
		SamplesSet samples_;

		/**
		Instance of @ref SamplesSet class. Keeps information about all obejctive functions of all created samples.
		@since 0.1.0.0
		*/
		SamplesSet samplesObjs_;

		/**
		Instance of @ref SamplesSet class. Keeps information about all constraint of all created samples.
		@since 0.1.0.0
		*/
		SamplesSet samplesConstr_;

		/**
		For each constraint in @ref samplesConstr_, keeps information if they are satisfied (true) or broken (true)
		@since 0.1.0.0
		@sa setConstraintSatisfied setSampleFeasibile
		*/
		std::vector<std::vector<bool>> satisfied_;

		/**
		For each sample in @ref samples_, keeps information if they are feasible (i.e. all constraints are satisfied) or 
		unfeasible (i.e. at least one costraint is broken)
		@since 0.1.0.0
		@sa setConstraintSatisfied setSampleFeasibile
		*/
		std::vector<bool> feasibile_;

		/**
		For each sample in @ref samples_, keeps information if they belong to current Pareto front. Pareto front is evaluated
		by member function @ref evalParetoFront
		@since 0.1.0.0
		@sa evalParetoFront
		*/
		std::vector<bool> paretoSols_;

		/**
		For each parameter in @ref params_, keeps information of correlation coefficients among parameters and objectives & 
		constraints. Correlation coefficients are evaluated by member function @ref evalCorrCoeff.
		@since 0.1.0.0
		@sa evalCorrCoeff
		*/
		std::vector<std::vector<double>> corrCoeff_;
	};
}