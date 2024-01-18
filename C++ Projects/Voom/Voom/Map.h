#pragma once

#include <iostream>
#include <vector>

#include "DataTypes.h"
#include "Player.h"

#include <SDL2/SDL.h>

class Map
{
public:
	Map(std::string name, Player* player);
	~Map();

	std::string GetName();
	void AddVertex(Vertex& v);
	void AddLinedef(Linedef& l);
	void AddThing(Thing& thing);
	void RenderAutoMap(SDL_Renderer* renderer);
	void RenderAutoMapPlayer(SDL_Renderer* renderer, int iXShift, int iYShift);
	void RenderAutoMapWalls(SDL_Renderer* renderer, int iXShift, int iYShift);

protected:
	std::string m_Name;
	std::vector<Vertex> m_Vertexes;
	std::vector<Linedef> m_Linedefs;
	std::vector<Thing> m_Things;
	Player* m_Player;
	int m_XMin;
	int m_XMax;
	int m_YMin;
	int m_YMax;
	int m_iAutoMapScaleFactor;
};
