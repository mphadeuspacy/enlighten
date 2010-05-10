#pragma once

#include <map>

#include <step_definition.h>

namespace enlighten {
	class StepMap 
   {
   	std::map<std::string, StepDefinition*> stepMap;

	public:
      StepMap &GetInstance()
      {
         static StepMap stepMapInstance;
         return stepMapInstance;
      }

		void AddStep(const std::string &stepId, StepDefinition *func)
		{
			stepMap[stepId]= func;
		}

		void RemoveStep(const std::string &stepId)
		{
         delete stepMap[stepId];
			stepMap.erase(stepId);
		}   

		bool ExistStepDefinition(const std::string &stepId)
		{	
			return stepMap.find(stepId) != stepMap.end();
		}

		StepDefinition* GetStepDefinition(const std::string &stepId)
		{
			return stepMap[stepId];
		}
	};
	
}