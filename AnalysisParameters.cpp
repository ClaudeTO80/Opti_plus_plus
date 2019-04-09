#include "AnalysisParameters.h"


using namespace std;
using namespace AnalysisGenerator;

AnalysisParameter::AnalysisParameter(std::string name, double lb, double ub)
{
	name_ = name;
	lb_ = lb;
	ub_ = ub;
}

AnalysisParameter::AnalysisParameter(string name, const vector<double>& values)
{
	name_ = name;
	values_ = values;
}

AnalysisParameter::AnalysisParameter(string name, double lb, double ub, int dim)
{
	name_ = name;
	lb_ = lb;
	ub_ = ub;
	dim_ = dim;
}

AnalysisParameter::AnalysisParameter(string name, const vector<double>& values, int dim)
{
	name_ = name;
	values_ = values;
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, double lb, double ub)
{
	auto param = new AnalysisParameter(name, lb, ub);
	shared_ptr<AnalysisParameter> shared_param;
	shared_param.reset(param);
	paramsVect_.push_back(shared_param);
	params_.insert(make_pair(name, shared_param));
	return shared_param;
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, const vector<double>& values)
{
	auto param = new AnalysisParameter(name, values);
	shared_ptr<AnalysisParameter> shared_param;
	shared_param.reset(param);
	paramsVect_.push_back(shared_param);
	params_.insert(make_pair(name, shared_param));
	return shared_param;
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, double lb, double ub, int dim)
{
	auto param = new AnalysisParameter(name, lb, ub, dim);
	shared_ptr<AnalysisParameter> shared_param;
	shared_param.reset(param);
	paramsVect_.push_back(shared_param);
	params_.insert(make_pair(name, shared_param));
	return shared_param;
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, const vector<double>& values, int dim)
{
	auto param = new AnalysisParameter(name, values, dim);
	shared_ptr<AnalysisParameter> shared_param(param);
	//shared_param.reset(param);
	paramsVect_.push_back(shared_param);
	params_.insert(make_pair(name, shared_param));
	return shared_param;
}

shared_ptr<AnalysisParameter> AnalysisParameters::getParameter(int index)
{
	shared_ptr<AnalysisParameter> temp;
	return index < (int)paramsVect_.size() ? paramsVect_[index] : temp;
}

shared_ptr<AnalysisParameter> AnalysisParameters::getParameter(string name)
{
	auto param = params_.find(name);
	shared_ptr<AnalysisParameter> temp;
	return param != params_.end() ? param->second : temp;
}