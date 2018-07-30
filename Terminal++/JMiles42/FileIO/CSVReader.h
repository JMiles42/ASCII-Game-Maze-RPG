#pragma once
#include <vector>
#include <fstream>
#include <string>
class CSVReader
{
public:
	static std::vector<std::string> LoadCSVFile(std::string filename);
	static std::string RemoveCommas(std::string &data);
};
