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

void WADReader::ReadDirectoryData(const uint8_t *pWADData, int offset, Directory& directory)
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

void WADReader::ReadVertexData(const uint8_t *pWADData, int offset, Vertex& vertex)
{
	vertex.x_pos = Read2Bytes(pWADData, offset);
	vertex.y_pos = Read2Bytes(pWADData, offset + 2);
}

void WADReader::ReadLinedefData(const uint8_t *pWADData, int offset, Linedef& linedef)
{
	linedef.StartVertex = Read2Bytes(pWADData, offset);
	linedef.EndVertex = Read2Bytes(pWADData, offset + 2);
	linedef.Flags = Read2Bytes(pWADData, offset + 4);
	linedef.LineType = Read2Bytes(pWADData, offset + 6);
	linedef.SectorTag = Read2Bytes(pWADData, offset + 8);
	linedef.RightSidedef = Read2Bytes(pWADData, offset + 10);
	linedef.LeftSidedef = Read2Bytes(pWADData, offset + 12);
}

void WADReader::ReadThingData(const uint8_t* pWADData, int offset, Thing& thing)
{
	thing.XPos = Read2Bytes(pWADData, offset);
	thing.YPos = Read2Bytes(pWADData, offset + 2);
	thing.Angle = Read2Bytes(pWADData, offset + 4);
	thing.Type = Read2Bytes(pWADData, offset + 6);
	thing.Flag = Read2Bytes(pWADData, offset + 8);
}

void WADReader::ReadNodeData(const uint8_t *pWADData, int offset, Node& node)
{
	node.XPartition = Read2Bytes(pWADData, offset);
	node.YPartition = Read2Bytes(pWADData, offset + 2);
	node.ChangeXPartition = Read2Bytes(pWADData, offset + 4);
	node.ChangeYPartition = Read2Bytes(pWADData, offset + 6);

	node.RightBoxTop = Read2Bytes(pWADData, offset + 8);
	node.RightBoxBottom = Read2Bytes(pWADData, offset + 10);
	node.RightBoxLeft = Read2Bytes(pWADData, offset + 12);
	node.RightBoxRight = Read2Bytes(pWADData, offset + 14);

	node.LeftBoxTop = Read2Bytes(pWADData, offset + 16);
	node.LeftBoxBottom = Read2Bytes(pWADData, offset + 18);
	node.LeftBoxLeft = Read2Bytes(pWADData, offset + 20);
	node.LeftBoxRight = Read2Bytes(pWADData, offset + 22);

	node.RightChild = Read2Bytes(pWADData, offset + 24);
	node.LeftChild = Read2Bytes(pWADData, offset + 26);
}

uint16_t WADReader::Read2Bytes(const uint8_t *pWADData, int offset)
{
	uint16_t ReadValue;
	memcpy(&ReadValue, pWADData + offset, sizeof(uint16_t));
	return ReadValue;
}


uint32_t WADReader::Read4Bytes(const uint8_t *pWADData, int offset)
{
	uint32_t ReadValue;
	memcpy(&ReadValue, pWADData + offset, sizeof(uint32_t));
	return ReadValue;
}

