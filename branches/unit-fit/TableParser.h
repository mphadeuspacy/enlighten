#ifndef INCLUDE_TABLEPARSERBASE_H
#define INCLUDE_TABLEPARSERBASE_H

#include "Fixture.h"
#include <string>

class TableParser
{
public:
   TableParser(){}
   virtual ~TableParser(){}

   Fixture::Table LoadTable(const std::string &contents)
   {
	   std::stringstream stream(contents.c_str());
	   std::string cabecalho= getLine(stream);
	   while (!stream.eof()){
		   std::string linha= getLine(stream);


	   }	   
	   return Fixture::Table();    
   }

   std::string getLine(std::stringstream &stream){
      const int MAX_LINE= 256;
	  char line[MAX_LINE];
	  stream.getline(line,MAX_LINE);
	  return std::string (line);
   }

};

#endif //INCLUDE_TABLEPARSERBASE_H