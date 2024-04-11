#pragma once

#include "DataTypes.h"

class WADReader
{
public:
    WADReader();
    ~WADReader();
    
    void ReadHeaderData(const uint8_t* WADData, int offset, Header& header);
    void ReadDirectoryData(const uint8_t* WADData, int offset, Directory& directory);
    void ReadVertexData(const uint8_t* WADData, int offset, Vertex& vertex);
    void ReadLinedefData(const uint8_t* WADData, int offset, WADLinedef& linedef);
    void ReadThingData(const uint8_t* WADData, int offset, Thing& thing);
    void ReadNodeData(const uint8_t* WADData, int offset, Node& node);
    void ReadSubsectorData(const uint8_t* WADData, int offset, Subsector& subsector);
    void ReadSegData(const uint8_t* WADData, int offset, WADSeg& seg);
    void ReadSidedefData(const uint8_t* WADData, int offset, WADSidedef& sidedef);
    void ReadSectorData(const uint8_t* WADData, int offset, WADSector& sector);
    
protected:
    
    uint16_t Read2Bytes(const uint8_t* WADData, int offset);
    uint32_t Read4Bytes(const uint8_t* WADData, int offest);
};
