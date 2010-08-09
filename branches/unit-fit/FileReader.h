#ifndef INCLUDED_FileReader_H
#define INCLUDED_FileReader_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

class FileReader
{
public:
	FileReader(std::string _fileName);
	virtual ~FileReader();

	std::map<std::string,std::vector<std::string>> Table();


private:
	std::string fileName;
	static const unsigned int MAX_LINE_SIZE;

private:
	std::vector<std::string> getNomeDosParemetros(FILE *arq);
};

#endif //INCLUDED_FileReader_H
