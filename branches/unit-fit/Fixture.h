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
   T getCellAs(const std::string label, int row)
   {
      T valueAsInt;
      std::stringstream ss(rows[row][label].c_str());
      ss >> valueAsInt;
      return valueAsInt;      
   }

   int ExampleCount() const
   {
      return exampleCount;
   }

public:
	typedef std::map<std::string,std::string> Row;
	typedef std::vector<Row> Table;

protected:
   int exampleCount;
   Table rows;
};

#endif //INCLUDED_FIXTURE_H