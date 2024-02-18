#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DataTypes.h"
#include "WADReader.h"
#include "Map.h"

class WADLoader
{
public:
    WADLoader();
    ~WADLoader();
    
    void SetWADFilePath(std::string file_path);
    bool LoadWAD();
    bool LoadMapData(Map* map);
    
private:
    bool OpenAndLoad();
    bool ReadDirectories();
    bool ReadMapVertex(Map* map);
    bool ReadMapLinedef(Map* map);
    int FindMapIndex(Map* map);
    
    std::string WADFilePath;
    std::ifstream WADFile;
    uint8_t* WADData;
    std::vector<Directory> Directories;
    WADReader reader;
};
