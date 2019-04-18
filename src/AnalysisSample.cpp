#include "AnalysisSample.h"

using namespace std;
using namespace AnalysisGenerator;

Sample::Sample(const vector<double>& values)
{
	values_.assign(values.begin(), values.end());
	return;
}

bool Sample::setValue(double value,int index)
{
	if (index < 0 || index >= (int)values_.size())
		return false;

	values_[index] = value;
	return true;
}

SamplesSet::SamplesSet()
{
	samples_ = vector<shared_ptr<Sample>>();
}

size_t SamplesSet::dim() {return samples_.size();}
void SamplesSet::capacity(size_t dim) { samples_.reserve(dim); }
	
bool SamplesSet::add(shared_ptr<Sample> sample, int pos)
{
	if (pos >= (int)samples_.size())
		samples_.resize(pos+1);

	samples_.insert(begin(samples_) + pos, sample);

	return true;
}

bool SamplesSet::add(shared_ptr<Sample> sample)
{
	samples_.push_back(sample);
	return true;
}

bool SamplesSet::add(vector<double> sample)
{
	auto temp = new Sample(sample);
	shared_ptr<Sample> tt;
	tt.reset(temp);
	samples_.push_back(tt);
	return true;
}

/*bool setValue(double value, int index, int pos)
{
	if (index < 0 || index >= samples_.size())
		return false;

	samples_[index]-> = value;
}*/

shared_ptr<Sample> SamplesSet::get(int i)
{
	if (i >= (int)samples_.size())
		return {};
	else
		return samples_[i];
}
		
	
