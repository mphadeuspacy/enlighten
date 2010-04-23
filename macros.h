#pragma once

namespace enlighten {

#define GIVEN \
   consumer.SetThisPointer(this, typeid(*this).name()); consumer

#define WHEN \
   consumer.SetThisPointer(this, typeid(*this).name()); consumer

#define THEN \
   consumer.SetThisPointer(this, typeid(*this).name()); consumer

#define AND \
   consumer.SetThisPointer(this, typeid(*this).name()); consumer

#define OK ok   

#define IT_SHOULD_THROW consumer.ItShouldThrow()

#define STEP(stepId, classType, methodName) \
   struct methodName##Step {  \
      typedef classType Type; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this); \
			StepMap::AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap::RemoveStep(stepId);   \
      }  \
   } methodName##Step;

#define STEP1(stepId, classType, methodName, p1) \
   struct methodName##Step {  \
      typedef classType Type; \
      typedef p1 P1; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this, 1); \
         StepMap::AddStep(stepId, functionBase);   \
      }  \
		~methodName##Step()  \
      {  \
         StepMap::RemoveStep(stepId);   \
      }  \
   } methodName##Step;

#define STEP2(stepId, classType, methodName, p1, p2) \
   struct methodName##Step {  \
      typedef classType Type; \
      typedef p1 P1; \
      typedef p2 P2; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this, 1, 2); \
         StepMap::AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap::RemoveStep(stepId);   \
      }  \
   } methodName##Step;

#define STEP3(stepId, classType, methodName, p1, p2, p3) \
   struct methodName##Step {  \
      typedef classType Type; \
      typedef p1 P1; \
      typedef p2 P2; \
      typedef p3 P3; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this, 1, 2, 3); \
         StepMap::AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap::RemoveStep(stepId);   \
      }  \
   } methodName##Step;

} //namespace enlighten