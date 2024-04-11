#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "DataTypes.h"
#include "WADReader.h"
#include "Map.h"

class WADLoader
{
public:
    WADLoader();
    bool LoadWAD();
    bool LoadMapData(Map* map);
    void SetWADFilePath(std::string WADFilePath);
    
    ~WADLoader();
    
private:
    bool OpenAndLoad();
    bool ReadDirectories();
    bool ReadMapVertex(Map* map);
    bool ReadMapLinedef(Map* map);
    bool ReadMapThing(Map* map);
    bool ReadMapNode(Map* map);
    bool ReadMapSubsector(Map* map);
    bool ReadMapSeg(Map* map);
    bool ReadMapSectors(Map* map);
    bool ReadMapSidedefs(Map* map);
    int FindMapIndex(Map* map);
    
    std::string m_WADFilePath;
    std::ifstream m_WADFile;
    uint8_t* m_WADData;
    std::vector<Directory> m_Directories;
    WADReader m_Reader;
};
