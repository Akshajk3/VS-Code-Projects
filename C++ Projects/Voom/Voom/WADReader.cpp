#include "WADReader.h"

WADReader::WADReader()
{
	
}

WADReader::~WADReader()
{
	
}

void WADReader::ReadHeaderData(const uint8_t *pWADData, int offset, Header& header)
{
	header.WADTypes[0] = pWADData[offset];
	header.WADTypes[1] = pWADData[offset + 1];
	header.WADTypes[2] = pWADData[offset + 2];
	header.WADTypes[3] = pWADData[offset + 3];
	header.WADTypes[4] = '\0';

	header.DirectoryCount = Read4Bytes(pWADData, offset + 4);

	header.DirectoryOffset = Read4Bytes(pWADData, offset + 8);
}

uint16_t WADReader::Read2Bytes(const uint8_t *pWADData, int offset)
{
	uint16_t ReadValue;
	std::memcpy(&ReadValue, pWADData + offset, sizeof(uint16_t));
	return ReadValue;
}

uint32_t WADReader::Read4Bytes(const uint8_t *pWADData, int offset)
{
	uint32_t ReadValue;
	std::memcpy(&ReadValue, pWADData + offset, sizeof(uint32_t));
	return ReadValue;
}

