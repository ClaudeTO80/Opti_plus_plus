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
		@brief Returns all objectives values of an analysis sample
		@details Returns values of all objectives of an analysis sample whose index is defined by parameter @ref i.
		@param i: index of required sample's objectives
		@return obj_ptr: shared pointer to required objectives values
		@since 0.1.0.0
		*/
		std::shared_ptr<Sample> getSampleObjectives(int i);

		/**
		@brief Returns all constriants values of an analysis sample
		@details Returns values of all constriants of an analysis sample whose index is defined by parameter @ref i.
		@param i: index of required sample's constraints
		@return constr_ptr: shared pointer to required constriants values
		@since 0.1.0.0
		*/
		std::shared_ptr<Sample> getSampleConstraints(int i);

		/**
		@brief Get a constraint value of a sample
		@details Returns a constraint values, identified by parameter @ref indConstr, if a given sample, identified 
		by parameter @ref indSample
		@param indSample: index of required sample's constraint value
		@param indConstr: index of required constraint value
		@return constrValue: value of constraint
		@since 0.1.0.0
		*/
		double getSampleConstraint(int indSample, int indConstr);

		/**
		@brief Adds a sample to samples set
		@details Adds a sample to samples set. Currently there is no reason why joining shoud fail.
		@param sample: shared pointer of sample to be added
		@return status: true is sample had been succesfully added to samples set, false otherwise.
		@since 0.1.0.0
		*/
		bool addSample(std::shared_ptr<Sample> sample);

		/**
		@brief Adds a vecotr of samples to samples set
		@details Adds a vector f sample to samples set. Currently there is no reason why joining shoud fail.
		@param samples: vector of shared pointer of samplse to be added
		@return status: true is samples had been succesfully added to samples set, false otherwise.
		@since 0.1.0.0
		*/
		bool addSamples(const std::vector<std::shared_ptr<Sample>>& samples);

		/**
		@brief Adds a parameter to analysis parameters set
		@details Adds a parameter to analysis parameters set. Joining new parameter is sucessfull only if another parameter 
		with same name	does not exist yet. If it already exists, joining fails. If joining fails, function returns shared 
		pointer of parameter already defined in analysis parameters set.
		@param param: shared pointer of parameter to be added
		@return addedPara: shared pointer to added parameter. If joining fails, function returns shared	pointer of parameter 
		already defined in analysis parameters set.
		@since 0.1.0.0
		*/
		shared_ptr<AnalysisParameter> addParameter(std::shared_ptr<AnalysisParameter> param);

		/**
		@brief Adds a double bounded parameter to analysis parameters set
		@details Adds a parameter to analysis parameters set. This overload defines a double bounded parameter.
		Joining new parameter is sucessfull only if another parameter with same name	does not exist yet. If it already 
		exists, joining fails. Information about new parameter are given via input parameters @ref name, @ref lb, @ref ub. 
		@param name: name of parameter to be added
		@param lb: lower bound of parameter to be added
		@param ub: upper bound of parameter to be added
		@return addedPara: shared pointer to added parameter. If joining fails, function returns shared	pointer of parameter
		already defined in analysis parameters set.
		@since 0.1.0.0
		*/
		std::shared_ptr<AnalysisParameter> addParameter(std::string name, double lb, double ub);

		/**
		@brief Adds a values defined parameter to analysis parameters set
		@details Adds a parameter to analysis parameters set. This overload defines a parameter with fixed values.
		Joining new parameter is sucessfull only if another parameter with same name	does not exist yet. If it already
		exists, joining fails. Information about new parameter are given via input parameters @ref name, @ref values,.
		@param name: name of parameter to be added
		@param values: vector of fixed values of parameter to be added
		@return addedPara: shared pointer to added parameter. If joining fails, function returns shared	pointer of parameter
		already defined in analysis parameters set.
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
		@brief Set value of a sample's objective
		@details Set value of a sample's objective. Objective is identified by its name (parameter @ref name). Value is 
		defined by parameter @ref value. Sample is identified by @ref index
		param name: name of objective whose value must be set
		param value: value of objective to be set
		param index: index of sample show objective must be set
		@since 0.1.0.0
		*/
		bool setObjective(std::string name, double value,int index);

		/**
		@brief Set value of a sample's constraint
		@details Set value of a sample's constraint. Constraint is identified by its name (parameter @ref name). Value is
		defined by parameter @ref value. Sample is identified by @ref index
		param name: name of constraint whose value must be set
		param value: value of constraint to be set
		param index: index of sample show constraint must be set
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