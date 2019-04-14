#pragma once
#include <vector>
#include <string>

namespace AnalysisGenerator
{
	//class AnalysisBlock;
	class Sample
	{
	public:
		friend class AnalysisGenerator::AnalysisParametersBlock;
		

	private:
		
		Sample(const std::vector<double>& values)
		{
			values_.assign(values.begin(), values.end());
			return;
		}

		std::vector<double> values_;
	};

	class SamplesSet
	{
		friend class AnalysisParametersBlock;
	public:
		

	private:
		

		bool add(std::shared_ptr<Sample> sample, int pos)
		{
			if (pos >= numElems_)
				samples_.resize(pos);

			samples_.insert(std::begin(samples_) + pos, sample);

			return true;
		}

		bool add(std::shared_ptr<Sample> sample)
		{
			samples_.push_back(sample);
			return true;
		}

		std::shared_ptr<Sample> get(int i)
		{
			if (i >= numElems_)
				return {};
			else
				return samples_[i];
		}

		std::vector<std::shared_ptr<Sample>> samples_;
		int numElems_{ 0 };

	};
}