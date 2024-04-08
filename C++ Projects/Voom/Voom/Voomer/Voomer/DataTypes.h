#pragma once

#include <cstdint>

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
