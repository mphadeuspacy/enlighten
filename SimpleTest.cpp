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
      for (int i= 0; i < ExampleCount(); i++)
      {
         double altura= this->getCellAs<double>("altura", i);
         double peso= this->getCellAs<double>("peso", i);
			double imcEsperado= this->getCellAs<double>("imc", i);
			Assert::That(IMC(altura,peso),Is().EqualTo(imcEsperado));     
      }      
   }

	double IMC(double altura, double peso)
	{
		return peso / (altura*altura);
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
		Table table= parser.LoadTable("|altura|peso|imc|\n|1.74|73|24.11|\n|1.63|62|23.33|\n|1.52|51|22.07|");
		Assert::That(table.size(), Is().EqualTo(3));	
      Assert::That(numberOfFields(table), Is().EqualTo(3));	
	}

   size_t numberOfFields(const Table &table) const
   {
      if (table.empty()) return 0;
      else return table.begin()->size();
   }

	Spec(ParserFromFile)
	{		
		Table table= TableParser().LoadTableFromFile("teste.txt");
		Assert::That(table.size(), Is().EqualTo(3));	
	}

   Spec(ShouldReadExampleFile)
   {
      SimpleFixture fixture;
		fixture.LoadingData("|some|\n|50|");	
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
         .LoadingData("|altura|peso|imc|\n|1.74|73|24.1115|\n|1.63|62|23.33|\n|1.52|51|22.07|");
   }
};