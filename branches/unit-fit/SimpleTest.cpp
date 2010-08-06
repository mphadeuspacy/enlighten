#include <igloo/igloo.h>
using namespace igloo;

#include "FluentInterfaceHelper.h"

typedef std::vector<std::string> Rows;

class ExampleFixture
{
public:
   void ParaOsDados(const std::string &file)
   {
      //parse
      
      execute();
   }

   virtual void execute()= 0;

   template <class T>
   T getCellAs(const std::string label, int row)
   {
      T valueAsInt;
      std::stringstream ss(columns[label][row].c_str());
      ss >> valueAsInt;
      return valueAsInt;      
   }

   int ExampleCount() const
   {
      return exampleCount;
   }

protected:
   int exampleCount;
   std::map<std::string, Rows> columns;
};

#define DECLARE_COLUMN(name, klass)  \
   klass &name(const std::string &_##name)   \
   {  \
      columns[_##name]= Rows();  \
      return *this;  \
   }  




class CalculeIMC : public ExampleFixture
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

struct SimpleFixture : public ExampleFixture
{
   DECLARE_COLUMN(SomeColumn, SimpleFixture);

   void execute()
   {
   
   }
};

Context(SimpleExamples)
{

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