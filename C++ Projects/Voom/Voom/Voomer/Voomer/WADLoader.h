#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "DataTypes.h"
#include "WADReader.h"

class WADLoader
{
public:
    WADLoader(std::string WADFilePath);
    bool LoadWAD();
    
    ~WADLoader();
private:
    bool OpenAndLoad();
    bool ReadDirectories();
    bool ReadVertexes();
    bool ReadLinedefs();
    
    std::string m_WADFilePath;
    std::ifstream m_WADFile;
    uint8_t* m_WADData;
    std::vector<Directory> m_Directories;
};
