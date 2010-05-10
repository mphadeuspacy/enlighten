#include "step_map.h"

#include <consumer.h>
#include <enlighten_macros.h>

namespace enlighten {	

	Consumer consumer;
	Consumer::EndMarker ok;   

   struct BuiltInSteps {      

      STEP("it should throw", BuiltInSteps, ItShouldThrow)
      void ItShouldThrow()
      {
         consumer.NextStepShouldThrow();
      }
   } builtinSteps;

} //namespace enlighten