#include "WADLoader.h"


WADLoader::WADLoader(std::string wad_file)
    : WADFile(wad_file), WADData(NULL)
{
    
}

WADLoader::~WADLoader()
{
    delete[] WADData;
    WADData = NULL;
}

bool WADLoader::LoadWAD()
{
    if(!OpenAndLoad())
    {
        return false;
    }
    
    if(!ReadDirectories())
    {
        return false;
    }
    
    return true;
}

bool WADLoader::OpenAndLoad()
{
    std::cout << "Opening WAD File: " << WADFilePath << std::endl;
    
    WADFile.open(WADFilePath, std::ifstream::binary);
    if(!WADFile.is_open())
    {
        std::cout << "Failed to Open WAD File: " << WADFilePath << std::endl;
        return false;
    }
    
    WADFile.seekg(0, WADFile.end);
    size_t length = WADFile.tellg();
    
    if(WADData)
    {
        delete[] WADData;
        WADData = NULL;
    }
    
    WADData = new uint8_t[length];
    if(WADData == NULL)
    {
        std::cout << "Failed to allocate Memory for WAD File of size: " << length << std::endl;
        return false;
    }
    
    WADFile.seekg(std::ifstream::beg);
    WADFile.read((char *)WADData, length);
    
    WADFile.close();
    
    std::cout << "Loading Complete" << std::endl;
    return true;
}

bool WADLoader::ReadDirectories()
{
    WADReader reader;
    
    Header header;
    reader.ReadHeaderData(WADData, 0, header);
    
    std::cout << header.WADType << std::endl;
    std::cout << header.DirectoryCount << std::endl;
    std::cout << header.DirectoryOffset << std::endl;
    std::cout << std::endl << std::endl;
    
    Directory directory;
    
    for(unsigned int i = 0; i < header.DirectoryCount; i++)
    {
        reader.ReadDirectoryData(WADData, header.DirectoryOffset, directory);
        
        Directories.push_back(directory);
        
        std::cout << directory.LumpOffset << std::endl;
        std::cout << directory.LumpSize << std::endl;
        std::cout << directory.LumpName << std::endl;
        std::cout << std::endl << std::endl;
    }
    
    return true;
}
