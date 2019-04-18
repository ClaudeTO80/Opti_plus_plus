#pragma once
#include "AnalysisParametersBlock.h"

using namespace std;
using namespace AnalysisGenerator;

shared_ptr<Sample> AnalysisParametersBlock::getSample(int i)
{
	return samples_.get(i);
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

const vector<shared_ptr<AnalysisParameter>>& AnalysisParametersBlock::getParameters() { return params_.getParameters(); }

bool AnalysisParametersBlock::setObjective(string name, double value,int index)
{
	auto pos=objs_.getIndex(name);

	if (pos == -1)
		return false;

	auto sample = samplesObjs_.get(index);
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

	if (index >= sample->values_.size())
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

		for (int i = 0; i < objs_.dim(); ++i)
		{
			auto dir = objs_.get(i)->dir();
			if (dir == AnalysisObjective::MIN_)
				currObjs.push_back(1e30);

			if (dir == AnalysisObjective::MAX_ || dir == AnalysisObjective::TARGET_)
				currObjs.push_back(-1e30);
		}

		/*auto temp = new Sample(currObjs);
		shared_ptr<Sample> tt(new Sample(currObjs));
		tt.reset(temp);*/
		samplesObjs_.add(shared_ptr<Sample>(new Sample(currObjs)));
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
											bool headers,
											ios_base::openmode mode,
											string separator)
{
	ofstream ofs(fileName, mode);

	if (!ofs.is_open())
		return false;

	int numSamples = (int)samples_.dim();
	/*auto params = params_.getParameters();*/
	auto params = params_.getParameters();
	int numVars = (int)params.size();

	auto objs = objs_.getObjectives();
	int numObjs = (int)objs.size();

	if (headers)
	{
		for (auto& param: params)
			ofs << param->name() << separator;

		for (auto& param : objs)
			ofs << param->name() << separator;

		ofs << endl;
	}

	for (int i = 0; i < numSamples; ++i)
	{
		auto currSample = samples_.get(i);
		for (int j = 0; j < numVars; ++j)
			ofs << currSample->values_[j] << separator;
				
		auto currObj = samplesObjs_.get(i);
		for (int j = 0; j < numObjs; ++j)
			ofs << currObj->values_[j] << separator;

		ofs << endl;
	}

	return true;
}


	