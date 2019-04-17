#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace AnalysisGenerator
{
	class AnalysisParametersBlock;
	class AnalysisObjectiveCreator;

	/**
	@brief 
	@details
	@since 0.1.0
	*/
	class AnalysisObjective
	{
	public:
		enum ObjDir {MIN_=-1,MAX_=1,TARGET_=2};
		/**
		@brief Returns name of objective
		@details Returns name of objective. It must be a string with at least 1 character
		@return name: name of objective
		@since 0.1.0
		*/
		std::string name() { return name_; }
		
		

	private:

		friend class AnalysisObjectiveCreator;
		AnalysisObjective(std::string name, ObjDir dir) : name_(name), dir_(dir) {}
		std::string name_{ "" };		/**< Name of objective. It must be a non empty string @since 0.1.0*/
		ObjDir dir_{ MIN_ };			/**< Direction of objective. @since 0.1.0*/
	};

	class AnalysisObjectiveCreator
	{
	public:
		static std::shared_ptr<AnalysisObjective> createObjective(const std::string& name, AnalysisObjective::ObjDir dir)
		{
			if (name.empty())
				return {};

			else
				return std::shared_ptr<AnalysisObjective>(new AnalysisObjective(name, dir));
		}
	};

	class AnalysisObjectives
	{
	public:
				
		AnalysisObjectives() {}
		int dim() {	return objsVect_.size();}
	private:
		
		friend class AnalysisParametersBlock;

		std::shared_ptr<AnalysisObjective> addObjective(std::shared_ptr<AnalysisObjective>& obj);

		std::shared_ptr<AnalysisObjective> addObjective(std::string name, AnalysisObjective::ObjDir dir)
		{
			return addObjective(AnalysisObjectiveCreator::createObjective(name, dir));
		}

		const int findElement(std::string name)
		{
			auto temp = pos_.find(name);

			if (temp == pos_.end())
				return -1;

			else
				return temp->second;
		}

		std::vector<std::shared_ptr<AnalysisObjective>> objsVect_;
		std::map<std::string, std::shared_ptr<AnalysisObjective>> objs_;
		std::map<std::string, int> pos_;

	};
}

