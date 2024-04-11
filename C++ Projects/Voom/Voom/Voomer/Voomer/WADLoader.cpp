#include "WADLoader.h"

WADLoader::WADLoader()
    : m_WADData(NULL)
{
    
}

WADLoader::~WADLoader()
{
    delete[] m_WADData;
}

void WADLoader::SetWADFilePath(std::string WADFilePath)
{
    m_WADFilePath = WADFilePath;
}

bool WADLoader::LoadWAD()
{
    if (!OpenAndLoad())
    {
        return false;
    }
    if (!ReadDirectories())
    {
        return false;
    }
    
    return true;
}

bool WADLoader::OpenAndLoad()
{
    std::cout << "Loading WAD File: " << m_WADFilePath << std::endl;
    
    m_WADFile.open(m_WADFilePath, std::ifstream::binary);
    if (!m_WADFile.is_open())
    {
        std::cout << "Failed to Open WAD File: " << m_WADFilePath << std::endl;
        return false;
    }
    
    m_WADFile.seekg(0, m_WADFile.end);
    size_t length = m_WADFile.tellg();
    
    if (m_WADData)
    {
        delete[] m_WADData;
        m_WADData = NULL;
    }
    
    m_WADData = new uint8_t[length];
    if (m_WADData == NULL)
    {
        std::cout << "Failed to Allocate Memory For WAD File of size " << length << std::endl;
        return false;
    }
    
    m_WADFile.seekg(std::ifstream::beg);
    m_WADFile.read((char*)m_WADData, length);
    
    m_WADFile.close();
    
    std::cout << "Finished Loading WAD File" << std::endl;
    std::cout << std::endl << std::endl;
    
    return true;
}

bool WADLoader::ReadDirectories()
{
    WADReader reader;
    
    Header header;
    reader.ReadHeaderData(m_WADData, 0, header);
    
//    std::cout << header.WADType << std::endl;
//    std::cout << header.DirectoryCount << std::endl;
//    std::cout << header.DirectoryOffset << std::endl;
//    std::cout << std::endl << std::endl;
    
    Directory directory;
    
    for (unsigned int i = 0; i < header.DirectoryCount; i++)
    {
        reader.ReadDirectoryData(m_WADData, header.DirectoryOffset + i * 16, directory);
        
        m_Directories.push_back(directory);
        
//        std::cout << directory.LumpOffset << std::endl;
//        std::cout << directory.LumpSize << std::endl;
//        std::cout << directory.LumpName << std::endl;
//        std::cout << std::endl;
    }
    
    return true;
}

bool WADLoader::LoadMapData(Map *map)
{
    if (!ReadMapVertex(map))
    {
        std::cout << "Error Failed to Load map Vertex Data, MAP: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapLinedef(map))
    {
        std::cout << "Error Failed to Load map Linedef Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapThing(map))
    {
        std::cout << "Error Failed to Load map Thing Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapNode(map))
    {
        std::cout << "Error Failed to Load map Node Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapSubsector(map))
    {
        std::cout << "Error Failed to Load Map Subsector Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapSeg(map))
    {
        std::cout << "Error Failed to Load Map Seg Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapSidedefs(map))
    {
        std::cout << "Error Failed to Load Map Sidedef Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    if (!ReadMapSectors(map))
    {
        std::cout << "Error Failed to Load Map Sector Data, Map: " << map->GetName() << std::endl;
        return false;
    }
    
    return true;
}

int WADLoader::FindMapIndex(Map* map)
{
    if (map->GetLumpIndex() > -1)
    {
        return map->GetLumpIndex();
    }
    
    for (int i = 0; i < m_Directories.size(); i++)
    {
        if (m_Directories[i].LumpName == map->GetName())
        {
            map->SetLumpIndex(i);
            return i;
        }
    }
    
    return -1;
}

bool WADLoader::ReadMapVertex(Map* map)
{
    std::cout << "Reading Map Vertex Data..." << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::VERTEXES;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "VERTEXES") != 0)
    {
        return false;
    }
    
    int VertexSize = sizeof(Vertex);
    int VertexCount = m_Directories[MapIndex].LumpSize / VertexSize;
    
    Vertex vertex;
    
    for (int i = 0; i < VertexCount; i++)
    {
        m_Reader.ReadVertexData(m_WADData, m_Directories[MapIndex].LumpOffset + i * VertexSize, vertex);
        
        map->AddVertex(vertex);
        
//        std::cout << vertex.xPos << std::endl;
//        std::cout << vertex.yPos << std::endl;
        //std::cout << "("  << vertex.xPos << "," << vertex.yPos << ")" << std::endl;
        //std::cout << std::endl << std::endl;
    }
    
    std::cout << "Finished Loading Map Vertex Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapLinedef(Map* map)
{
    std::cout << "Reading Map Linedef Data... " << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::LINEDEFS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "LINEDEFS") != 0)
    {
        return false;
    }
    
    int LinedefSize = sizeof(WADLinedef);
    int LinedefCount = m_Directories[MapIndex].LumpSize / LinedefSize;
    
    WADLinedef linedef;
    
    for (int i = 0; i < LinedefCount; i++)
    {
        m_Reader.ReadLinedefData(m_WADData, m_Directories[MapIndex].LumpOffset + i * LinedefSize, linedef);
        
        map->AddLinedef(linedef);
        
//        std::cout << linedef.StartVertex << std::endl;
//        std::cout << linedef.EndVertex << std::endl;
//        std::cout << linedef.Flags << std::endl;
//        std::cout << linedef.LineType << std::endl;
//        std::cout << linedef.SectorTag << std::endl;
//        std::cout << linedef.RightSidedef << std::endl;
//        std::cout << linedef.LeftSidedef << std::endl;
    }
    
    std::cout << "Finished Loading Map Linedef Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapThing(Map *map)
{
    std::cout << "Reading Map Thing Data... " << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::THINGS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "THINGS") != 0)
    {
        return false;
    }
    
    int ThingSize = sizeof(Thing);
    int ThingCount = m_Directories[MapIndex].LumpSize / ThingSize;
    
    Thing thing;
    for (int i = 0; i < ThingCount; i++)
    {
        m_Reader.ReadThingData(m_WADData, m_Directories[MapIndex].LumpOffset + i * ThingSize, thing);
        
        (map->GetThing())->AddThing(thing);
    }
    
    std::cout << "Finished Loading Map Thing Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapNode(Map *map)
{
    std::cout << "Reading Map Node Data... " << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::NODES;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "NODES") != 0)
    {
        return false;
    }
    
    int NodeSize = sizeof(Node);
    int NodeCount = m_Directories[MapIndex].LumpSize / NodeSize;
    
    Node node;
    
    for (int i = 0; i < NodeCount; i++)
    {
        m_Reader.ReadNodeData(m_WADData, m_Directories[MapIndex].LumpOffset + i * NodeSize, node);
        
        map->AddNode(node);
    }
    
    std::cout << "Finished Loading Map Node Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapSubsector(Map* map)
{
    std::cout << "Reading Map Subsector Data... " << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == 1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::SSECTORS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "SSECTORS") != 0)
    {
        return false;
    }
    
    int SubsectorSize = sizeof(Subsector);
    int SubsectorCount = m_Directories[MapIndex].LumpSize / SubsectorSize;
    
    Subsector subsector;
    
    for (int i = 0; i < SubsectorCount; i++)
    {
        m_Reader.ReadSubsectorData(m_WADData, m_Directories[MapIndex].LumpOffset + i * SubsectorSize, subsector);
        
        map->AddSubsector(subsector);
    }
    
    std::cout << "Finished Loading Map Subsector Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapSeg(Map *map)
{
    std::cout << "Reading Map Seg Data... " << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::SEGS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "SEGS") != 0)
    {
        return false;
    }
    
    int SegSize = sizeof(WADSeg);
    int SegCount = m_Directories[MapIndex].LumpSize / SegSize;
    
    WADSeg seg;
    
    for (int i = 0; i < SegCount; i++)
    {
        m_Reader.ReadSegData(m_WADData, m_Directories[MapIndex].LumpOffset + i * SegSize, seg);
        
        map->AddSeg(seg);
    }
    
    std::cout << "Finished Loading Map Seg Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapSidedefs(Map *map)
{
    std::cout << "Reading Map Sidedefs..." << std::endl;
    
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::SIDEDEFS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "SIDEDEFS") != 0)
    {
        return false;
    }
    
    int SidedefSize = sizeof(WADSidedef);
    int SidedefCount = m_Directories[MapIndex].LumpSize / SidedefSize;
    
    WADSidedef sidedef;
    
    for (int i = 0; i < SidedefCount; i++)
    {
        m_Reader.ReadSidedefData(m_WADData, m_Directories[MapIndex].LumpOffset + i * SidedefSize, sidedef);
        
        map->AddSidedef(sidedef);
    }
    
    std::cout << "Finished Loading Map Sidedef Data!" << std::endl;
    std::cout << std::endl;
    
    return true;
}

bool WADLoader::ReadMapSectors(Map *map)
{
    int MapIndex = FindMapIndex(map);
    
    if (MapIndex == -1)
    {
        return false;
    }
    
    MapIndex += MAPLUMPSINDEX::SECTORS;
    
    if (strcmp(m_Directories[MapIndex].LumpName, "SECTORS") != 0)
    {
        return false;
    }
    
    int SectorSize = sizeof(WADSector);
    int SectorCount = m_Directories[MapIndex].LumpSize / SectorSize;
    
    WADSector sector;
    
    for (int i = 0; i < SectorCount; i++)
    {
        m_Reader.ReadSectorData(m_WADData, m_Directories[MapIndex].LumpOffset + i * SectorSize, sector);
        
        map->AddSector(sector);
    }
    
    return true;
}
