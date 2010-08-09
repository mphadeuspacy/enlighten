#ifndef INCLUDED_FIXTURE_H
#define INCLUDED_FIXTURE_H

#include <map>
#include <string>
#include <vector>


class Fixture
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

public:
	typedef std::vector<std::string> Rows;
	typedef std::map<std::string, Rows> Table;

protected:
   int exampleCount;
   std::map<std::string, Rows> columns;
};

#endif //INCLUDED_FIXTURE_H