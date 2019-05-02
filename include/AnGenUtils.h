#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <math.h>  
#include <numeric> 

namespace AnalysisGenerator::Utils
{
	template<
		typename T,
		typename = typename std::enable_if_t<std::is_arithmetic<T>::value || std::is_literal_type<T>::value>>
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
		typename = typename std::enable_if_t<std::is_arithmetic<T>::value, T>>
	std::string Stringify(T value)
	{
		return std::to_string(value);
	}

	std::string Stringify(const std::string& value);

	class StatisticTools
	{

	public:
		static double CorrCoeff(std::vector<double> x, std::vector<double> y)
		{
			int dim = (int)x.size();
			if (x.size() != y.size())
				return -2;

			double num1 = 0;
			double num2 = 0;
			double num3 = 0;
			double num = 0;

			double den1 = 0;
			double den2 = 0;
			double den3 = 0;
			double den4 = 0;
			double den = 0;

			for (int i = 0; i < dim; ++i)
			{
				num1 += x[i] * y[i];
				num2 += x[i];
				num3 += y[i];

				den1 += x[i] * x[i];
				den3 += y[i] * y[i];
			}

			den2 = num2 * num2;
			den4 = num3 * num3;

			num = dim * num1 - (num2*num3);
			den = sqrt(dim*den1 - den2)*sqrt(dim*den3 - den4);

			if (den != 0)
				return num / den;

			else
				return -2;

		}

		static double mean(std::vector<double> x)
		{
			return std::accumulate(x.begin(), x.end(), 0.0) / x.size();
		}

		static double variance(std::vector<double> x)
		{
			double result = 0;
			double meanValue = mean(x);

			for (double number : x)
				result += pow(number - meanValue,2);

			return result / (x.size() - 1);
		}

		static double stdVariance(std::vector<double> x)
		{
			return sqrt(variance(x));
		}
	};
}