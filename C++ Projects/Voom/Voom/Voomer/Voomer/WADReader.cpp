#include "WADReader.h"
#include <cstring>

WADReader::WADReader()
{
    
}

WADReader::~WADReader()
{
    
}

uint16_t WADReader::Read2Bytes(const uint8_t *WADData, int offset)
{
    uint16_t ReadValue;
    std::memcpy(&ReadValue, WADData + offset, sizeof(uint16_t));
    return ReadValue;
}

uint32_t WADReader::Read4Bytes(const uint8_t *WADData, int offest)
{
    uint32_t ReadValue;
    std::memcpy(&ReadValue, WADData + offest, sizeof(uint32_t));
    return ReadValue;
}

void WADReader::ReadHeaderData(const uint8_t *WADData, int offset, Header &header)
{
    header.WADType[0] = WADData[offset];
    header.WADType[1] = WADData[offset + 1];
    header.WADType[2] = WADData[offset + 2];
    header.WADType[3] = WADData[offset + 3];
    header.WADType[4] = '\0';
    
    header.DirectoryCount = Read4Bytes(WADData, offset + 4);
    header.DirectoryOffset = Read4Bytes(WADData, offset + 8);
}

void WADReader::ReadDirectoryData(const uint8_t *WADData, int offset, Directory &directory)
{
    directory.LumpOffset = Read4Bytes(WADData, offset);
    
    directory.LumpSize = Read4Bytes(WADData, offset + 4);
    
    directory.LumpName[0] = WADData[offset + 8];
    directory.LumpName[1] = WADData[offset + 9];
    directory.LumpName[2] = WADData[offset + 10];
    directory.LumpName[3] = WADData[offset + 11];
    directory.LumpName[4] = WADData[offset + 12];
    directory.LumpName[5] = WADData[offset + 13];
    directory.LumpName[6] = WADData[offset + 14];
    directory.LumpName[7] = WADData[offset + 15];
    directory.LumpName[8] = '\0';
}

void WADReader::ReadVertexData(const uint8_t *WADData, int offset, Vertex &vertex)
{
    vertex.xPos = Read2Bytes(WADData, offset);
    vertex.yPos = Read2Bytes(WADData, offset);
}

void WADReader::ReadLinedefData(const uint8_t *WADData, int offset, Linedef &linedef)
{
    linedef.StartVertex = Read2Bytes(WADData, offset);
    linedef.EndVertex = Read2Bytes(WADData, offset + 2);
    linedef.Flags = Read2Bytes(WADData, offset = 4);
    linedef.LineType = Read2Bytes(WADData, offset + 6);
    linedef.SectorTag = Read2Bytes(WADData, offset + 8);
    linedef.RightSidedef = Read2Bytes(WADData, offset + 10);
    linedef.LeftSidedef = Read2Bytes(WADData, offset + 12);
}
