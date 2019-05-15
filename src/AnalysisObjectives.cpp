#include "AnalysisObjectives.h"

using namespace std;
using namespace AnalysisGenerator;

AnalysisObjective::AnalysisObjective(std::string name, ObjDir dir) : name_(name), dir_(dir) {}

shared_ptr<AnalysisObjective> AnalysisObjectiveCreator::createObjective(const std::string& name, AnalysisObjective::ObjDir dir)
{
	if (name.empty())
		return {};

	else
		return std::shared_ptr<AnalysisObjective>(new AnalysisObjective(name, dir));
}

std::shared_ptr<AnalysisObjective> AnalysisObjectives::addObjective(shared_ptr<AnalysisObjective>& obj)
{
	if (obj.get())
	{
		objsVect_.push_back(obj);
		objs_.insert(make_pair(obj->name(), obj));
		pos_.insert(make_pair(obj->name(), (int)objsVect_.size() - 1));
	}
		
	return obj;
}

std::shared_ptr<AnalysisObjective> AnalysisObjectives::addObjective(std::string name, AnalysisObjective::ObjDir dir)
{
	auto temp = AnalysisObjectiveCreator::createObjective(name, dir);
	return addObjective(temp);
}
