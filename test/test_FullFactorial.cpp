#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "Model.h"
#include "AnalysisGenerator.h"
#include "AnalysisParameters.h"
#include "AnalysisConstraints.h"

using namespace std;
using namespace AnalysisGenerator;

int main()
{
	shared_ptr<AnalysisParametersBlock> block= AnalysisParametersBlock::create();

	block->addParameter("x", vector<double>{0, .11, .33, .44, .77, .99, 1});
	block->addParameter("y", -1, 1);
	block->addParameter("z", 0, 10);

	block->addObjective("o1", AnalysisObjective::MIN_);
	block->addObjective("o2", AnalysisObjective::MAX_);

	block->addConstraint("c1", -1, 1);
	block->addConstraint("c2", AnalysisConstraint::LB_,1);

	function<bool(shared_ptr<AnalysisParametersBlock>&, int)> objf = [](shared_ptr<AnalysisParametersBlock>& tempBlock, int index)->bool
	{
		auto x= tempBlock->getValue("x", index);
		auto y= tempBlock->getValue("y", index);
		auto z= tempBlock->getValue("z", index);

		tempBlock->setObjective("o1", x + y, index);
		tempBlock->setObjective("o2", z - y, index);

		tempBlock->setConstraint("c1", x + y, index);
		tempBlock->setConstraint("c2", z - y, index);

		return true;
	};

	shared_ptr<Generator> FF_Generator(new FullFactorial(block));

	FF_Generator->setOption("x", "5");
	FF_Generator->setOption("y", "5");
	FF_Generator->setOption("z", "5");

	Model model(FF_Generator);
	//model.setBlock(block);
	model.setObjf(objf);
	model.run();
	model.dumpSamples(R"(C:\tmp\samples_FF.txt)", 0);// , OPTIPP_DUMP_FEAS | OPTIPP_DUMP_PARETO);
	block->evalCorrCoeff();
	return 0;
}