#ifndef INCLUDED_FIXTURE_H
#define INCLUDED_FIXTURE_H

#include <map>
#include <string>
#include <vector>
#include "TableParser.h"
#include "FixtureGlossary.h"


class Fixture
{
public:	
	
	void LoadingData(const std::string &data)
   {  		 
		table= TableParser().LoadTable(data);
		execute();
   }

	void LoadingDataFronFile(const std::string &fileName)
	{  		 
		table= TableParser().LoadTableFromFile(fileName);
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
      return table.size();
   }

protected:
   Table table;	
   std::vector<std::string> fields;  	
};

#endif //INCLUDED_FIXTURE_H