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

bool WADLoader::LoadMapData(Map* map)
{
	if (!ReadMapVertex(map))
	{
		std::cout << "Error: Failed to load map vertex data MAP: " << map->getName() << std::endl;
		return false;
	}

	if (!ReadMapLineDef(map))
	{
		std::cout << "Error: Failed to load map linedef data MAP: " << map->getName() << std::endl;
		return false;
	}

	return true;
}

bool WADLoader::OpenAndLoad()
{
	std::cout << "Info: Loading WAD file: " << m_sWADFilePath << std::endl;

	m_WADFile.open(m_sWADFilePath, std::ifstream::binary);
	if (!m_WADFile.is_open())
	{
		std::cout << "Failed to Open WAD File" << m_sWADFilePath << std::endl;
		return false;
	}

	m_WADFile.seekg(0, m_WADFile.end);
	size_t length = m_WADFile.tellg();

	m_WADData = new uint8_t[length];

	m_WADFile.seekg(std::ifstream::beg);
	m_WADFile.read((char*)m_WADData, length);

	m_WADFile.close();

	std::cout << "Info: Loading Complete" << std::endl;
	return true;
}


bool WADLoader::ReadDirectories()
{
	WADReader reader;

	Header header;

	Directory directory;

	reader.ReadHeaderData(m_WADData, 0, header);

	/*
	std::cout << header.WADType << std::endl;
	std::cout << header.DirectoryCount << std::endl;
	std::cout << header.DirectoryOffset << std::endl;
	std::cout << std::endl << std::endl;
	*/

	for (unsigned int i = 0; i < header.DirectoryCount; i++)
	{
		reader.ReadDirectoryData(m_WADData, header.DirectoryOffset + i * 16, directory);

		m_WADDirectories.push_back(directory);
		
		/*
		std::cout << directory.LumpOffset << std::endl;
		std::cout << directory.LumpSize << std::endl;
		std::cout << directory.LumpName << std::endl;
		std::cout << std::endl << std::endl;
		*/
	}

	return true;
}

int WADLoader::FindMapIndex(Map* map)
{
	for (int i = 0; i < m_WADDirectories.size(); i++)
	{
		if (m_WADDirectories[i].LumpName == map->getName())
		{
			return i;
		}
	}

	return -1;
}

bool WADLoader::ReadMapVertex(Map* map)
{
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
	for (int i = 0; i < iVertexesCount; i++)
	{
		m_Reader.ReadVertexData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iVertexSizeInBytes, vertex);

		map->AddVertex(vertex);

		/*
		std::cout << vertex.XPosition << std::endl;
		std::cout << vertex.YPosition << std::endl;
		std::cout << std::endl << std::endl;
		*/
	}

	return true;
}

bool WADLoader::ReadMapLineDef(Map* map)
{
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

	int iLineDefSizeInBytes = sizeof(LineDef);
	int iLineDefCount = m_WADDirectories[iMapIndex].LumpSize / iLineDefSizeInBytes;

	LineDef linedef;
	for (int i = 0; i < iLineDefCount; i++)
	{
		m_Reader.ReadLineDefData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iLineDefSizeInBytes, linedef);

		map->AddLinedef(linedef);

		/*
		std::cout << linedef.StartVertex << std::endl;
		std::cout << linedef.EndVertex << std::endl;
		std::cout << linedef.Flags << std::endl;
		std::cout << linedef.LineType << std::endl;
		std::cout << linedef.SectorTag << std::endl;
		std::cout << linedef.RightSideDef << std::endl;
		std::cout << linedef.LeftSideDef << std::endl;
		
		std::cout << std::endl << std::endl;
		*/
	}

	return true;
}

bool WADLoader::ReadMapThing(Map* map)
{
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

	int iThingsSizeInBytes = sizeof(Thing);
	int iThingsCount = m_WADDirectories[iMapIndex].LumpSize / iThingsSizeInBytes;

	Thing thing;
	for (int i = 0; i < iThingsCount; i++)
	{
		m_Reader.ReadThingData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iThingsSizeInBytes, thing);

		map->AddThing(thing);
	}

	return true;
}