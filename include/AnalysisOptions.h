#pragma once
#include "AnGenUtils.h"
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <iostream>
#include <sstream>



namespace AnalysisGenerator
{
	class GeneratorOption
	{
	public:
		void value(std::string value);
		template<
			typename T, //real type
			typename = typename std::enable_if_t<std::is_arithmetic_v<T> || std::is_literal_type_v<T>> >
		void value(T value) { value_ = CurrUtils::Stringify(value); }
		template<
			typename T, //real type
			typename = typename std::enable_if_t<std::is_arithmetic_v<T> || std::is_literal_type_v<T>> >
		void value(std::vector<T> value) { value_ = CurrUtils::Stringify(value); }
		std::string asString();
		

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

		GeneratorOption(std::string name, const std::string& def);
		GeneratorOption(std::string name);
		std::string value_;
		std::string name_;

	};

	class GeneratorOptions
	{
	public:


		GeneratorOptions();

		const std::shared_ptr <GeneratorOption>& addOption(std::string name, std::string value);
		const std::shared_ptr <GeneratorOption>& addOption(std::string name, int value);
		const std::shared_ptr <GeneratorOption>& addOption(std::string name, double value);
		const std::shared_ptr <GeneratorOption>& addOption(std::string name, float value);
		bool hasOption(std::string name);
		const std::shared_ptr <GeneratorOption>& getOption(std::string name);
		bool setOption(std::string name, std::string value)
		{
			auto temp = opts_.find(name);
			if (temp == opts_.end())
				return false;

			temp->second->value(value);
			return true;
		}

	//private:
		std::map<std::string, std::shared_ptr<GeneratorOption>> opts_;
		std::vector<std::string> names_;
	};
}