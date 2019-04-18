#include "AnalysisConstraints.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using namespace AnalysisGenerator;

string AnalysisConstraint::name() 
{ 
	return name_; 
}
		
AnalysisConstraint::ConstrType AnalysisConstraint::type() 
{ 
	return type_; 
}
		
double AnalysisConstraint::lb() 
{ 
	return lb_; 
}

double AnalysisConstraint::ub() 
{ 
	return ub_;
}

vector<double> AnalysisConstraint::values() 
{ 
	return av_; 
}
		
AnalysisConstraint::AnalysisConstraint(std::string name, double lb, double ub)
{
	if (lb <= ub)
	{
		type_ = AnalysisConstraint::DB_;
		lb_ = lb;
		ub_ = ub;
		av_.clear();
	}
}

AnalysisConstraint::AnalysisConstraint(std::string name, ConstrType type, double value)
{
	if (type == AnalysisConstraint::LB_ || type == AnalysisConstraint::UB_)
	{
		type_ = type;

		if (type == AnalysisConstraint::LB_)
			lb_ = value;

		if (type == AnalysisConstraint::UB_)
			ub_ = value;

		av_.clear();
	}
}

AnalysisConstraint::AnalysisConstraint(std::string name, std::vector<double> values)
{
	type_ = AnalysisConstraint::AV_;
	av_.clear();
	av_.assign(values.begin(), values.end());
}

std::shared_ptr<AnalysisConstraint> AnalysisConstraintCreator::createConstraint(std::string name, double lb, double ub)
{
	return shared_ptr<AnalysisConstraint>(new AnalysisConstraint(name, lb, ub));
}

std::shared_ptr<AnalysisConstraint> AnalysisConstraintCreator::createConstraint(std::string name, AnalysisConstraint::ConstrType type, double value)
{
	return shared_ptr<AnalysisConstraint>(new AnalysisConstraint(name, type, value));
}

std::shared_ptr<AnalysisConstraint> AnalysisConstraintCreator::createConstraint(std::string name, std::vector<double> values)
{
	return shared_ptr<AnalysisConstraint>(new AnalysisConstraint(name, values));
}


std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, double lb, double ub)
{
	auto temp = AnalysisConstraintCreator::createConstraint(name, lb,ub);
	addConstraint(temp);
	return temp;
}

std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value)
{
	auto temp = AnalysisConstraintCreator::createConstraint(name, type,value);
	addConstraint(temp);
	return temp;
}

std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, std::vector<double> values)
{
	
	auto temp= AnalysisConstraintCreator::createConstraint(name, values);
	addConstraint(temp);
	return temp;
}

AnalysisConstraints::AnalysisConstraints() {}
size_t AnalysisConstraints::dim()
{
	return constrVect_.size();
}

string AnalysisConstraints::getName(int index)
{

	if (index >= (int)constrVect_.size() || index < 0)
		return "";

	return get(index)->name();
}

shared_ptr<AnalysisConstraint> AnalysisConstraints::get(int index)
{

	if (index >= (int)constrVect_.size() || index < 0)
		return {};

	return constrVect_[index];
}

int AnalysisConstraints::getIndex(string name)
{
	auto temp = pos_.find(name);

	if (temp == pos_.end())
		return -1;

	return temp->second;
}

const vector<shared_ptr<AnalysisConstraint>>& AnalysisConstraints::getConstraints() { return constrVect_; }
	

void AnalysisConstraints::addConstraint(shared_ptr<AnalysisConstraint>& constr)
{
	constrVect_.push_back(constr);
	constr_.insert(make_pair(constr->name(), constr));
	pos_.insert(make_pair(constr->name(), constrVect_.size() - 1));
	return;
}
												
//std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, double lb, double ub)
//{
//	shared_ptr<AnalysisConstraint> temp
//}
//
//std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value)
//{
//
//}
//
//std::shared_ptr<AnalysisConstraint> AnalysisConstraints::addConstraint(std::string name, std::vector<double> values)
//{
//
//}


const int AnalysisConstraints::findElement(string name)
{
	auto temp = pos_.find(name);

	if (temp == pos_.end())
		return -1;

	else
		return temp->second;
}

