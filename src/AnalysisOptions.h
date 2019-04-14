#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <iostream>
#include <sstream>

#include "AnGenUtils.h"

namespace AnalysisGenerator
{
	class GeneratorOption
	{
	public:
		void value(std::string value) { value_ = value; }
		template<
			typename T, //real type
			typename = typename std::enable_if_t<std::is_arithmetic_v<T> || std::is_literal_type_v<T>> >
		void value(T value) { value_ = Utils::Stringify(value); }
		template<
			typename T, //real type
			typename = typename std::enable_if_t<std::is_arithmetic_v<T> || std::is_literal_type_v<T>> >
		void value(std::vector<T> value) { value_ = Utils::Stringify(value); }
		std::string asString() { return value_; };
		

		template<
			typename T,
			typename = typename std::enable_if_t<std::is_literal_type_v<T> || std::is_arithmetic_v<T>>>
		T value() 
		{ 
			std::stringstream ss(value_);
			T t;
			ss >> t;
			return t;

			/*if (std::is_same_v<T, double>)
				return std::stod(value_);
		
			if (std::is_same_v<T, float>)
				return std::stof(value_);

			if (std::is_same_v<T, int>)
				return std::stoi(value_);*/

			//if (std::is_same_v<T, std::string>)
			//	return value_;
		};

		//template<
		//	typename T, //real type
		//	typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
		//	T value()
		//{
		//	if (std::is_same_v<T, double>)
		//		return std::stod(value_);

		//	if (std::is_same_v<T, float>)
		//		return std::stof(value_);

		//	if (std::is_same_v<T, int>)
		//		return std::stoi(value_);

		//	/*if (std::is_same_v<T, std::string>)
		//		return value_;*/
		//};
		
	private:
		friend class GeneratorOptions;

		GeneratorOption(std::string name, const std::string& def)
		{
			name_ = name;
			value_ = def;
		}

		GeneratorOption(std::string name)
		{
			name_ = name;
			value_ = "";
		}

		std::string value_;
		std::string name_;

	};

	class GeneratorOptions
	{
	public:


		GeneratorOptions()
		{
		}

		const std::shared_ptr <GeneratorOption>& addOption(std::string name, std::string value)
		{
			GeneratorOption* opt = new GeneratorOption(name,value);
			std::shared_ptr<GeneratorOption> ptr;
			ptr.reset(opt);
			opts_.insert(std::pair(name, ptr));
			return opts_.find(name)->second;
		}

		const std::shared_ptr <GeneratorOption>& addOption(std::string name, int value)
		{
			return addOption(name, std::to_string(value));
		}

		const std::shared_ptr <GeneratorOption>& addOption(std::string name, double value)
		{
			return addOption(name, std::to_string(value));
		}

		const std::shared_ptr <GeneratorOption>& addOption(std::string name, float value)
		{
			return addOption(name, std::to_string(value));
		}

		bool hasOption(std::string name) { return opts_.find(name) == opts_.end(); }
		const std::shared_ptr <GeneratorOption>& getOption(std::string name) { return opts_.find(name)->second; }
	//private:
		std::map<std::string, std::shared_ptr<GeneratorOption>> opts_;
		std::map<std::string, std::string> names_;
	};
}