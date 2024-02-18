#pragma once

#include <iostream>

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

enum LUMP_INDICES
{
    THINGS = 1,
    LINEDEFS = 2,
    SIDEDEFS = 3,
    VERTEXES = 4,
    SEGS = 5,
    SSECTORS = 6,
    NODES = 7,
    SECTORS = 8,
    REJECT = 9,
    BLOCKMAP = 10
};

struct Vertex
{
    int16_t XPosition;
    int16_t YPosition;
};

struct Linedef
{
    uint16_t StartVertex;
    uint16_t EndVertex;
    uint16_t Flags;
    uint16_t LineType;
    uint16_t SectorTag;
    uint16_t FrontSidedef;
    uint16_t BackSidedef;
};
