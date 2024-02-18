#pragma once

#include <iostream>
#include "DataTypes.h"


class WADReader
{
public:
    WADReader();
    ~WADReader();
    
    void ReadHeaderData(const uint8_t* WADData, int offset, Header& header);
    void ReadDirectoryData(const uint8_t* WADData, int offset, Directory& directory);
    void ReadVertexData(const uint8_t* WADData, int offset, Vertex& vertex);
    void ReadLinedefData(const uint8_t* WADData, int offset, Linedef& linedef);
    
private:
    uint16_t Read2Bytes(const uint8_t* WADData, int offset);
    uint32_t Read4Bytes(const uint8_t* WADData, int offset);
};
