#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

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
		const std::string& name() { return name_; }
		
		ObjDir dir() { return dir_; }
		

	private:

		friend class AnalysisObjectiveCreator;
		AnalysisObjective(std::string name, ObjDir dir);// : name_(name), dir_(dir) {}
		std::string name_{ "" };		/**< Name of objective. It must be a non empty string @since 0.1.0*/
		ObjDir dir_{ MIN_ };			/**< Direction of objective. @since 0.1.0*/
	};

	class AnalysisObjectiveCreator
	{
	public:
		static std::shared_ptr<AnalysisObjective> createObjective(const std::string& name, AnalysisObjective::ObjDir dir);
		static std::shared_ptr<AnalysisObjective> createObjective(const std::shared_ptr<AnalysisObjective>& obj)
		{
			return createObjective(obj->name(), obj->dir());
		}
	};

	class AnalysisObjectives
	{
	public:
				
		AnalysisObjectives() {}
		size_t dim() 
		{	
			return objsVect_.size();
		}

		std::string getName(int index)
		{
			
			if (index >= (int)objsVect_.size() || index<0)
				return "";

			return get(index)->name();
		}

		std::shared_ptr<AnalysisObjective> get(int index)
		{

			if (index >= (int)objsVect_.size() || index < 0)
				return {};

			return objsVect_[index];
		}

		int getIndex(std::string name)
		{
			auto temp = pos_.find(name);

			if (temp == pos_.end())
				return -1;

			return temp->second;
		}

		const std::vector<std::shared_ptr<AnalysisObjective>>& getObjectives() { return objsVect_; }
		
		AnalysisObjectives clone()
		{
			AnalysisObjectives output;
			std::for_each(objsVect_.begin(), objsVect_.end(), [&](const std::shared_ptr<AnalysisObjective>& curr)
			{
				output.addObjective(AnalysisObjectiveCreator::createObjective(curr));
			});

			return output;
		}

	private:
		
		friend class AnalysisParametersBlock;

		std::shared_ptr<AnalysisObjective> addObjective(std::shared_ptr<AnalysisObjective>& obj);

		std::shared_ptr<AnalysisObjective> addObjective(std::string name, AnalysisObjective::ObjDir dir);

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

