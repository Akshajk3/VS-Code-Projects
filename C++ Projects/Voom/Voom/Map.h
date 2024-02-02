#pragma once

#include <iostream>
#include <vector>

#include "DataTypes.h"
#include "Player.h"

#include <SDL2/SDL.h>

class Map
{
public:
	Map(SDL_Renderer* renderer, std::string name, Player* player);
	~Map();

	std::string GetName();
	void AddVertex(Vertex& v);
	void AddLinedef(Linedef& l);
	void AddThing(Thing& thing);
	void AddNode(Node& node);
	void RenderAutoMap();
	void RenderAutoMapPlayer();
	void RenderAutoMapWalls();
	void RenderAutoMapNodes();
	void RenderBSPNode(int NodeID);
	void RenderBSPNodes();
	void RenderSubsector(int SubsectorID);
	void SetLumpIndex(int iIndex);

	int GetLumpIndex();
	int RemapXToScreen(int XMapPosition);
	int RemapYToScreen(int YMapPosition);

	bool IsPointOnLeftSide(int XPosition, int YPosition, int NodeID);

protected:
	std::string m_Name;
	std::vector<Vertex> m_Vertexes;
	std::vector<Linedef> m_Linedefs;
	std::vector<Thing> m_Things;
	std::vector<Node> m_Nodes;

	int m_XMin;
	int m_XMax;
	int m_YMin;
	int m_YMax;
	int iRenderXSize;
	int iRenderYSize;
	int m_iAutoMapScaleFactor;
	int m_iLumpIndex;

	Player* m_Player;
	SDL_Renderer* m_Renderer;
};
