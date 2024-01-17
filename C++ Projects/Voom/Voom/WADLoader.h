#pragma once

#include <iostream>
#include <fstream>

#include "WADReader.h"
#include "Map.h"

class WADLoader
{
public:
    WADLoader(std::string sWADFilePath);
    bool LoadWAD();
    int FindMapIndex(Map& map);
    bool ReadMapVertex(Map& map);
    bool ReadMapLinedef(Map& map);
    bool LoadMapData(Map& map);

    ~WADLoader();

protected:
    bool OpenAndLoad();
    bool ReadDirectories();

    std::string m_sWADFilePath;
    std::ifstream m_WADFile;
    uint8_t *m_WADData;
    std::vector<Directory> m_WADDirectories;
    WADReader m_Reader;
};
