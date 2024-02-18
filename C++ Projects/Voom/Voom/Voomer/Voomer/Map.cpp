#include "Map.h"


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
}

void Map::AddLinedef(Linedef &l)
{
    Linedefs.push_back(l);
}

void Map::RenderAutoMap(SDL_Renderer* renderer)
{
    int XShift = -XMin;
    int YShift = -YMin;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(Linedef& l : Linedefs)
    {
        Vertex VStart = Vertexes[l.StartVertex];
        Vertex VEnd = Vertexes[l.EndVertex];
        SDL_RenderDrawLine(renderer,
                           (VStart.XPosition + XShift) / AutoMapScaleFactor,
                           (VStart.YPosition + XShift) / AutoMapScaleFactor,
                           (VEnd.XPosition + XShift) / AutoMapScaleFactor,
                           (VEnd.YPosition + XShift) / AutoMapScaleFactor);
    }
}

int Map::RemapX(int x, int out_min, int out_max)
{
    return 0;
}

int Map::RemapY(int y, int out_min, int out_max)
{
    return 0;
}
