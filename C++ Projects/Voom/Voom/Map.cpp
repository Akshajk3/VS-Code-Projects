#include "Map.h"

Map::Map(std::string name, Player* player)
	: m_Name(name), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MIN), m_iAutoMapScaleFactor(15)
{

}

Map::~Map()
{

}

void Map::AddVertex(Vertex& v)
{
	m_Vertexes.push_back(v);

	if (m_XMin > v.x_pos)
	{
		m_XMin = v.x_pos;
	}
	else if (m_XMax < v.x_pos)
	{
		m_XMax = v.x_pos;
	}
	if (m_YMin > v.y_pos)
	{
		m_YMin = v.y_pos;
	}
	else if (m_YMax < v.y_pos)
	{
		m_YMax = v.y_pos;
	}
}

void Map::AddLinedef(Linedef& l)
{
	m_Linedefs.push_back(l);
}

std::string Map::GetName()
{
	return m_Name;
}

void Map::RenderAutoMap(SDL_Renderer* renderer)
{
	int iXShift = -m_XMin;
	int iYShift = -m_YMin;
	
	RenderAutoMapWalls(renderer, iXShift, iYShift);
	RenderAutoMapPlayer(renderer, iXShift, iYShift);
}

void Map::RenderAutoMapWalls(SDL_Renderer* renderer, int iXShift, int iYShift)
{
	int iRenderXSize;
	int iRenderYSize;

	SDL_RenderGetLogicalSize(renderer, &iRenderXSize, &iRenderYSize);

	for (Linedef& l : m_Linedefs)
	{
		Vertex vStart = m_Vertexes[l.StartVertex];
		Vertex vEnd = m_Vertexes[l.EndVertex];

		SDL_RenderDrawLine(renderer,
			(vStart.x_pos + iXShift) / m_iAutoMapScaleFactor,
			iRenderYSize - (vStart.y_pos + iYShift) / m_iAutoMapScaleFactor,
			(vEnd.x_pos + iXShift) / m_iAutoMapScaleFactor,
			iRenderYSize - (vEnd.y_pos + iYShift) / m_iAutoMapScaleFactor);
	}
}

void Map::RenderAutoMapPlayer(SDL_Renderer* renderer, int iXShift, int iYShift)
{
	int iRenderXSize;
	int iRenderYSize;

	SDL_RenderGetLogicalSize(renderer, &iRenderXSize, &iRenderYSize);

	iRenderXSize--;
	iRenderYSize--;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	std::pair<int, int> Direction[] = {
		std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(+1, -1),	// Above Row
		std::make_pair(-1, 0), std::make_pair(0, 0), std::make_pair(+1, 0),		// Center Row
		std::make_pair(-1, +1), std::make_pair(0, +1), std::make_pair(+1, +1)	// Bottom Row
	};

	for (int i = 0; i < 9; i++)
	{
		SDL_RenderDrawPoint(renderer,
			(m_Player->GetXPosition() + iXShift) / m_iAutoMapScaleFactor + Direction[i].first,
			iRenderYSize - (m_Player->GetYPosition() + iYShift) / m_iAutoMapScaleFactor + Direction->second);
	}
}

void Map::AddThing(Thing& thing)
{
	m_Things.push_back(thing);
}