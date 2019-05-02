#include <algorithm>
#include "RobustDesign.h"
#include <random>

using namespace std;
using namespace AnalysisGenerator;

bool RobustDesignGenerator::generate()
{
	int totSamples =numSamples_+1;
	matrix_.reserve(totSamples);
	default_random_engine generator;
	{
		auto curr = basicSample_;
		matrix_.push_back(curr);
		int dim= (int)curr.size();
		vector<normal_distribution<double>> distr;
		distr.reserve(curr.size());
		
		for (int i = 0; i < dim; ++i)
		{
			if (variance_[i])
				distr.push_back(normal_distribution<double>(curr[i], variance_[i]));
			else
				distr.push_back(normal_distribution<double>(curr[i], 1));
		}
		for (int i = 0; i < numSamples_; ++i)
		{
			vector<double> currSample;
			currSample.reserve(dim);
			for (int j = 0; j < dim; ++j)
			{ 
				if (variance_[j])
					currSample.push_back(distr[j](generator));
				else
					currSample.push_back(curr[j]);
				
			}

			matrix_.push_back(currSample);
		}

	}
	//);

	return true;
}