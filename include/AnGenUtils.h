#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace AnalysisGenerator::Utils
{
	template<
		typename T,
		typename = typename std::enable_if_t<std::is_arithmetic_v<T> || std::is_literal_type_v<T>>>
	std::string Stringify(const std::vector<T>& value)
	{
		std::string out("");
		std::for_each(value.begin(), value.end(),[&](T& curr) 
		{
			if (!out.empty())
				out.append(",");

			out.append(std::to_string(curr));
		});

		return out;
	}

	template<
		typename T,
		typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>>
	std::string Stringify(T value)
	{
		return std::to_string(value);
	}

	std::string Stringify(const std::string& value);
}