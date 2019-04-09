#include "LatinHypercube.h"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>

using namespace std;
using namespace AnalysisGenerator;

bool LatinHypercube::generateIndicesMatrix()
{
	int numVars = bounds_.size();
	int locSamples = numSamples_;
	vector<vector<int>> subsets;
	subsets.reserve(numVars);
	matrixIndices_.reserve(numSamples_);
	for (int i = 0; i < numSamples_; ++i)
	{
		vector<int> currSubset;
		currSubset.resize(numSamples_);
		iota(begin(currSubset), end(currSubset), 0);
		subsets.push_back(currSubset);
	}

	for (int i = 0; i < numSamples_; ++i)
	{
		vector<int> currSample;
		currSample.resize(numVars);

		for (int j = 0; j < numVars; ++j)
		{
			vector<int>& currSubset = subsets[j];
			auto v1 = rand() % locSamples;
			currSample[j] = currSubset[v1];
			currSubset.erase(begin(currSubset) + v1);
		}
		--locSamples;
		matrixIndices_.push_back(currSample);
	}

	return true;
}

bool LatinHypercube::generate()
{
	generateIndicesMatrix();
	int numVars = bounds_.size();
	int locSamples = numSamples_;
	vector<vector<double>> tempSamples;
	tempSamples.reserve(numVars);

	for_each(begin(bounds_), end(bounds_), [&](pair<double, double> &curr)
	{
		vector<double> currSample;
		currSample.reserve(numSamples_ + 1);
		double min = curr.first;
		double max = curr.second;
		double step = (max - min) / numSamples_;

		for (int i = 0; i < numSamples_ + 1; ++i)
			currSample.push_back(min + step * i);

		tempSamples.push_back(currSample);
	});

	int i = 0;
	int j = 0;
	matrix_.resize(numSamples_);
	for_each(begin(matrixIndices_), end(matrixIndices_), [&](vector<int> &curr)
	{
		matrix_[i].resize(numVars);
		j = 0;
		for_each(begin(curr), end(curr), [&](int &currIndex)
		{
			matrix_[i][j] = (tempSamples[j][currIndex + 1]+tempSamples[j][currIndex])/2;
			++j;
		});

		++i;
	});

	

	return true;
}

void LatinHypercube::setNumSamples(int numSamples)
{
	numSamples_ = numSamples;
	return;
}

void LatinHypercube::dumpIndicesMatrix(ostream& os,bool headers, string separator)
{
	if (matrixIndices_.size() == 0)
		return;

	int numSamples = matrixIndices_.size();
	int numVars = matrixIndices_[0].size();

	if (headers)
	{
		for (int j = 0; j < numVars; ++j)
		{
			if (j < (int)varNames_.size())
				os << varNames_[j].c_str() << separator.c_str();

			else
				os << "var_" + to_string(j) << separator.c_str();

		}
		os << endl;
	}

	for (int i = 0; i < numSamples; ++i)
	{
		for (int j = 0; j < numVars; ++j)
			os << matrixIndices_[i][j] << separator.c_str();

		os << endl;
	}

	return;
}

void LatinHypercube::dumpIndicesMatrix(	const string& fileName, 
										bool headers,
										ios_base::openmode mode,
										string separator)
{
	ofstream ofs(fileName, mode);
	dumpIndicesMatrix(ofs,headers, separator);
	ofs.close();
	return;
}