#pragma once
#include <vector>
#include <string>

namespace AnalysisGenerator
{
	class SamplesSet;
	class Sample
	{
	public:
		friend class AnalysisParametersBlock;
		friend class SamplesSet;

	private:
		
		Sample(const std::vector<double>& values);
		bool setValue(double value,int index);
		std::vector<double> values_;
	};

	class SamplesSet
	{
		friend class AnalysisParametersBlock;
	public:
		SamplesSet();
		size_t dim();
		void capacity(size_t dim);
		
	private:

		bool add(std::shared_ptr<Sample> sample, int pos);
		bool add(std::shared_ptr<Sample> sample);
		bool add(std::vector<double> sample);
		/*bool setValue(double value, int index, int pos)
		{
			if (index < 0 || index >= samples_.size())
				return false;

			samples_[index]-> = value;
		}*/

		std::shared_ptr<Sample> get(int i);
		std::vector<std::shared_ptr<Sample>> samples_;
		//int numElems_{ 0 };

	};
}