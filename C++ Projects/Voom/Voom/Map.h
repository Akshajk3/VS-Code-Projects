#pragma once

#include <iostream>
#include <vector>
#include "DataTypes.h"

class Map
{
public:
	Map(std::string name);
	~Map();

	std::string GetName();
	std::vector<Vertex> GetVertices();
	void AddVertex(Vertex& v);
	void AddLinedef(Linedef& l);

protected:
	std::string m_Name;
	std::vector<Vertex> m_Vertexes;
	std::vector<Linedef> m_Linedefs;
};
