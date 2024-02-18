#include "Map.h"


Map::Map(std::string name)
    : name(name)
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

void Map::RenderAutoMap()
{
    
}
