#pragma once

#include "DataTypes.h"
#include "Player.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Map
{
public:
	Map(std::string sName, Player* pPlayer);
	~Map();

	std::string getName();
	void AddVertex(Vertex& v);
	void AddLinedef(LineDef& l);
	void AddThing(Thing& thing);
	void RenderAutoMap(SDL_Renderer* renderer);
	void RenderAutoMapPlayer(SDL_Renderer* renderer, int iXShift, int iYShift);
	void RenderAutoMapWall(SDL_Renderer* renderer, int iXShift, int iYShift);
	void SetLumpIndex(int iIndex);

protected:
	std::string m_sName;
	std::vector<Vertex> m_Vertexes;
	std::vector<LineDef> m_LineDefs;
	std::vector<Thing> m_Things;

	int m_XMin;
	int m_XMax;
	int m_YMin;
	int m_YMax;
	int m_iAutoMapScaleFactor;
	int m_iLumpIndex;

	Player* m_Player;
};