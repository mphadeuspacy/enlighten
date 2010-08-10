#include "TableParser.h"

#include <sstream>
#include <fstream>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////

TableParser::TableParser()
{

}

TableParser::~TableParser()
{

}

Fixture::Table TableParser::LoadTable(const std::string &contents)
{	
	Fixture::Table table;
	std::stringstream stream(contents.c_str());	

	std::string header= getLine(stream);
	std::vector<std::string> fields= tokenize(header, '|');	

	while (!stream.eof())
   {
		std::string line= getLine(stream);
		std::vector<std::string> lineParams= tokenize(line, '|');		
		addParametersInTable(table, fields, lineParams); 
	}	   
	return table;    
}

std::string TableParser::getLine(std::stringstream &stream)
{
	const int MAX_LINE= 256;
	char line[MAX_LINE];
	stream.getline(line,MAX_LINE);
	return std::string (line);
}

std::vector<std::string> TableParser::tokenize(std::string content, char separator)
{
   std::string token;
   std::stringstream ss(content);
   std::vector<std::string> tokens;

   while (std::getline(ss, token, separator))
   {
      if (!token.empty())
         tokens.push_back(token);
   }

   return tokens;
}

void TableParser::addParametersInTable
( 
   Fixture::Table &table
   , const std::vector<std::string> &paramNames
   , const std::vector<std::string> &lineParams 
) 
{
	assert(paramNames.size()== lineParams.size());
	Fixture::Row row;
	for (unsigned int i= 0; i< paramNames.size(); i++){
		row[paramNames[i]]= lineParams[i];		
	}
	table.push_back(row);
}

Fixture::Table TableParser::LoadTableFromFile( const std::string &fileName )
{
	std::string buffer;
	std::ifstream arq;		
	arq.open(fileName.c_str(), std::ios::in);
	std::getline(arq, buffer, '\0');
	arq.close();
	return LoadTable(buffer);
}
