#pragma once

#include <iostream>

struct Header
{
	char WADTypes[5];
	uint32_t DirectoryCount;
	uint32_t DirectoryOffset;
};

struct Directory
{
	uint32_t LumpOffset;
	uint32_t LumpSize;
	char LumpName[9];
};

struct Vertex
{
	int16_t x_pos;
	int16_t y_pos;
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

enum EMAPLUMPSINDEX
{
	eTHINGS = 1,
	eLINEDEFS,
	eSIDEDEFS,
	eVERTEXES,
	eSEGS,
	eSSECTORS,
	eNODES,
	eSECTORS,
	eREJECT,
	eBLOCKMAP,
	eCOUNT
};

enum ELINEDEFFLAGS
{
	eBLOCKING = 0,
	eBLOCKINGMONSTERS = 1,
	eTWOSIDED = 4,
	eDONTPEGTOP = 8,
	eDONTPEGBOTTOM = 10,
	eSECRET = 20,
	eBLOCKSOUND = 40,
	eDONTDRAW = 80,
	eDRAW = 100
};
