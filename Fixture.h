#ifndef INCLUDED_FIXTURE_H
#define INCLUDED_FIXTURE_H

#include <map>
#include <string>
#include <vector>
#include "Table.h"
#include "TableParser.h"
#include "FixtureGlossary.h"




class Fixture
{
public:	

   ~Fixture()
   {
      TableIterator it= FirstTable();
      for (; it != LastTable(); it++)
         delete (*it).second;
   }
	
	void LoadingData(const std::string &data)
   {
		tables= TableParser().LoadTables(data);    
   	execute();
   }

	void LoadingDataFromFile(const std::string &fileName)
	{  		 
		//table= TableParser().LoadTableFromFile(fileName);

      tables= TableParser().LoadTablesFromFile(fileName);
	   execute();
	}

   virtual void execute()= 0;

   template <class T>
   T getCellAs(const std::string tableName, const std::string field, int row)
   {
      T valueAsInt;
      std::stringstream ss(GetTable(tableName)->GetRows()[row][field].c_str());
      ss >> valueAsInt;
      return valueAsInt;
   }

   /*int ExampleCount() const
   {
      return tables.GetRows().size();
   }*/

   Table *GetTable(const std::string &tableName)
   {
      if (tables.find(tableName) == tables.end())
         throw std::runtime_error("cant find a table with name " + tableName);
      return tables[tableName];
   }  
   
   

   typedef std::map<std::string, Table*>::iterator TableIterator;
   TableIterator FirstTable()
   {
      return tables.begin();
   }

   TableIterator LastTable()
   {
      return tables.end();
   }

protected:
   std::map<std::string, Table*> tables;
   //std::vector<Table*> tables;
   //Table table;
   std::vector<std::string> fields;
};

#endif //INCLUDED_FIXTURE_H