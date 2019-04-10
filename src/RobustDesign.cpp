#include <algorithm>
#include "RobustDesign.h"
#include <random>

using namespace std;
using namespace AnalysisGenerator;

bool RobustDesignGenerator::generate()
{
	int totSamples = (int)basicSamples_.size()*(numSamples_ + 1);
	output_.reserve(totSamples);
	default_random_engine generator;
	
	for_each(begin(basicSamples_), end(basicSamples_), [&](vector<double>& curr) 
	{
		output_.push_back(curr);
		int dim= (int)curr.size();
		vector<normal_distribution<double>> distr;
		distr.reserve(basicSamples_[0].size());

		for (int i = 0; i < numSamples_; ++i)
			distr.push_back(normal_distribution<double>(curr[i], variance_[i]));

		for (int i = 0; i < numSamples_; ++i)
		{
			vector<double> currSample;
			currSample.reserve(dim);
			for (int j = 0; j < dim; ++j)
				currSample.push_back(distr[i](generator));

			output_.push_back(currSample);
		}

	});

	return true;
}