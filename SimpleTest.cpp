#include <igloo/igloo.h>
using namespace igloo;

#include "FluentInterfaceHelper.h"


class QualquerCoisa
{
public:
   void ParaOsDados(const std::string &file)
   {
      
      executeTest();
   }

   virtual void executeTest()= 0;
protected:
   std::map<std::string, std::vector<std::string> > dataMap;
};

class CalculeIMC : public QualquerCoisa
{
public:
   DECLARE_SUGAR(ParaPessoa, CalculeIMC);
   DECLARE_SUGAR(Com, CalculeIMC);
   DECLARE_SUGAR(E, CalculeIMC);

   void Peso(const std::string &strPeso)
   {
      dataMap[strPeso]= std::vector<std::string> >();
   }

   void executeTest()
   {

   }

};

Context(Some)
{
   Spec(ShouldHaveAnEmptyBoard)
   {
      CalculeIMC()
         .ParaPessoa().Com()
         .Peso("peso")
         .E()
         .Altura("altura")
         .EsperaSe("result")
      .ParaOsDados("dados.txt");
   }
   
};