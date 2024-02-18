#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DataTypes.h"
#include "WADReader.h"

class WADLoader
{
public:
    WADLoader(std::string wad_path);
    ~WADLoader();
    
    bool LoadWAD();
    
private:
    bool OpenAndLoad();
    bool ReadDirectories();
    
    std::string WADFilePath;
    std::ifstream WADFile;
    uint8_t* WADData;
    std::vector<Directory> Directories;
};
