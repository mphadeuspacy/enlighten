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
      execute();
   }

   virtual void execute()= 0;

   template <class T>
   T getCellAs(const std::string field, int row)
   {
      T valueAsInt;
      std::stringstream ss(table[row][field].c_str());
      ss >> valueAsInt;
      return valueAsInt;
   }

   int ExampleCount() const
   {
      return exampleCount;
   }

public:
	//typedef std::vector<std::string> Rows;
	//typedef std::map<std::string, Rows> Table;
   typedef std::map<std::string, std::string> Row;
   typedef std::vector<Row> Table;

protected:
   int exampleCount;
   //std::map<std::string, Rows> columns;

   std::vector<std::string> fields;
   Table table;
};

#endif //INCLUDED_FIXTURE_H