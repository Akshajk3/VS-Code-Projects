#pragma once

#include "DataTypes.h"

#include <string>
#include <vector>

class Map
{
public:
	Map(std::string sName);
	~Map();

	std::string getName();
	void AddVertex(Vertex& v);
	void AddLinedef(LineDef& l);

protected:
	std::string m_sName;
	std::vector<Vertex> m_Vertexes;
	std::vector<LineDef> m_LineDefs;
};