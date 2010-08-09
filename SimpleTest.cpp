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
   DECLARE_COLUMN(Altura, CalculeIMC);
   DECLARE_COLUMN(Peso, CalculeIMC);
   DECLARE_COLUMN(EsperaSe, CalculeIMC);   

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
   DECLARE_COLUMN(SomeColumn, SimpleFixture);

   void execute()
   {
   
   }
};

Context(SimpleExamples)
{

	Spec(Tokenizer)
	{
		TableParser parser;
		Fixture::Table table= parser.LoadTable("|some|\n|50|");

		Assert::That(table.size(), Is().EqualTo(1));

	}

   Spec(ShouldReadExampleFile)
   {
      SimpleFixture fixture;
      fixture.SomeColumn("some")
         .ParaOsDados("|some|\n|50|");

      Assert::That(fixture.ExampleCount(), Is().EqualTo(1));

            
   }

   Spec(ShouldFailOnError)
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
   }
};