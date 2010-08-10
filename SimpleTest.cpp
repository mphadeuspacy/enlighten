#include <igloo/igloo.h>
using namespace igloo;

#include "Fixture.h"
#include "TableParser.h"
#include "FluentInterfaceHelper.h"

class CalculeIMC : public Fixture
{
public:
   DECLARE_SUGAR(ParaPessoa, CalculeIMC);
   DECLARE_SUGAR(Com, CalculeIMC);
   DECLARE_SUGAR(E, CalculeIMC);
   //DECLARE_COLUMN(Altura, CalculeIMC);
   //DECLARE_COLUMN(Peso, CalculeIMC);
   //DECLARE_COLUMN(EsperaSe, CalculeIMC);   

   void execute()
   {   
      for (int i= 0; i < exampleCount; i++)
      {
         double altura= this->getCellAs<double>("altura", i);
         double peso= this->getCellAs<double>("peso", i);
      }      
   }
};

struct SimpleFixture : public Fixture
{
   //DECLARE_COLUMN(SomeColumn, SimpleFixture);

   void execute()
   {
   
   }
};

Context(SimpleExamples)
{

	Spec(Tokenizer)
	{
		TableParser parser;		
		Fixture::Table table= parser.LoadTable("|altura|peso|imc|\n|1.74|73|24.11|\n|1.63|62|23.33|\n|1.52|51|22.07|");
		Assert::That(table.size(), Is().EqualTo(3));	
	}

	Spec(ParserFromFile)
	{
		TableParser parser;
		Fixture::Table table= parser.LoadTableFromFile("D:\\User\\UnitFitnes\\teste.txt");
		Assert::That(table.size(), Is().EqualTo(3));	
	}

   /*Spec(ShouldReadExampleFile)
   {
      SimpleFixture fixture;
      fixture.SomeColumn("some")
         .ParaOsDados("|some|\n|50|");

      Assert::That(fixture.ExampleCount(), Is().EqualTo(1));

            
   }*/

   /*Spec(ShouldFailOnError)
   {
      CalculeIMC()
         .ParaPessoa().Com()
         .Peso("peso")
         .E()
         .Altura("altura")
         .EsperaSe("imc")
      //.ParaOsDados("dados.txt");
      .ParaOsDados(" \
         |altura|peso|imc?|  \
         |50|50|100|");
   }*/
};