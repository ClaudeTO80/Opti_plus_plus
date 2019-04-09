#pragma once
#include <vector>
#include <ostream>

#include "GenericGenerator.h"

namespace AnalysisGenerator
{
	class DoeGenerator : public Generator
	{
	public:

		DoeGenerator(const std::vector<std::pair<double, double>>& bounds) : bounds_(bounds) {};
		DoeGenerator() {}
		void setBounds(const std::vector<std::pair<double, double>>& bounds) { bounds_ = bounds; }
		void addBound(const std::pair<double, double>& bounds)
		{
			bounds_.push_back(bounds);
		}

		std::vector<std::vector<double>> getMatrix();
		

		virtual bool generate() = 0;
		bool randomSorting() { return randomSorting_; }
		void randomSorting(bool value) { randomSorting_=value; }

	protected:
		bool randomSorting_{ false };
		std::vector<std::pair<double, double>> bounds_;
		
	};

	/*class ActiveDoeGenerator : public DoeGenerator
	{
	public:
		ActiveDoeGenerator(const std::vector<std::pair<double, double>>& bounds) : bounds_(bounds) {};
		ActiveDoeGenerator() {}
		void setBounds(const std::vector<std::pair<double, double>>& bounds) { bounds_ = bounds; }
		void addBound(const std::pair<double, double>& bounds)
		{
			bounds_.push_back(bounds);
		}
	protected:
		std::vector<std::pair<double, double>> bounds_;
	};*/
}