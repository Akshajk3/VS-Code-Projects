#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "DataTypes.h"


class WADReader
{
public:
	WADReader();
	~WADReader();

	uint16_t Read2Bytes(const uint8_t *pWADData, int offset);
	uint32_t Read4Bytes(const uint8_t *pWADData, int offset);
	void ReadHeaderData(const uint8_t *pWADData, int offset, Header& header);
};
