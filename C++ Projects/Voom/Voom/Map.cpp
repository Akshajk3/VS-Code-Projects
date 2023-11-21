#pragma once

#include "Map.h"

Map::Map(std::string sName)
	: m_sName(sName)
{

}

Map::~Map()
{

}

std::string Map::getName()
{
	return m_sName;
}

void Map::AddVertex(Vertex& v)
{
	m_Vertexes.push_back(v);
}

void Map::AddLinedef(LineDef& lineDef)
{
	m_LineDefs.push_back(lineDef);
}