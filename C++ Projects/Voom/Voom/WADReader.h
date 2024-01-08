#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class WADReader
{
public:
	WADReader(std::string filePath);
	bool LoadWAD();

	~WADReader();

private:
	bool OpenAndLoad();
	bool ReadDictionaries();

	std::string m_WadFilePath;
	std::ifstream m_WadFile;
	uint8_t* WADData;
	std::vector<
};