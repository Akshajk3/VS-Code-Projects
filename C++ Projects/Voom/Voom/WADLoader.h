#pragma once

#include <iostream>
#include <fstream>

#include "WADReader.h"
#include "Map.h"

class WADLoader
{
public:
    WADLoader();
    void SetWADFilePath(std::string sWADFilePath);
    bool LoadWAD();
    bool LoadMapData(Map *pMap);

    ~WADLoader();

protected:
    bool OpenAndLoad();
    bool ReadDirectories();
    bool ReadMapVertex(Map* map);
    bool ReadMapLinedef(Map* map); 
    int FindMapIndex(Map* map);


    std::string m_sWADFilePath;
    std::ifstream m_WADFile;
    uint8_t *m_WADData;
    std::vector<Directory> m_WADDirectories;
    WADReader m_Reader;
};
