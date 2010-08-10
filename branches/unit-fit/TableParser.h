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

   /**
   *  Loads a table
   *  @return Fixture::Table
   *  @param  const std::string & contents
   */
   Fixture::Table LoadTable(const std::string &contents); 

	/**
	*  Loads a table from a file
	*  @return Fixture::Table
	*  @param  const std::string & fileName
	*/
	Fixture::Table LoadTableFromFile(const std::string &fileName);

private:
   /**
   *  std::getline adapter 
   *  @return std::string
   *  @param  std::stringstream & stream
   */
   std::string getLine(std::stringstream &stream); 

	/**
	*  Tokenize a string with the separator passed.
   *
	*  @return std::vector<std::string>
	*  @param  std::string content
	*  @param  char separator
	*/
	std::vector<std::string> tokenize(std::string content, char separator);

   /**
   *  Add a line in the table
   *  @param  Fixture::Table & table
   *  @param  const std::vector<std::string> & paramNames
   *  @param  const std::vector<std::string> & lineParams
   */
   void addParametersInTable( Fixture::Table &table, 
      const std::vector<std::string> &paramNames,
      const std::vector<std::string> &lineParams
   );
};

#endif //INCLUDE_TABLEPARSERBASE_H