#ifndef INCLUDE_TABLEPARSERBASE_H
#define INCLUDE_TABLEPARSERBASE_H

#include <sstream>
#include <fstream>
#include <assert.h>
#include <string>
#include "FixtureGlossary.h"

class TableParser
{
public:
	TableParser(){}
	virtual ~TableParser(){}

   /**
   *  Loads a table
   *  @return Table
   *  @param  const std::string & contents
   */
   Table LoadTable(const std::string &contents)
	{	
		Table table;
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

	/**
	*  Loads a table from a file
	*  @return Table
	*  @param  const std::string & fileName
	*/
	Table LoadTableFromFile(const std::string &fileName)
	{
		std::string buffer;
		std::ifstream arq;		
		arq.open(fileName.c_str(), std::ios::in);
		std::getline(arq, buffer, '\0');
		arq.close();
		return LoadTable(buffer);
	}

private:
   /**
   *  std::getline adapter 
   *  @return std::string
   *  @param  std::stringstream & stream
   */
   std::string getLine(std::stringstream &stream)
	{
		const int MAX_LINE= 256;
		char line[MAX_LINE];
		stream.getline(line,MAX_LINE);
		return std::string (line);
	}

	/**
	*  Tokenize a string with the separator passed.
   *
	*  @return std::vector<std::string>
	*  @param  std::string content
	*  @param  char separator
	*/
	std::vector<std::string> tokenize(std::string content, char separator)
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

   /**
   *  Add a line in the table
   *  @param  Table & table
   *  @param  const std::vector<std::string> & paramNames
   *  @param  const std::vector<std::string> & lineParams
   */
   void addParametersInTable( Table &table, 
      const std::vector<std::string> &paramNames,
      const std::vector<std::string> &lineParams
		) 
	{
		assert(paramNames.size()== lineParams.size());
		Row row;
		for (unsigned int i= 0; i< paramNames.size(); i++){
			row[paramNames[i]]= lineParams[i];		
		}
		table.push_back(row);
	}
};

#endif //INCLUDE_TABLEPARSERBASE_H