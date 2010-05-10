#pragma once
#ifndef INCLUDED_MORNING_MACROS_H
#define INCLUDED_MORNING_MACROS_H

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

#define STEP(stepId, classType, methodName) \
   struct methodName##Step {  \
      typedef classType Type; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this); \
			StepMap().GetInstance().AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap().GetInstance().RemoveStep(stepId);   \
      }  \
   } methodName##Step;

#define STEP1(stepId, classType, methodName, p1) \
   struct methodName##Step {  \
      typedef classType Type; \
      typedef p1 P1; \
      methodName##Step()  \
      {  \
      StepDefinition *functionBase= new StepDefinition(#methodName, &classType::methodName, this, 1); \
         StepMap().GetInstance().AddStep(stepId, functionBase);   \
      }  \
		~methodName##Step()  \
      {  \
         StepMap().GetInstance().RemoveStep(stepId);   \
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
         StepMap().GetInstance().AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap().GetInstance().RemoveStep(stepId);   \
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
         StepMap().GetInstance().AddStep(stepId, functionBase);   \
      }  \
      ~methodName##Step()  \
      {  \
         StepMap().GetInstance().RemoveStep(stepId);   \
      }  \
   } methodName##Step;

} //namespace enlighten

#endif //INCLUDED_MORNING_MACROS_H