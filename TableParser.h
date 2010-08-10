#ifndef INCLUDE_TABLEPARSERBASE_H
#define INCLUDE_TABLEPARSERBASE_H

#ifndef INCLUDED_FIXTURE_H
#include "Fixture.h"
#endif

#include <string>

class TableParser
{
public:
   TableParser();
   virtual ~TableParser();

   Fixture::Table LoadTable(const std::string &contents); 
	Fixture::Table LoadTableFromFile(const std::string &fileName);

private:
   std::string getLine(std::stringstream &stream); 
	void separaParametros( std::string linhaComTokens, std::vector<std::string> &parameters); 
   void addParametersInTable( Fixture::Table &table,const std::vector<std::string> &paramNames,const std::vector<std::string> &lineParams); 	
};

#endif //INCLUDE_TABLEPARSERBASE_H