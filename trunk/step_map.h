#pragma once

#include <map>

#include <step_definition.h>

namespace enlighten {
	class StepMap {

	static std::map<std::string, StepDefinition*> stepMap;

	public:
		static void AddStep(const std::string &stepId, StepDefinition *func)
		{
			stepMap[stepId]= func;
		}

		static void RemoveStep(const std::string &stepId)
		{
         delete stepMap[stepId];
			stepMap.erase(stepId);
		}   

		static bool ExistStepDefinition(const std::string &stepId)
		{	
			return stepMap.find(stepId) != stepMap.end();
		}

		static StepDefinition* GetStepDefinition(const std::string &stepId)
		{
			return stepMap[stepId];
		}
	};
	
}