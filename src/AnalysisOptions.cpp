#include "AnalysisOptions.h"

using namespace AnalysisGenerator;
		
void GeneratorOption::value(std::string value) { value_ = value; }
std::string GeneratorOption::asString() { return value_; };
				
GeneratorOption::GeneratorOption(std::string name, const std::string& def)
{
	name_ = name;
	value_ = def;
}

GeneratorOption::GeneratorOption(std::string name)
{
	name_ = name;
	value_ = "";
}


GeneratorOptions::GeneratorOptions(){}

const std::shared_ptr <GeneratorOption>& GeneratorOptions::addOption(std::string name, std::string value)
{
	GeneratorOption* opt = new GeneratorOption(name,value);
	std::shared_ptr<GeneratorOption> ptr(opt);
	//ptr.reset(opt);
	opts_.insert(make_pair(name, ptr));
	names_.push_back(name);
	return opts_.find(name)->second;
}

const std::shared_ptr <GeneratorOption>& GeneratorOptions::addOption(std::string name, int value)
{
	return addOption(name, std::to_string(value));
}

const std::shared_ptr <GeneratorOption>& GeneratorOptions::addOption(std::string name, double value)
{
	return addOption(name, std::to_string(value));
}

const std::shared_ptr <GeneratorOption>& GeneratorOptions::addOption(std::string name, float value)
{
	return addOption(name, std::to_string(value));
}

bool GeneratorOptions::hasOption(std::string name) { return opts_.find(name) == opts_.end(); }
const std::shared_ptr <GeneratorOption>& GeneratorOptions::getOption(std::string name) { return opts_.find(name)->second; }
	
