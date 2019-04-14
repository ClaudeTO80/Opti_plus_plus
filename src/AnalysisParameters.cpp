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

std::shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(shared_ptr<AnalysisParameter>& param)
{
	if (param.get())
	{
		paramsVect_.push_back(param);
		params_.insert(make_pair(param->name(), param));
	}
		
	return param;
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, double lb, double ub)
{
	if (params_.find(name) == params_.end())
		return addParameter(AnalysisParameterCreator::createParameter(name, lb, ub));
	else
		return {};
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, const vector<double>& values)
{
	if (params_.find(name) == params_.end())
		return addParameter(AnalysisParameterCreator::createParameter(name, values));
	else
		return {};
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, double lb, double ub, int dim)
{
	if (params_.find(name) == params_.end())
		return addParameter(AnalysisParameterCreator::createParameter(name, lb, ub, dim));
	else
		return {};
}

shared_ptr<AnalysisParameter> AnalysisParameters::addParameter(string name, const vector<double>& values, int dim)
{
	if (params_.find(name) == params_.end())
		return addParameter(AnalysisParameterCreator::createParameter(name, values, dim));
	else
		return {};
}

shared_ptr<AnalysisParameter> AnalysisParameters::getParameter(int index)
{
	shared_ptr<AnalysisParameter> temp;
	return index < (int)paramsVect_.size() ? paramsVect_[index] : temp;
}

shared_ptr<AnalysisParameter> AnalysisParameters::getParameter(string name)
{
	auto param = params_.find(name);
	return param != params_.end() ? param->second : shared_ptr<AnalysisParameter>{};
}

const vector<double> AnalysisParameter::createValues(double lb, double ub, double step )
{
	vector<double> output;
	int dim=(int)((ub-lb)/step);
	output.reserve(dim);
	
	for (int i=0;i<dim;++i)
		output.push_back(lb+i*step);
	
	return output;
	
}

const vector<double> AnalysisParameter::createValues(double lb, double ub, int numElems)
{
	vector<double> output;
	double step=(ub-lb)/numElems;
	output.reserve(numElems);
	
	for (int i=0;i<numElems;++i)
		output.push_back(lb+i*step);
	
	return output;	
}

bool  AnalysisParameter::setBounds(double lb, double ub)
{
	if (lb<ub)
	{
		lb_=lb;
		ub_=ub;
		values_.clear();
		return true;
	}
	
	else
		return false;
}

bool  AnalysisParameter::setValues(double lb, double ub, double step )
{
	auto temp=createValues(lb,ub,step);
	
	if (temp.empty())
		return false;
	
	else
	{
		values_=temp;
		return true;
	}
	
}

bool  AnalysisParameter::setValues(double lb, double ub, int numElems)
{
	auto temp=createValues(lb,ub, numElems);
	
	if (temp.empty())
		return false;
	
	else
	{
		values_=temp;
		return true;
	}
}

bool  AnalysisParameter::setValues(const vector<double>& values)
{
	if (values.empty())
		return false;
	
	else
	{
		values_=values;
		return true;
	}
}

bool  AnalysisParameter::appendValues(double lb, double ub, double step )
{
	auto temp=createValues(lb,ub,step);
	
	if (temp.empty())
		return false;
	
	else
	{
		values_.reserve(values_.size()+temp.size());
		values_.insert(values_.end(), temp.begin(), temp.end());
		return true;
	}
}

bool  AnalysisParameter::appendValues(double lb, double ub, int numElems)
{
	auto temp=createValues(lb,ub,numElems);
	
	if (temp.empty())
		return false;
	
	else
	{
		values_.reserve(values_.size()+temp.size());
		values_.insert(values_.end(), temp.begin(), temp.end());
		return true;
	}
}

bool  AnalysisParameter::appendValues(const vector<double>& values)
{
	if (values.empty())
		return false;
	
	else
	{
		values_.reserve(values_.size()+values.size());
		values_.insert(values_.end(), values.begin(), values.end());
		return true;
	}
}