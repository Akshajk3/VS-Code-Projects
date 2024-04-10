#pragma once

#include <cstdint>

#define SUBSECTORIDENTIFIER 0x8000
#define PI 3.14159265358979f

enum MAPLUMPSINDEX
{
    THINGS = 1,
    LINEDEFS,
    SIDEDEFS,
    VERTEXES,
    SEGS,
    SSECTORS,
    NODES,
    SECTORS,
    REJECT,
    BLOCKMAP,
    COUNT
};

enum LINEDEFFLAGS
{
    BLOCKING = 0,
    BLOCKMONSTERS = 1,
    TWOSIDED = 2,
    DONTPEGTOP = 4,
    DONTPEGBOTTOM = 8,
    SECRET = 16,
    SOUNDBLOCK = 32,
    DONTDRAW = 64,
    DRAW = 128
};

struct Subsector
{
    uint16_t SegCount;
    uint16_t FirstSegID;
};

struct Seg
{
    uint16_t StartVertexID;
    uint16_t EndVertexID;
    uint16_t Angle;
    uint16_t LinedefID;
    uint16_t Direction;
    uint16_t Offset;
};

struct Node
{
    int16_t XPartition;
    int16_t YPartition;
    int16_t ChangeXPartition;
    int16_t ChangeYPartition;
    
    int16_t RightBoxTop;
    int16_t RightBoxBottom;
    int16_t RightBoxLeft;
    int16_t RightBoxRight;
    
    int16_t LeftBoxTop;
    int16_t LeftBoxBottom;
    int16_t LeftBoxLeft;
    int16_t LeftBoxRight;
    
    uint16_t RightChildID;
    uint16_t LeftChildID;
};

struct Thing
{
    int16_t XPosition;
    int16_t YPosition;
    uint16_t Angle;
    uint16_t Type;
    uint16_t Flag;
};

struct Vertex
{
    int16_t xPos;
    int16_t yPos;
};

struct Linedef
{
    uint16_t StartVertex;
    uint16_t EndVertex;
    uint16_t Flags;
    uint16_t LineType;
    uint16_t SectorTag;
    uint16_t RightSidedef;
    uint16_t LeftSidedef;
};

struct Header
{
    char WADType[5];
    uint32_t DirectoryCount;
    uint32_t DirectoryOffset;
};

struct Directory
{
    uint32_t LumpOffset;
    uint32_t LumpSize;
    char LumpName[9];
};
