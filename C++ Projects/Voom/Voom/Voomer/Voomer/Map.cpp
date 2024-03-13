#include "Map.h"
#include <SDL2/SDL.h>


Map::Map(std::string name)
    : name(name), XMin(INT_MAX), XMax(INT_MIN), YMin(INT_MAX), YMax(INT_MIN), AutoMapScaleFactor(15)
{
    
}

Map::~Map()
{
    
}

std::string Map::GetName()
{
    return name;
}

void Map::AddVertex(Vertex &v)
{
    Vertexes.push_back(v);
    
    if (XMin > v.XPosition)
    {
        XMin = v.XPosition;
    }
    else if (XMax < v.XPosition)
    {
        XMax = v.XPosition;
    }
    
    if (YMin > v.YPosition)
    {
        YMin = v.YPosition;
    }
    else if (YMax < v.XPosition)
    {
        YMax = v.YPosition;
    }
}

void Map::AddLinedef(Linedef &l)
{
    Linedefs.push_back(l);
}

void Map::RenderAutoMap(SDL_Renderer *pRenderer)
{
    int iXShift = -XMin; // Invert the min X value
    int iYShift = -YMin; // Invert the min Y value

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (Linedef &l : Linedefs)
    {
        Vertex vStart = Vertexes[l.StartVertex]; // Read the first point
        Vertex vEnd = Vertexes[l.EndVertex]; // Read the second point

        //Draw a line between those 2 points and scale it down by a factor
        SDL_RenderDrawLine(pRenderer,
            (vStart.XPosition + iXShift) / AutoMapScaleFactor,
            (vStart.YPosition + iYShift) / AutoMapScaleFactor,
            (vEnd.XPosition + iXShift) / AutoMapScaleFactor,
            (vEnd.YPosition + iYShift) / AutoMapScaleFactor);
    }
}
