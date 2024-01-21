#include "WADLoader.h"

WADLoader::WADLoader()
	: m_WADData(NULL)
{
	
}

WADLoader::~WADLoader()
{
    delete[] m_WADData;
}

void WADLoader::SetWADFilePath(std::string sWADFilePath)
{
	m_sWADFilePath = sWADFilePath;
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
	m_WADFile.open(m_sWADFilePath, std::ifstream::binary);
	if(!m_WADFile.is_open())
	{
		std::cout << "Error: Failed to open WAD file " << m_sWADFilePath << std::endl;
		return false;
	}

	m_WADFile.seekg(0, m_WADFile.end);
	size_t length = m_WADFile.tellg();

	if (m_WADData)
	{
		delete[] m_WADData;
	}

	m_WADData = new uint8_t[length];
	if (m_WADData == NULL)
	{
		std::cout << "Failed to Allocate memory for WAD file of size" << length << std::endl;
		return false;
	}
	m_WADFile.seekg(std::ifstream::beg);
	m_WADFile.read((char*)m_WADData, length);
	
	m_WADFile.close();

	std::cout << "Info: Loading Complete" << std::endl;
	
	return true;
}

bool WADLoader::ReadDirectories()
{
	std::cout << "Info: Reading Complete" << std::endl;

	WADReader reader;

	Header header;
	reader.ReadHeaderData(m_WADData, 0, header);
	
	/*
	std::cout << header.WADTypes << std::endl;
	std::cout << header.DirectoryCount << std::endl;
	std::cout << header.DirectoryOffset << std::endl;
	std::cout << std::endl << std::endl;
	*/

	Directory directory;

	for (unsigned int i = 0; i < header.DirectoryCount; i++)
	{
		reader.ReadDirectoryData(m_WADData, header.DirectoryOffset + i * 16, directory);

		m_WADDirectories.push_back(directory);
		
		/*
		std::cout << directory.LumpOffset << std::endl;
		std::cout << directory.LumpSize << std::endl;
		std::cout << directory.LumpName << std::endl;
		std::cout << std::endl;
		*/
	}

	return true;
}

int WADLoader::FindMapIndex(Map* map)
{
	if (map->GetLumpIndex() > -1)
	{
		return map->GetLumpIndex();
	}

	for (int i = 0; i < m_WADDirectories.size(); i++)
	{
		if (m_WADDirectories[i].LumpName == map->GetName())
		{
			map->SetLumpIndex(i);
			return i;
		}
	}

	return -1;
}

bool WADLoader::ReadMapVertex(Map* map)
{
	std::cout << "Info: Loading Map Vertex" << std::endl;

	int iMapIndex = FindMapIndex(map);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eVERTEXES;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "VERTEXES") != 0)
	{
		return false;
	}

	int iVertexSizeInBytes = sizeof(Vertex);
	int iVertexesCount = m_WADDirectories[iMapIndex].LumpSize / iVertexSizeInBytes;

	Vertex vertex;

	for (int i = 0; i < iVertexesCount; ++i)
	{
		m_Reader.ReadVertexData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iVertexSizeInBytes, vertex);

		map->AddVertex(vertex);
		//std::cout << "(" << vertex.x_pos << "," << vertex.y_pos << ")" << std::endl;
	}

	return true;
}

bool WADLoader::ReadMapLinedef(Map* map)
{
	std::cout << "Info: Loading Map Linedef" << std::endl;

	int iMapIndex = FindMapIndex(map);
	
	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eLINEDEFS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "LINEDEFS") != 0)
	{
		return false;
	}

	int iLinedefSizeInBytes = sizeof(Linedef);
	int iLinedefCount = m_WADDirectories[iMapIndex].LumpSize / iLinedefSizeInBytes;

	Linedef linedef;
	
	for (int i = 0; i < iLinedefCount; ++i)
	{
		m_Reader.ReadLinedefData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iLinedefSizeInBytes, linedef);

		map->AddLinedef(linedef);

		
		//std::cout << linedef.StartVertex << std::endl;
		//std::cout << linedef.EndVertex << std::endl;
		//std::cout << linedef.Flags << std::endl;
		//std::cout << linedef.LineType << std::endl;
		//std::cout << linedef.SectorTag << std::endl;
		//std::cout << linedef.RightSidedef << std::endl;
		//std::cout << linedef.LeftSidedef << std::endl;
		//std::cout << std::endl;
	}

	return true;
}

bool WADLoader::ReadMapThing(Map* map)
{
	std::cout << "Info: Loading Thing" << std::endl;
	int iMapIndex = FindMapIndex(map);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eTHINGS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "THINGS") != 0)
	{
		return false;
	}

	int iThingSizeInBytes = sizeof(Thing);
	int iThingCount = m_WADDirectories[iMapIndex].LumpSize / iThingSizeInBytes;

	Thing thing;

	for (int i = 0; i < iThingCount; i++)
	{
		m_Reader.ReadThingData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iThingSizeInBytes, thing);

		map->AddThing(thing);
	}

	return true;
}

bool WADLoader::ReadMapNode(Map* map)
{
	std::cout << "Info: Loading Map Node" << std::endl;
	int iMapIndex = FindMapIndex(map);

	if(iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eNODES;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "NODES") != 0)
	{
		return false;
	}

	int iNodeSizeInBytes = sizeof(Node);
	int iNodeCount = m_WADDirectories[iMapIndex].LumpSize / iNodeSizeInBytes;

	Node node;

	for (int i = 0; i < iNodeCount; i++)
	{
		m_Reader.ReadNodeData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iNodeSizeInBytes, node);

		map->AddNode(node);
	}

	return true;
}

bool WADLoader::LoadMapData(Map* map)
{
	
	if (!ReadMapVertex(map))
	{
		std::cout << "Error: Failed to load map vertex data MAP: " << map->GetName() << std::endl;
		return false;
	}
	
	if (!ReadMapLinedef(map))
	{
		std::cout << "Error: Failed to load map linedef data MAP: " << map->GetName() << std::endl;
		return false;
	}

	if (!ReadMapThing(map))
	{
		std::cout << "Error: Failed to load map thing data MAP: " << map->GetName() << std::endl;
		return false;
	}

	if(!ReadMapNode(map))
	{
		std::cout << "Error: Failed to load map node data Map: " << map->GetName() << std::endl;
		return false;
	}
	
	return true;
}
