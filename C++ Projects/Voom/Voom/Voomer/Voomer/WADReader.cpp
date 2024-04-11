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
    vertex.yPos = Read2Bytes(WADData, offset + 2);
}

void WADReader::ReadLinedefData(const uint8_t *WADData, int offset, WADLinedef &linedef)
{
    linedef.StartVertex = Read2Bytes(WADData, offset);
    linedef.EndVertex = Read2Bytes(WADData, offset + 2);
    linedef.Flags = Read2Bytes(WADData, offset = 4);
    linedef.LineType = Read2Bytes(WADData, offset + 6);
    linedef.SectorTag = Read2Bytes(WADData, offset + 8);
    linedef.RightSidedef = Read2Bytes(WADData, offset + 10);
    linedef.LeftSidedef = Read2Bytes(WADData, offset + 12);
}

void WADReader::ReadThingData(const uint8_t *WADData, int offset, Thing &thing)
{
    thing.XPosition = Read2Bytes(WADData, offset);
    thing.YPosition = Read2Bytes(WADData, offset + 2);
    thing.Angle = Read2Bytes(WADData, offset + 4);
    thing.Type = Read2Bytes(WADData, offset + 6);
    thing.Flag = Read2Bytes(WADData, offset + 8);
}

void WADReader::ReadNodeData(const uint8_t *WADData, int offset, Node &node)
{
    node.XPartition = Read2Bytes(WADData, offset);
    node.YPartition = Read2Bytes(WADData, offset + 2);
    node.ChangeXPartition = Read2Bytes(WADData, offset + 4);
    node.ChangeYPartition = Read2Bytes(WADData, offset + 6);
    
    node.RightBoxTop = Read2Bytes(WADData, offset + 8);
    node.RightBoxBottom = Read2Bytes(WADData, offset + 10);
    node.RightBoxLeft = Read2Bytes(WADData, offset + 12);
    node.RightBoxRight = Read2Bytes(WADData, offset + 14);
    
    node.LeftBoxTop = Read2Bytes(WADData, offset + 16);
    node.LeftBoxBottom = Read2Bytes(WADData, offset + 18);
    node.LeftBoxLeft = Read2Bytes(WADData, offset + 20);
    node.LeftBoxRight = Read2Bytes(WADData, offset + 22);
    
    node.RightChildID = Read2Bytes(WADData, offset + 24);
    node.LeftChildID = Read2Bytes(WADData, offset + 26);
}

void WADReader::ReadSubsectorData(const uint8_t *WADData, int offset, Subsector &subsector)
{
    subsector.SegCount = Read2Bytes(WADData, offset);
    subsector.FirstSegID = Read2Bytes(WADData, offset + 2);
}

void WADReader::ReadSegData(const uint8_t *WADData, int offset, WADSeg &seg)
{
    seg.StartVertexID = Read2Bytes(WADData, offset);
    seg.EndVertexID = Read2Bytes(WADData, offset + 2);
    seg.Angle = Read2Bytes(WADData, offset + 4);
    seg.LinedefID = Read2Bytes(WADData, offset + 6);
    seg.Direction = Read2Bytes(WADData, offset + 8);
    seg.Offset = Read2Bytes(WADData, offset + 10);
}

void WADReader::ReadSidedefData(const uint8_t *WADData, int offset, WADSidedef &sidedef)
{
    sidedef.XOffset = Read2Bytes(WADData, offset);
    sidedef.YOffset = Read2Bytes(WADData, offset + 2);
    
    sidedef.UpperTexture[0] = WADData[offset + 4];
    sidedef.UpperTexture[1] = WADData[offset + 5];
    sidedef.UpperTexture[2] = WADData[offset + 6];
    sidedef.UpperTexture[3] = WADData[offset + 7];
    sidedef.UpperTexture[4] = WADData[offset + 8];
    sidedef.UpperTexture[5] = WADData[offset + 9];
    sidedef.UpperTexture[6] = WADData[offset + 10];
    sidedef.UpperTexture[7] = WADData[offset + 11];
    
    sidedef.LowerTexture[0] = WADData[offset + 12];
    sidedef.LowerTexture[1] = WADData[offset + 13];
    sidedef.LowerTexture[2] = WADData[offset + 14];
    sidedef.LowerTexture[3] = WADData[offset + 15];
    sidedef.LowerTexture[4] = WADData[offset + 16];
    sidedef.LowerTexture[5] = WADData[offset + 17];
    sidedef.LowerTexture[6] = WADData[offset + 18];
    sidedef.LowerTexture[7] = WADData[offset + 19];
    
    sidedef.MiddleTexture[0] = WADData[offset + 20];
    sidedef.MiddleTexture[1] = WADData[offset + 21];
    sidedef.MiddleTexture[2] = WADData[offset + 22];
    sidedef.MiddleTexture[3] = WADData[offset + 23];
    sidedef.MiddleTexture[4] = WADData[offset + 24];
    sidedef.MiddleTexture[5] = WADData[offset + 25];
    sidedef.MiddleTexture[6] = WADData[offset + 26];
    sidedef.MiddleTexture[7] = WADData[offset + 27];
    
    sidedef.SectorID = Read2Bytes(WADData, offset + 28);
}

void WADReader::ReadSectorData(const uint8_t *WADData, int offset, WADSector &sector)
{
    sector.FloorHeight = Read2Bytes(WADData, offset);
    sector.CeilingHeight = Read2Bytes(WADData, offset + 2);
    
    sector.FloorTexture[0] = WADData[offset + 4];
    sector.FloorTexture[1] = WADData[offset + 5];
    sector.FloorTexture[2] = WADData[offset + 6];
    sector.FloorTexture[3] = WADData[offset + 7];
    sector.FloorTexture[4] = WADData[offset + 8];
    sector.FloorTexture[5] = WADData[offset + 9];
    sector.FloorTexture[6] = WADData[offset + 10];
    sector.FloorTexture[7] = WADData[offset + 11];
    
    sector.CeilingTexture[0] = WADData[offset + 12];
    sector.CeilingTexture[1] = WADData[offset + 13];
    sector.CeilingTexture[2] = WADData[offset + 14];
    sector.CeilingTexture[3] = WADData[offset + 15];
    sector.CeilingTexture[4] = WADData[offset + 16];
    sector.CeilingTexture[5] = WADData[offset + 17];
    sector.CeilingTexture[6] = WADData[offset + 18];
    sector.CeilingTexture[7] = WADData[offset + 19];
    
    sector.LightLevel = Read2Bytes(WADData, offset + 20);
    sector.Type = Read2Bytes(WADData, offset + 22);
    sector.Tag = Read2Bytes(WADData, offset + 24);
}
