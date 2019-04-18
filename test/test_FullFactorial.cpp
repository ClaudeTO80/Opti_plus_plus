#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "Model.h"
#include "AnalysisGenerator.h"
#include "AnalysisParameters.h"

using namespace std;
using namespace AnalysisGenerator;

int main()
{
	AnalysisParametersBlock block;

	block.addParameter("x", 0, 1);
	block.addParameter("y", -1, 1);
	block.addParameter("z", 0, 10);

	block.addObjective("o1", AnalysisObjective::MIN_);
	block.addObjective("o2", AnalysisObjective::MAX_);
	
	function<bool(shared_ptr<AnalysisParametersBlock>&, int)> objf = [&](shared_ptr<AnalysisParametersBlock>& block, int index)->bool
	{
		auto x=block->getValue("x", index);
		auto y=block->getValue("y", index);
		auto z=block->getValue("z", index);

		block->setObjective("o1", x + y, index);
		block->setObjective("o2", z - y, index);
		return true;
	};
	auto temp = make_shared< AnalysisParametersBlock>(block);
	shared_ptr<Generator> tt(new FullFactorial(temp));
	Model model(tt);
	model.setBlock(temp);
	model.setObjf(objf);
	model.run();
	model.dumpSamples(R"(C:\tmp\samples.txt)");
	return 0;
}