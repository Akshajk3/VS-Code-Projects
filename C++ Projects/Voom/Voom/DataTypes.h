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

struct Thing
{
	int16_t XPos;
	int16_t YPos;
	uint16_t Angle;
	uint16_t Type;
	uint16_t Flag;
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

	int16_t RightChild;
	int16_t LeftChild;
};
