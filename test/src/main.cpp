#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "AnalysisGenerator.h"
#include "AnalysisParameters.h"

using namespace std;
using namespace AnalysisGenerator;

int main()
{
	vector<int> levels;
	levels.push_back(2);
	levels.push_back(4);
	levels.push_back(3);

	vector<pair<double,double>> bounds;
	bounds.push_back(make_pair(0, 1));
	bounds.push_back(make_pair(-1, 1));
	bounds.push_back(make_pair(0, 10));

	AnalysisParameters params;

	params.addParameter("x", 0, 1);
	params.addParameter("y", -1, 1);
	params.addParameter("z", 0, 10);

	FullFactorial ff();
	Model model;
	//FullFactorialDoeGenerator sgdg(bounds);
	//sgdg.setLevels(levels);
	//auto ret=sgdg.generateMatrix();
	//auto matrix = sgdg.getMatrix();

	//sgdg.dumpIndicesMatrix(cout);
	//cout << endl;
	//sgdg.dumpMatrix(cout);
	
	/*LatinHypercube latHyper(bounds);
	latHyper.setNumSamples(10);
	auto ret = latHyper.generateMatrix();
	auto matrix = latHyper.getMatrix();

	latHyper.dumpIndicesMatrix(cout);
	cout << endl;
	latHyper.dumpMatrix(cout);*/

	RobustDesignOptions rdo = RobustDesignOptions();
	return 0;
}
