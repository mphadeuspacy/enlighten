#pragma once

#include <vector>
#include <parameter.h>
#include <sstream>

#define CALL_MEMBER_FUNCTION(instance, mem_function) ((instance).*(mem_function))

namespace enlighten {

	struct nulltype {};

	struct StepHolder {      
		virtual bool MatchParameters( std::vector<ParameterBase*> parameters )= 0;
		virtual void Execute( void *instance,  std::vector<ParameterBase*> parameters )= 0;
	};

	template <class FuncType=nulltype, class ClassType=nulltype, class Param1=nulltype, class Param2=nulltype
      , class Param3=nulltype, class Param4=nulltype>
	struct StepHolderImpl;

	//0 arity
	template <typename FuncType, typename ClassType>
	struct StepHolderImpl<FuncType, ClassType> : public StepHolder
	{    
		FuncType f;

		StepHolderImpl(FuncType _f) : f(_f) {}

		void operator()(void *instance)
		{
			//ClassType *inst= reinterpret_cast<ClassType*>(instance);
         ClassType *inst= static_cast<ClassType*>(instance);
			CALL_MEMBER_FUNCTION(*inst, f)();
		}   

		bool MatchParameters( std::vector<ParameterBase*> parameters )
		{
			return parameters.empty();
		}

		void Execute( void *instance, std::vector<ParameterBase*> parameters )
		{
			(*this)(instance);
		}

	};

	//1 arity
	template <typename FuncType, typename ClassType, typename Param1>
	struct StepHolderImpl<FuncType, ClassType, Param1> : public StepHolder
	{    
		FuncType f;

		StepHolderImpl(FuncType _f) : f(_f) {}

		void operator()(void *instance, Param1 p1)
		{
			//ClassType *inst= reinterpret_cast<ClassType*>(instance);
         ClassType *inst= static_cast<ClassType*>(instance);
			CALL_MEMBER_FUNCTION(*inst, f)(p1);
		}   

		bool MatchParameters( std::vector<ParameterBase*> parameters )
		{
			if (parameters.size() != 1) return false;

			Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
			if (param1 == NULL) return false;

			return true;
		}

		void Execute( void *instance, std::vector<ParameterBase*> parameters )
		{
			assert(parameters.size() == 1);

			Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
			assert(param1 != NULL);

			(*this)(instance, param1->GetValue());         
		}
	};

   //2 arity
   template <typename FuncType, typename ClassType, typename Param1, typename Param2>
   struct StepHolderImpl<FuncType, ClassType, Param1, Param2> : public StepHolder
   {    
      FuncType f;

      StepHolderImpl(FuncType _f) : f(_f) {}

      void operator()(void *instance, Param1 p1, Param2 p2)
      {
         //ClassType *inst= reinterpret_cast<ClassType*>(instance);
         ClassType *inst= static_cast<ClassType*>(instance);
         CALL_MEMBER_FUNCTION(*inst, f)(p1, p2);
      }   

      bool MatchParameters( std::vector<ParameterBase*> parameters )
      {
         if (parameters.size() != 2) return false;

         Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
         Parameter<Param2> *param2= dynamic_cast<Parameter<Param2> *>(parameters[1]);
         if (param1 == NULL || param2 == NULL) return false;

         return true;
      }

      void Execute( void *instance, std::vector<ParameterBase*> parameters )
      {
         assert(parameters.size() == 2);

         Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
         Parameter<Param2> *param2= dynamic_cast<Parameter<Param2> *>(parameters[1]);
         assert(param1 != NULL || param2 != NULL );

         (*this)(instance, param1->GetValue(), param2->GetValue());
      }
   };

   //3 arity
   template <typename FuncType, typename ClassType, typename Param1, typename Param2, typename Param3>
   struct StepHolderImpl<FuncType, ClassType, Param1, Param2, Param3> : public StepHolder
   {    
      FuncType f;

      StepHolderImpl(FuncType _f) : f(_f) {}

      void operator()(void *instance, Param1 p1, Param2 p2, Param3 p3)
      {
         //ClassType *inst= reinterpret_cast<ClassType*>(instance);
         ClassType *inst= static_cast<ClassType*>(instance);
         CALL_MEMBER_FUNCTION(*inst, f)(p1, p2, p3);
      }   

      bool MatchParameters( std::vector<ParameterBase*> parameters )
      {
         if (parameters.size() != 3) return false;

         Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
         Parameter<Param2> *param2= dynamic_cast<Parameter<Param2> *>(parameters[1]);
         Parameter<Param3> *param3= dynamic_cast<Parameter<Param3> *>(parameters[2]);
         if (param1 == NULL || param2 == NULL || param3 == NULL) return false;

         return true;
      }

      void Execute( void *instance, std::vector<ParameterBase*> parameters )
      {
         assert(parameters.size() == 3);

         Parameter<Param1> *param1= dynamic_cast<Parameter<Param1> *>(parameters[0]);
         Parameter<Param2> *param2= dynamic_cast<Parameter<Param2> *>(parameters[1]);
         Parameter<Param3> *param3= dynamic_cast<Parameter<Param3> *>(parameters[2]);
         assert(param1 != NULL || param2 != NULL || param3 != NULL);

         (*this)(instance, param1->GetValue(), param2->GetValue(), param3->GetValue());
      }
   };


	class StepDefinition 
	{	
		StepHolder *funcImpl;
      bool exceptionThrown;
      std::string stepName;

	public:

      ~StepDefinition() {
         if (exceptionThrown) {
            std::stringstream ss; 
            ss << "The step " << stepName << "has thrown an exception but was not specified\n"
               << "If it is a specification you can use the built in step \"it should throw\" "
               << "\n\nExample: THEN << \"it should throw\" << OK; \n\n";
            std::runtime_error e(ss.str());
            throw e;
         }
      }


		template <class FuncType, class ClassType>
      StepDefinition(const std::string &_stepName, FuncType f, ClassType *t)
			: stepName(_stepName), exceptionThrown(false), funcImpl(new StepHolderImpl<FuncType, typename ClassType::Type>(f))
		{
		}

		template <class FuncType, class ClassType>
		StepDefinition(const std::string &_stepName, FuncType f, ClassType *t, int)
			: stepName(_stepName), exceptionThrown(false), funcImpl(new StepHolderImpl<FuncType
         , typename ClassType::Type, typename ClassType::P1>(f))
		{
		}

      template <class FuncType, class ClassType>
      StepDefinition(const std::string &_stepName, FuncType f, ClassType *t, int, int)
         : stepName(_stepName), exceptionThrown(false), funcImpl(new StepHolderImpl<FuncType
         , typename ClassType::Type, typename ClassType::P1, typename ClassType::P2>(f))
      {
      }

      template <class FuncType, class ClassType>
      StepDefinition(const std::string &_stepName, FuncType f, ClassType *t, int, int, int)
         : stepName(_stepName), exceptionThrown(false), funcImpl(new StepHolderImpl<FuncType, typename ClassType::Type
         , typename ClassType::P1, typename ClassType::P2, typename ClassType::P3>(f))
      {
      }
      
		StepHolder *GetStepImpl() { return funcImpl; }


      std::string GetStepName() const { return stepName; }
      bool HasThrown() const { return exceptionThrown; }
      void HasThrown(bool hasThrown) { exceptionThrown= hasThrown; }
	};


}