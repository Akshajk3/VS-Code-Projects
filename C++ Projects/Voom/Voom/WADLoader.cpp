#include "WADLoader.h"

WADLoader::WADLoader(std::string sWADFilePath)
	: m_WADData(NULL), m_sWADFilePath(sWADFilePath)
{
	
}

WADLoader::~WADLoader()
{
    delete[] m_WADData;
    m_WADData = NULL;
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
		std::cout << "Error: Failed to open WAD file" << m_sWADFilePath << std::endl;
		return false;
	}

	m_WADFile.seekg(0, m_WADFile.end);
	size_t length = m_WADFile.tellg();

	m_WADData = new uint8_t[length];

	m_WADFile.seekg(std::ifstream::beg);
	m_WADFile.read((char*)m_WADData, length);
	
	m_WADFile.close();
	
	return true;
}

bool WADLoader::ReadDirectories()
{
	std::cout << "Reading" << std::endl;

	WADReader reader;

	Header header;
	reader.ReadHeaderData(m_WADData, 0, header);

	std::cout << header.WADTypes << std::endl;
	std::cout << header.DirectoryCount << std::endl;
	std::cout << header.DirectoryOffset << std::endl;
	std::cout << std::endl << std::endl;
	return true;
}
