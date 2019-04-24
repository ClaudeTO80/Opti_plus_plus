#include "AnalysisOptions.h"
#include "Optipp_Exceptions.h"

using namespace std;
using namespace AnalysisGenerator;
		
void GeneratorOption::value(string value) { value_ = value; }
string GeneratorOption::asString() { return value_; };
				
GeneratorOption::GeneratorOption(string name, const string& def)
{
	name_ = name;
	value_ = def;
}

GeneratorOption::GeneratorOption(string name)
{
	name_ = name;
	value_ = "";
}


GeneratorOptions::GeneratorOptions(){}

const shared_ptr <GeneratorOption>& GeneratorOptions::addOption(string name, string value)
{
	GeneratorOption* opt = new GeneratorOption(name,value);
	shared_ptr<GeneratorOption> ptr(opt);
	//ptr.reset(opt);
	opts_.insert(make_pair(name, ptr));
	names_.push_back(name);
	return opts_.find(name)->second;
}

const shared_ptr <GeneratorOption>& GeneratorOptions::addOption(string name, int value)
{
	return addOption(name, to_string(value));
}

const shared_ptr <GeneratorOption>& GeneratorOptions::addOption(string name, double value)
{
	return addOption(name, to_string(value));
}

const shared_ptr <GeneratorOption>& GeneratorOptions::addOption(string name, float value)
{
	return addOption(name, to_string(value));
}

bool GeneratorOptions::hasOption(string name) 
{ 
	return opts_.find(name) != opts_.end(); 
}

const shared_ptr <GeneratorOption>& GeneratorOptions::getOption(string name) 
{ 
	if (hasOption(name))
		return opts_.find(name)->second;

	throw Optipp_MissionOptionException("Missing option " +  name);
}
	
