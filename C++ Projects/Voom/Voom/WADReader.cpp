#include "WADReader.h"

#include <memory>

WADReader::WADReader()
{

}

WADReader::~WADReader()
{

}

uint16_t WADReader::Read2Bytes(const uint8_t* pWADData, int offset)
{
	uint16_t ReadValue;
	std::memcpy(&ReadValue, pWADData + offset, sizeof(uint16_t));
	return ReadValue;
}

uint32_t WADReader::Read4Bytes(const uint8_t* pWADData, int offset)
{
	uint32_t ReadValue;
	std::memcpy(&ReadValue, pWADData + offset, sizeof(uint32_t));
	return ReadValue;
}

void WADReader::ReadHeaderData(const uint8_t* pWADData, int offset, Header& header)
{
	header.WADType[0] = pWADData[offset];
	header.WADType[1] = pWADData[offset + 1];
	header.WADType[2] = pWADData[offset + 2];
	header.WADType[3] = pWADData[offset + 3];
	header.WADType[4] = '\0';

	header.DirectoryCount = Read4Bytes(pWADData, offset + 4);
	header.DirectoryOffset = Read4Bytes(pWADData, offset + 8);
}

void WADReader::ReadDirectoryData(const uint8_t* pWADData, int offset, Directory& directory)
{
	directory.LumpOffset = Read4Bytes(pWADData, offset);

	directory.LumpSize = Read4Bytes(pWADData, offset + 4);

	directory.LumpName[0] = pWADData[offset + 8];
	directory.LumpName[1] = pWADData[offset + 9];
	directory.LumpName[2] = pWADData[offset + 10];
	directory.LumpName[3] = pWADData[offset + 11];
	directory.LumpName[4] = pWADData[offset + 12];
	directory.LumpName[5] = pWADData[offset + 13];
	directory.LumpName[6] = pWADData[offset + 14];
	directory.LumpName[7] = pWADData[offset + 15];
	directory.LumpName[8] = '\0';
}

void WADReader::ReadVertexData(const uint8_t* pWADData, int offset, Vertex& vertex)
{
	vertex.XPosition = Read2Bytes(pWADData, offset);
	vertex.YPosition = Read2Bytes(pWADData, offset + 2);
}

void WADReader::ReadLineDefData(const uint8_t* pWADData, int offset, LineDef& lineDef)
{
	lineDef.StartVertex = Read2Bytes(pWADData, offset);
	lineDef.EndVertex = Read2Bytes(pWADData, offset + 2);
	lineDef.Flags = Read2Bytes(pWADData, offset + 4);
	lineDef.LineType = Read2Bytes(pWADData, offset + 6);
	lineDef.SectorTag = Read2Bytes(pWADData, offset + 8);
	lineDef.RightSideDef = Read2Bytes(pWADData, offset + 10);
	lineDef.LeftSideDef = Read2Bytes(pWADData, offset + 12);
}