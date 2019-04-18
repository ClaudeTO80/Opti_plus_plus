#include "FullFactorial.h"
#include <algorithm>
#include <numeric>
#include <fstream>

using namespace std;
using namespace AnalysisGenerator;

bool FullFactorial::generateIndicesMatrix()
{
	int numVars = (int)levels_.size();
	int currLevel = 0;

	auto numSamples = accumulate(begin(levels_), end(levels_), 1, std::multiplies<int>());

	matrixIndices_.clear();
	matrixIndices_.reserve(numSamples);
	for (int i = 0; i < numSamples; ++i)
	{
		vector<int> currSample;
		currSample.reserve(numVars);
		currSample.assign(numVars, 0);
		matrixIndices_.push_back(currSample);
	}

	currLevel = numVars - 1;
	int locNumSamples = numSamples;
	auto myvector = levels_;
	std::reverse(myvector.begin(), myvector.end());

	for_each(myvector.begin(), myvector.end(), [&](int curr)
	{
		locNumSamples /= curr;
		int pos = 0;
		for (int i = 0; i < numSamples; ++i)
		{
			matrixIndices_[i][currLevel] = pos++ / locNumSamples;
			if ((pos / locNumSamples) == curr)
				pos = 0;
		}
		--currLevel;
	});

	return true;
}

bool FullFactorial::generate()
{
	auto params=block_->getParameters();

	for (auto& curr : params)
	{
		auto temp = genopts_.getOption(curr->name());
		if (temp.get())
			levels_.push_back(temp->value<int>());
		else
			levels_.push_back((int)curr->values().size());
	}

	int numVars = (int)levels_.size();
	generateIndicesMatrix();

	int numSamples = (int)matrixIndices_.size();
	vector<vector<double>> values;
	values.reserve(numVars);
	for (int i = 0; i < numVars; ++i)
	{
		auto currParam = params[i];
		vector<double> currVar;
		currVar.reserve(levels_[i]);

		if (currParam->values().empty())
		{
			auto min = currParam->lb();// bounds_[i].first;
			auto max = currParam->ub();//bounds_[i].second;
			int numDiscr = levels_[i];
			double step = (max - min) / (numDiscr - 1);

			for (int j = 0; j < numDiscr; ++j)
				currVar.push_back(min + step * j);
		}
		else
			currVar = currParam->values();

		values.push_back(currVar);
	}

	matrix_.clear();
	matrix_.reserve(numSamples);

	for (int i = 0; i < numSamples; ++i)
	{
		vector<double> currSample;
		currSample.reserve(numVars);
		auto currIndices = matrixIndices_[i];
		for (int j = 0; j < numVars; ++j)
			currSample.push_back(values[j][currIndices[j]]);

		matrix_.push_back(currSample);
	}

	return true;
}

void FullFactorial::setLevels(const std::vector<int>& levels)
{ 
	levels_ = levels; 
	return;
}

void FullFactorial::dumpIndicesMatrix(ostream& os, string separator)
{
	if (matrixIndices_.size() == 0)
		return;

	int numSamples = (int)matrixIndices_.size();
	int numVars = (int)matrixIndices_[0].size();

	for (int i = 0; i < numSamples; ++i)
	{
		for (int j = 0; j < numVars; ++j)
			os << matrixIndices_[i][j] << separator.c_str();

		os << endl;
	}

	return;
}

void FullFactorial::dumpIndicesMatrix(	const string& fileName,
												ios_base::openmode mode, 
												string separator)
{
	ofstream ofs(fileName, mode);
	dumpIndicesMatrix(ofs, separator);
	ofs.close();
	return;
}