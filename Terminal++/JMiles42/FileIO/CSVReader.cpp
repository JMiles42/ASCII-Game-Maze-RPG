#include "CSVReader.h"
std::vector<std::string> CSVReader::LoadCSVFile(std::string filename)
{
	//Loads csv file into a string
	std::ifstream file;
	std::vector<std::string> data;
	file.open(filename);
	if (file.good())
	{
		while (!file.eof())
		{
			std::string s;
			std::getline(file, s);
			s = RemoveCommas(s);
			data.push_back(s);
		}
		return data;
	}
	return std::vector<std::string>();
}
std::string CSVReader::RemoveCommas(std::string& data)
{
	//Removed commas from string
	std::string returnValue = "";
	for (auto c : data) if (c != ',') returnValue.push_back(c);
	return returnValue;
}
