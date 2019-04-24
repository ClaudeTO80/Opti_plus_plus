#include "AnalysisParametersBlock.h"

using namespace std;
using namespace AnalysisGenerator;

shared_ptr<Sample> AnalysisParametersBlock::getSample(int i)
{
	return samples_.get(i);
}

std::shared_ptr<Sample> AnalysisParametersBlock::getSampleObjectives(int i)
{
	return samplesObjs_.get(i);
}

std::shared_ptr<Sample> AnalysisParametersBlock::getSampleConstraints(int i)
{
	return samplesConstr_.get(i);
}

double AnalysisParametersBlock::getSampleConstraints(int indSample, int indConstr)
{
	if (indSample >= (int)samplesConstr_.dim() ||
		indConstr >= (int)samplesConstr_.get(indSample)->values_.size())
		return -1e30;

	return samplesConstr_.get(indSample)->values_[indConstr];
}

bool AnalysisParametersBlock::addSample(shared_ptr<Sample> sample)
{
	return samples_.add(sample);
}

bool AnalysisParametersBlock::addSamples(const vector<shared_ptr<Sample>>& samples)
{
	for_each(samples.begin(), samples.end(), [&](const shared_ptr<Sample>& curr)
	{
		samples_.add(curr);
	});

	return true;
}

bool AnalysisParametersBlock::addParameter(shared_ptr<AnalysisParameter> param)
{
	return params_.addParameter(param).get();
}

shared_ptr<AnalysisParameter> AnalysisParametersBlock::addParameter(string name, double lb, double ub)
{
	return params_.addParameter(name, lb,ub);
}

shared_ptr<AnalysisParameter> AnalysisParametersBlock::addParameter(string name, const vector<double>& values)
{
	return params_.addParameter(name, values);
}

shared_ptr<AnalysisParameter> AnalysisParametersBlock::addParameter(string name, double lb, double ub, int dim)
{
	return params_.addParameter(name, lb, ub, dim);
}

shared_ptr<AnalysisParameter> AnalysisParametersBlock::addParameter(string name, const vector<double>& values, int dim)
{
	return params_.addParameter(name, values, dim);
}

shared_ptr<AnalysisObjective> AnalysisParametersBlock::addObjective(string name, AnalysisObjective::ObjDir dir)
{
	return objs_.addObjective(name, dir);
}

std::shared_ptr<AnalysisConstraint> AnalysisParametersBlock::addConstraint(std::string name, double lb, double ub)
{
	return constr_.addConstraint(name, lb, ub);
}

std::shared_ptr<AnalysisConstraint> AnalysisParametersBlock::addConstraint(std::string name, AnalysisConstraint::ConstrType type, double value)
{
	return constr_.addConstraint(name, type, value);
}

std::shared_ptr<AnalysisConstraint> AnalysisParametersBlock::addConstraint(std::string name, std::vector<double> values)
{
	return constr_.addConstraint(name, values);
}

const vector<shared_ptr<AnalysisParameter>>& AnalysisParametersBlock::getParameters() { return params_.getParameters(); }
const vector<shared_ptr<AnalysisObjective>>& AnalysisParametersBlock::getObjectives() { return objs_.getObjectives(); }
const vector<shared_ptr<AnalysisConstraint>>& AnalysisParametersBlock::getConstraints() { return constr_.getConstraints(); }

bool AnalysisParametersBlock::setObjective(string name, double value,int index)
{
	auto pos=objs_.getIndex(name);

	if (pos == -1)
		return false;

	auto sample = samplesObjs_.get(index);
	return sample->setValue(value, pos);
}

bool AnalysisParametersBlock::setConstraint(string name, double value, int index)
{
	auto pos = constr_.getIndex(name);

	if (pos == -1)
		return false;

	auto sample = samplesConstr_.get(index);
	return sample->setValue(value, pos);
}

const double AnalysisParametersBlock::getValue(string name,int pos)
{
	int index=params_.findElement(name);

	if (index < 0)
		return -1e30;

	auto sample = samples_.get(pos);
	if (!sample.get())
		return -1e30;

	if (index >= (int)sample->values_.size())
		return -1e30;

	return sample->values_[index];
}

size_t AnalysisParametersBlock::getNumSamples() { return samples_.dim(); }

bool AnalysisParametersBlock::addSample(const vector<double>& value)
{ 
	auto temp = new Sample(value);
	shared_ptr<Sample> tt;
	tt.reset(temp);
	auto ret=samples_.add(tt);

	if (ret)
	{
		vector<double> currObjs;
		currObjs.reserve(objs_.dim());

		for (int i = 0; i < (int)objs_.dim(); ++i)
		{
			auto dir = objs_.get(i)->dir();
			if (dir == AnalysisObjective::MIN_)
				currObjs.push_back(1e30);

			if (dir == AnalysisObjective::MAX_ || dir == AnalysisObjective::TARGET_)
				currObjs.push_back(-1e30);
		}

		vector<double> currConstr;
		currConstr.reserve(constr_.dim());

		for (int i = 0; i < (int)constr_.dim(); ++i)
			currConstr.push_back(0);

		samplesObjs_.add(shared_ptr<Sample>(new Sample(currObjs)));
		samplesConstr_.add(shared_ptr<Sample>(new Sample(currConstr)));

		feasibile_.push_back(true);
		vector<bool> temp;
		temp.resize(constr_.dim());
		fill(temp.begin(), temp.end(), true);
		satisfied_.push_back(temp);
	}
	return ret;
}

unsigned int AnalysisParametersBlock::addSamples(const vector<vector<double>>& values)
{ 
	unsigned int num= 0;
	samples_.capacity(values.size());
	samplesObjs_.capacity(values.size());
	for_each(values.begin(), values.end(), [&](const vector<double>& value)
	{
		num += (int)addSample(value);
	});

	return num;
}

bool AnalysisParametersBlock::dumpSamples(	const string& fileName,
											int opts,
											bool headers,
											ios_base::openmode mode,
											string separator)
{
	ofstream ofs(fileName, mode);

	if (!ofs.is_open())
		return false;

	int numSamples = (int)samples_.dim();
	auto params = params_.getParameters();
	int numVars = (int)params.size();

	auto objs = objs_.getObjectives();
	int numObjs = (int)objs.size();

	auto constrs = constr_.getConstraints();
	int numConstr = (int)constrs.size();

	bool feasibileOnly	= !opts && (opts & OPTIPP_DUMP_FEAS);
	bool paretoOnly		= !opts && (opts & OPTIPP_DUMP_PARETO);

	if (paretoOnly)
		evalParetoFront();

	if (headers)
	{
		ofs << "SampleIndex" << separator;

		for (auto& param: params)
			ofs << param->name() << separator;

		for (auto& param : objs)
			ofs << param->name() << separator;

		for (auto& param : constrs)
			ofs << param->name() << separator;

		ofs << endl;
	}

	for (int i = 0; i < numSamples; ++i)
	{
		if (paretoOnly && find(paretoSols_.begin(), paretoSols_.end(), i) == paretoSols_.end())
			continue;

		if (!feasibileOnly || feasibile_[i])
		{
			ofs << to_string(i+1) << separator;
			auto currSample = samples_.get(i);
			for (int j = 0; j < numVars; ++j)
				ofs << currSample->values_[j] << separator;

			auto currObj = samplesObjs_.get(i);
			for (int j = 0; j < numObjs; ++j)
				ofs << currObj->values_[j] << separator;

			auto currConstr = samplesConstr_.get(i);
			for (int j = 0; j < numConstr; ++j)
				ofs << currConstr->values_[j] << separator;

			ofs << endl;
		}
	}

	return true;
}


	