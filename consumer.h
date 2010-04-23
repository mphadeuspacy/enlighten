#ifndef INCLUDED_CONSUMER_H
#define INCLUDED_CONSUMER_H

#include <vector>

#include <parameter.h>

#include <step_map.h>

#include <sstream>

#include <assert.h>
#include <iostream>

namespace enlighten {

	class ParameterBase;

	class lit
	{
	public:
		lit(const std::string &_lit)
			: _literal(_lit) {}

		std::string GetLiteral() const { return _literal; }

	private:
		std::string _literal;		
	};


   class Consumer
   {
      std::string methodName;
      std::vector<ParameterBase*> parameters;

      void *actualInstance;
		std::string className;

      
      struct ExceptionInfo {
      
         ExceptionInfo() : exceptionThrown(false) {}

         std::string methodThrown;
         bool exceptionThrown;

      } exceptionInfo;

      StepDefinition *lastStepExecuted;     

   public:
      Consumer() : lastStepExecuted(NULL) {}

      struct EndMarker {};

      Consumer &operator<<(const char* str) 
      {
         methodName.append(str);
         return *this;
      }
      
      Consumer &operator<<(int value) 
      {
         parameters.push_back(new Parameter<int>(value,"int"));
         return *this;
      }

		Consumer &operator<<(const lit &_literal) 
      {
			parameters.push_back(new Parameter<std::string>(_literal.GetLiteral(),"std::string"));
         return *this;
      }

		Consumer &operator<<(std::string str) 
      {
			parameters.push_back(new Parameter<std::string>(str,"std::string"));
         return *this;
      }


      Consumer &operator<<(EndMarker) 
      {
         Consume();
         return *this;
      }

		template <typename T>
		std::string getTypeName(const T &t)
		{
			std::string name(typeid(t).name());
			if (!name.find("class"))
				name.erase(0, 5);
			if (!name.find("struct"))
				name.erase(0, 6);

			return name;
		}

		template <typename T>
		Consumer &operator<<(T &object) 
      {         
			parameters.push_back(new Parameter<T>(object, getTypeName(object)));
         return *this;
      }

      void Consume()
      {
         if (lastStepExecuted && lastStepExecuted->HasThrown() && methodName.compare("it should throw")) {
            std::stringstream ss;
            ss << "\n\n\nENLIGHTEN LOG: \nAn exception was thrown during the step \"" 
               << lastStepExecuted->GetStepName() << "\" execution\n"
               << "If it is a specification you can use the built in step \"it should throw\" "
               << "\n\nExample: THEN << \"it should throw\" << OK; \n\n";

            lastStepExecuted->HasThrown(false);
            std::cerr << ss.str();

            std::runtime_error e("");
            throw e;
         }

			if (StepMap::ExistStepDefinition(methodName)) {
				StepDefinition *step= StepMap::GetStepDefinition(methodName);
            if (step->GetStepImpl()->MatchParameters(parameters)) {

               lastStepExecuted= step;

               try {
                  /*exceptionInfo.exceptionThrown= false;*/
                  lastStepExecuted->HasThrown(false);

                  step->GetStepImpl()->Execute(actualInstance, parameters);
                  return;

               } catch (...) 
               {
                  lastStepExecuted->HasThrown(true);

                  /*exceptionInfo.methodThrown= methodName;
                  exceptionInfo.exceptionThrown= true;*/
                  return;
               }
            }
         }
         std::stringstream ss;
         ss << "\nyou must define the step: \n\n";
         ss << methodName << "\n\n";
         ss << "you can implement the step definition with this snippet:\n\n";
         ss << "STEP"
				<< parameters.size()
				<< "(\"" << methodName << "\","
				<< getClassName()
				<< ", " 
				<< wikifyMethodName()
            << printParameters(false, true) 
            << ")\nvoid "
				<< wikifyMethodName()
				<< "(" 
            << printParameters(true, false) 
            << ") \n{ \n   pending \n} \n";   

			std::cerr << ss.str();
			//assert(false);

         std::runtime_error e("");
         throw e;
      }

		void SetThisPointer(void *instance, const std::string &_className)
      {
         parameters.clear();
         methodName= "";
         actualInstance= instance;			
			className= _className;
//#ifdef MSVC
			//clear the class from the typeid().name()
			//TODO: verify if its standard
			className.erase(0, 5);
//#endif 
      }

		std::string getClassName()
		{
			return className;
		}

      std::string printParameters(bool withName, bool withInitialCommon)
      {
         std::stringstream paramAsString;
         for (size_t i= 0; i < parameters.size(); i++) {
            if ((withInitialCommon && i==0) || i > 0) paramAsString << ", ";
            paramAsString << parameters[i]->AsString();
            if (withName) { paramAsString << " p" << i+1; }
            
         }
         return paramAsString.str();
      }

		std::string wikifyMethodName(std::string methodName, bool lastWasSpace)
		{
			if (methodName.empty())
				return methodName;
			else {
				char firstChar= methodName[0];
				bool isSpace= firstChar == ' ';
				if (!isSpace && lastWasSpace) 
					firstChar= toupper(methodName[0]);

				methodName.erase(methodName.begin());
				return !isSpace ? 
					firstChar + wikifyMethodName(methodName, isSpace)
					: wikifyMethodName(methodName, isSpace);
			}
		}

		std::string wikifyMethodName()
		{
			return wikifyMethodName(methodName, false);			
		}

      bool HasThrow() const
      {
         return lastStepExecuted->HasThrown();
      }

      void HasThrow(bool hasThrown) 
      {
         return lastStepExecuted->HasThrown(hasThrown);
      }

      void ItShouldThrow()
      {
         if (!HasThrow()) {
            //consumer.HasThrow(false);
            std::runtime_error e("The step should throw a exception but never did");
            throw e;
         }         
         HasThrow(false);
      } 
   };   

} //namespace enlighten

#endif