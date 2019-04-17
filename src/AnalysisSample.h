#pragma once
#include <vector>
#include <string>

namespace AnalysisGenerator
{
	class SamplesSet;
	class Sample
	{
	public:
		friend class AnalysisGenerator::AnalysisParametersBlock;
		friend class AnalysisGenerator::SamplesSet;

	private:
		
		Sample(const std::vector<double>& values)
		{
			values_.assign(values.begin(), values.end());
			return;
		}

		bool setValue(double value,int index)
		{
			if (index < 0 || index >= values_.size())
				return false;

			values_[index] = value;
			return true;
		}

		std::vector<double> values_;
	};

	class SamplesSet
	{
		friend class AnalysisParametersBlock;
	public:
		SamplesSet()
		{
			samples_ = std::vector<std::shared_ptr<Sample>>();
		}
		size_t dim() {return samples_.size();}
		void capacity(size_t dim) { samples_.reserve(dim); }
		
	private:

		bool add(std::shared_ptr<Sample> sample, int pos)
		{
			if (pos >= samples_.size())
				samples_.resize(pos+1);

			samples_.insert(std::begin(samples_) + pos, sample);

			return true;
		}

		bool add(std::shared_ptr<Sample> sample)
		{
			samples_.push_back(sample);
			return true;
		}

		bool add(std::vector<double> sample)
		{
			auto temp = new Sample(sample);
			std::shared_ptr<Sample> tt;
			tt.reset(temp);
			samples_.push_back(tt);
			return true;
		}

		/*bool setValue(double value, int index, int pos)
		{
			if (index < 0 || index >= samples_.size())
				return false;

			samples_[index]-> = value;
		}*/

		std::shared_ptr<Sample> get(int i)
		{
			if (i >= samples_.size())
				return {};
			else
				return samples_[i];
		}

		std::vector<std::shared_ptr<Sample>> samples_;
		//int numElems_{ 0 };

	};
}