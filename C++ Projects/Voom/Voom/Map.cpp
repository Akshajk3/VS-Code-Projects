#pragma once

#include "Map.h"

Map::Map(std::string sName, Player* pPlayer)
	: m_sName(sName), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MAX), m_iAutoMapScaleFactor(15), m_Player(pPlayer)
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

	if (m_XMin > v.XPosition)
	{
		m_XMin = v.XPosition;
	}
	else if (m_XMax < v.XPosition)
	{
		m_XMax = v.XPosition;
	}
	if (m_YMin > v.YPosition)
	{
		m_YMin = v.YPosition;
	}
	else if (m_YMax < v.YPosition)
	{
		m_YMax = v.YPosition;
	}
}

void Map::AddLinedef(LineDef& lineDef)
{
	m_LineDefs.push_back(lineDef);
}

void Map::AddThing(Thing& thing)
{
	if (thing.Type == m_Player->GetID())
	{
		m_Player->SetXPosition(thing.XPosition);
		m_Player->SetYPosition(thing.YPosition);
		m_Player->SetAngle(thing.Angle);
	}

	m_Things.push_back(thing);
}

void Map::RenderAutoMap(SDL_Renderer *pRenderer)
{
    int iXShift = -m_XMin; // Invert the min X value
    int iYShift = -m_YMin; // Invert the min Y value

	RenderAutoMapWall(pRenderer, iXShift, iYShift);
	RenderAutoMapPlayer(pRenderer, iXShift, iYShift);
}

void Map::RenderAutoMapPlayer(SDL_Renderer* renderer, int iXShift, int iYShift)
{
	int iRenderXSize;
	int iRenderYSize;

	SDL_RenderGetLogicalSize(renderer, &iRenderXSize, &iRenderYSize);

	--iRenderXSize;
	--iRenderYSize;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	std::pair<int, int> Direction[] =
	{
		std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(+1, -1),
		std::make_pair(-1, 0), std::make_pair(0, 0), std::make_pair(+1, 0),
		std::make_pair(-1, +1), std::make_pair(0, +1), std::make_pair(+1, +1)
	};

	for (int i = 0; i < 9; i++)
	{
		SDL_RenderDrawPoint(renderer,
			(m_Player->GetXPosition() + iXShift) / m_iAutoMapScaleFactor + Direction[i].first,
			iRenderYSize - (m_Player->GetYPosition() + iYShift) / m_iAutoMapScaleFactor + Direction[i].second);
	}
}

void Map::RenderAutoMapWall(SDL_Renderer* renderer, int iXShift, int iYShift)
{
	int iRenderXSize;
	int iRenderYSize;

	SDL_RenderGetLogicalSize(renderer, &iRenderXSize, &iRenderYSize);

	--iRenderXSize;
	--iRenderYSize;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for (LineDef& l : m_LineDefs)
	{
		Vertex vStart = m_Vertexes[l.StartVertex];
		Vertex vEnd = m_Vertexes[l.EndVertex];

		SDL_RenderDrawLine(renderer,
			(vStart.XPosition + iXShift) / m_iAutoMapScaleFactor,
			iRenderYSize - (vStart.YPosition + iYShift) / m_iAutoMapScaleFactor,
			(vEnd.XPosition + iXShift) / m_iAutoMapScaleFactor,
			iRenderYSize - (vEnd.YPosition + iYShift) / m_iAutoMapScaleFactor);

	}
}

void Map::SetLumpIndex(int iIndex)
{
	m_iLumpIndex = iIndex;
}