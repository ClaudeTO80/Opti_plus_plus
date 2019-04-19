#include <stdio.h>
#include <stdlib.h>
#include <vector>

class StatisticTools
{

public:
	static double CorrCoeff(std::vector<double> x, std::vector<double> y)
	{
		int dim = x.size();
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

};

int main()
{
	std::vector<double> x{ 1,3,2,7,9,11 };
	std::vector<double> y{ 2,4,3,8,10,11};

	auto r=StatisticTools::CorrCoeff(x, y);

	return 0;
}