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
      Table *imcTable= GetTable("ImcTable");
      for (unsigned i= 0; i < imcTable->GetRows().size(); i++)
      {
         double altura= this->getCellAs<double>("ImcTable", "altura", i);
         double peso= this->getCellAs<double>("ImcTable", "peso", i);
			double imcEsperado= this->getCellAs<double>("ImcTable", "imc", i);
			Assert::That(IMC(altura,peso)-imcEsperado,IsLessThan(0.01));     
      }      
   }

	double IMC(double altura, double peso)
	{
		return peso / (altura*altura);
	}
};

struct SimpleFixture : public Fixture
{
   void execute()
   {
   
   }
};

Context(SimpleExamples)
{
	Spec(Tokenizer)
	{
		TableParser parser;		
		Table *table= parser.LoadTable("|ImcTable|\n|altura|peso|imc|\n|1.74|73|24.11|\n|1.63|62|23.33|\n|1.52|51|22.07|");
		Assert::That(table->RowsCount(), Is().EqualTo(3));	
      Assert::That(table->FieldsCount(), Is().EqualTo(3));	

      delete table;
	}   

	Spec(ParserFromFile)
	{		
		Table *table= TableParser().LoadTableFromFile("teste.txt");
		Assert::That(table->RowsCount(), Is().EqualTo(3));	
      delete table;
	}

   Spec(ShouldReadExampleFromString)
   {
      SimpleFixture fixture;
		fixture.LoadingData("|some|\n|column|\n|50|\n\n");	
      Table *table= fixture.GetTable("some");
      Assert::That(table->RowsCount(), Is().EqualTo(1));
   }

   Spec(ShouldFailOnError)
   {
      CalculeIMC()
         .ParaPessoa().Com()
         .Peso("peso")
         .E()
         .Altura("altura")
         .EsperaSe("imc")      
         .LoadingDataFromFile("teste.txt");
   }
};