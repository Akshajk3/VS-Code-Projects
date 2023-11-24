#pragma once

#include "DataTypes.h"

class WADReader
{
public:
	WADReader();
	~WADReader();

	void ReadHeaderData(const uint8_t* pWADData, int offset, Header& header);
	void ReadDirectoryData(const uint8_t* pWADData, int offset, Directory& directory);
	void ReadVertexData(const uint8_t* pWADData, int offset, Vertex& vertex);
	void ReadLineDefData(const uint8_t* pWADData, int offset, LineDef& lineDef);
	void ReadThingData(const uint8_t* pWADData, int offset, Thing& thing);

private:
	uint16_t Read2Bytes(const uint8_t* pWADData, int offset);
	uint32_t Read4Bytes(const uint8_t* pWADData, int offset);
};