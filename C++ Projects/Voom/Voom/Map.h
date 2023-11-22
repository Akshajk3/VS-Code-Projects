#pragma once

#include "DataTypes.h"

#include <SDL2/SDL.h>
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
	void RenderAutoMap(SDL_Renderer* renderer);

protected:
	std::string m_sName;
	std::vector<Vertex> m_Vertexes;
	std::vector<LineDef> m_LineDefs;

	int m_XMin;
	int m_XMax;
	int m_YMin;
	int m_YMax;
	int m_iAutoMapScaleFactor;
};