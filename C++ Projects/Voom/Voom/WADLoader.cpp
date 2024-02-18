#include "WADLoader.h"


WADLoader::WADLoader()
    : WADData(NULL)
{
    
}

WADLoader::~WADLoader()
{
    delete[] WADData;
    WADData = NULL;
}

void WADLoader::SetWADFilePath(std::string file_path)
{
    WADFilePath = file_path;
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
    Header header;
    reader.ReadHeaderData(WADData, 0, header);
    
//    std::cout << header.WADType << std::endl;
//    std::cout << header.DirectoryCount << std::endl;
//    std::cout << header.DirectoryOffset << std::endl;
//    std::cout << std::endl << std::endl;
    
    Directory directory;
    
    for(unsigned int i = 0; i < header.DirectoryCount; i++)
    {
        reader.ReadDirectoryData(WADData, header.DirectoryOffset + i * 16, directory);
        
        Directories.push_back(directory);
        
//        std::cout << directory.LumpOffset << std::endl;
//        std::cout << directory.LumpSize << std::endl;
//        std::cout << directory.LumpName << std::endl;
//        std::cout << std::endl << std::endl;
    }
    
    return true;
}

int WADLoader::FindMapIndex(Map* map)
{
    for(int i = 0; i < Directories.size(); i++)
    {
        if(Directories[i].LumpName == map->GetName())
        {
            return i;
        }
    }
    
    return -1;
}

bool WADLoader::LoadMapData(Map* map)
{
    if(!ReadMapVertex(map))
    {
        std::cout << "Failed to Load map Vertex Data MAP: " << map->GetName() << std::endl;
        return false;
    }
    if(!ReadMapLinedef(map))
    {
        std::cout << "Failed to Load map Linedef Data MAP: " << map->GetName() << std::endl;
        return false;
    }
    
    return true;
}

bool WADLoader::ReadMapVertex(Map* map)
{
    int MapIndex = FindMapIndex(map);
    
    std::cout << MapIndex << std::endl;
    
    if(MapIndex == -1)
    {
        return false;
    }
    
    
    MapIndex += LUMP_INDICES::VERTEXES;
    
    if(strcmp(Directories[MapIndex].LumpName, "VERTEXES") != 0)
    {
        return false;
    }
    
    int VertSize = sizeof(Vertex);
    int VertCount = Directories[MapIndex].LumpSize / VertSize;
    
    Vertex vertex;
    for(int i = 0; i < VertCount; i++)
    {
        reader.ReadVertexData(WADData, Directories[MapIndex].LumpOffset, vertex);
        map->AddVertex(vertex);
        
        std::cout << vertex.XPosition << std::endl;
        std::cout << vertex.YPosition << std::endl;
        std::cout << std::endl;
    }
    
    return true;
}

bool WADLoader::ReadMapLinedef(Map* map)
{
    int MapIndex = FindMapIndex(map);
    
    if(MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += LUMP_INDICES::LINEDEFS;
    
    if(strcmp(Directories[MapIndex].LumpName, "LINEDEFS") != 0)
    {
        return false;
    }
    
    int LinedefSize = sizeof(Linedef);
    int LinedefCount = Directories[MapIndex].LumpSize / LinedefSize;
    
    Linedef linedef;
    for(int i = 0; i < LinedefCount; i++)
    {
        reader.ReadLinedefData(WADData, Directories[MapIndex].LumpOffset, linedef);
        map->AddLinedef(linedef);
    }
}
