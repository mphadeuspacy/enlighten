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

	std::string cabecalho= getLine(stream);
	std::vector<std::string> paramNames;
	separaParametros(cabecalho,paramNames);

	while (!stream.eof()){
		std::string linha= getLine(stream);
		std::vector<std::string> lineParams;
		separaParametros(linha,lineParams);
		addParametersInTable(table,paramNames,lineParams); 
	}	   
	return table;    
}

std::string TableParser::getLine(std::stringstream &stream){
	const int MAX_LINE= 256;
	char line[MAX_LINE];
	stream.getline(line,MAX_LINE);
	return std::string (line);
}

void TableParser::separaParametros( std::string linhaComTokens, std::vector<std::string> &parameters ) 
{
	parameters.clear();
	std::string parameter;		
	for (unsigned int i= 1; i<= linhaComTokens.size(); i++){
		char caracter= linhaComTokens[i];
		if (caracter == '|' && parameter.size()>0){
			parameters.push_back(parameter);  
			parameter.clear();
		}
		else
			parameter+= caracter;
	}
}
#include <iostream>
void TableParser::addParametersInTable( Fixture::Table &table,const std::vector<std::string> &paramNames,const std::vector<std::string> &lineParams ) 
{
	assert(paramNames.size()== lineParams.size());
	Fixture::Row row;
	for (unsigned int i= 0; i< paramNames.size(); i++){
		row[paramNames[i]]= lineParams[i];
		std::cout << paramNames[i] << " == " << lineParams[i] << std::endl; 
	}
	table.push_back(row);
}

Fixture::Table TableParser::LoadTableFromFile( const std::string &fileName )
{
	std::string buffer;
	std::ifstream arq;		
	arq.open(fileName.c_str(), std::ios::in);
	std::getline(arq,buffer,'\0');
	arq.close();
	return LoadTable(buffer);	
}
