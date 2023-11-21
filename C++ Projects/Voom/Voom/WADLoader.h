#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "DataTypes.h"
#include "WADReader.h"

#include "Map.h"

class WADLoader
{
public:
	WADLoader();
	void SetWADFilePath(std::string sWADFilePath);
	bool LoadWAD();
	bool LoadMapData(Map* map);

	~WADLoader();

protected:
	bool OpenAndLoad();
	bool ReadDirectories();
	bool ReadMapVertex(Map* map);
	bool ReadMapLineDef(Map* map);
	int FindMapIndex(Map* map);

	std::string m_sWADFilePath;
	std::ifstream m_WADFile;
	std::vector<Directory> m_WADDirectories;
	uint8_t* m_WADData;
	WADReader m_Reader;
};