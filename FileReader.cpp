#include "FileReader.h"

#include <stdio.h>  

const unsigned int FileReader::MAX_LINE_SIZE= 255;

FileReader::FileReader(std::string _fileName)
                        :fileName(_fileName) 
{
}

FileReader::~FileReader()
{
}

std::map<std::string,std::vector<std::string>> FileReader::Table()
{	 
	std::vector<std::string> parametersNames;
	std::map<std::string,std::vector<std::string>> table;
		
	FILE *arq;
	char str[MAX_LINE_SIZE];
	arq= fopen(fileName.c_str(),"r");
    if(arq)
    {
       parametersNames= getNomeDosParemetros(arq);
	   while(!feof(arq))
       {
          std::vector<std::string> parameters= getNomeDosParemetros(arq); 
		  if (parameters.size() == parametersNames.size())
		     for (unsigned int i= 0; i< parameters.size(); i++)
			    table[parametersNames[i]].push_back(parameters[i]);		  
       }
    }
    fclose(arq);	 
	return table;
}

std::vector<std::string> FileReader::getNomeDosParemetros(FILE *arq)
{
	char str[MAX_LINE_SIZE];
	fgets(str,MAX_LINE_SIZE,arq);
	std::string linha= str;
	std::string parameter;
	std::vector<std::string> parameters;
	
	for (unsigned int i= 1; i<= linha.size(); i++){
		char caracter= linha[i];
		if (caracter == '|' && parameter.size()>0){
			parameters.push_back(parameter);  
			parameter.clear();
		}
		else
		   parameter+= caracter;
	}

	return parameters;
}