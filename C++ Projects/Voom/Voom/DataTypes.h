#pragma once

#include <cstdint>

enum ELINEDEFFLAGS
{
	eBLOCKING = 0,
	eBLOCKINGMONSTERS = 1,
	eTWOSIDED = 2,
	eDONTPEGTOP = 4,
	eDONTPEGBOTTOM = 8,
	eSECRET = 16,
	eSOUNDBLOCK = 32,
	eDONTDRAW = 64,
	eDRAW = 128
};

enum EMAPLUMPSINDEX
{
	eTHINGS = 1,
	eLINEDEFS,
	eSIDEDDEFS,
	eVERTEXES,
	eSEAGS,
	eSSECTORS,
	eNODES,
	eSECTORS,
	eREJECTS,
	eBLOCKMAP,
	eCOUNT
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

struct Vertex
{
	int16_t XPosition;
	int16_t YPosition;
};

struct LineDef
{
	uint16_t StartVertex;
	uint16_t EndVertex;
	uint16_t Flags;
	uint16_t LineType;
	uint16_t SectorTag;
	uint16_t RightSideDef;
	uint16_t LeftSideDef;
};