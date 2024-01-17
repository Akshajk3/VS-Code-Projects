#include "Map.h"

Map::Map(std::string name)
	: m_Name(name)
{

}

Map::~Map()
{

}

void Map::AddVertex(Vertex& v)
{
	m_Vertexes.push_back(v);
}

void Map::AddLinedef(Linedef& l)
{
	m_Linedefs.push_back(l);
}

std::string Map::GetName()
{
	return m_Name;
}

std::vector<Vertex> Map::GetVertices()
{
	return m_Vertexes;
}
