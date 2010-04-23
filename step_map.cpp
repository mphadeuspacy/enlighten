#include "step_map.h"

#include <consumer.h>

#include <macros.h>

namespace enlighten {

	std::map<std::string, StepDefinition*> StepMap::stepMap;

	Consumer consumer;
	Consumer::EndMarker ok;   

   struct BuiltInSteps {      

      //STEP("it should throw", BuiltInSteps, itShouldThrow)
      static void ItShouldThrow()
      {
         if (!consumer.HasThrow()) {
            //consumer.HasThrow(false);
            std::runtime_error e("The step should throw a exception but never did");
            throw e;
         }         
         consumer.HasThrow(false);
      }
   } builtinSteps;

} //namespace enlighten