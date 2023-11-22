#pragma once

#include "Map.h"

Map::Map(std::string sName)
	: m_sName(sName), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MAX), m_iAutoMapScaleFactor(15)
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

void Map::RenderAutoMap(SDL_Renderer *pRenderer)
{
    int iXShift = -m_XMin; // Invert the min X value
    int iYShift = -m_YMin; // Invert the min Y value

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (LineDef &l : m_LineDefs)
    {
        Vertex vStart = m_Vertexes[l.StartVertex]; // Read the first point
        Vertex vEnd = m_Vertexes[l.EndVertex]; // Read the second point

        //Draw a line between those 2 points and scale it down by a factor
        SDL_RenderDrawLine(pRenderer,
            (vStart.XPosition + iXShift) / m_iAutoMapScaleFactor,
            (vStart.YPosition + iYShift) / m_iAutoMapScaleFactor,
            (vEnd.XPosition + iXShift) / m_iAutoMapScaleFactor,
            (vEnd.YPosition + iYShift) / m_iAutoMapScaleFactor);
    }
}