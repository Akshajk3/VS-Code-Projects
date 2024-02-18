#pragma once

#include <iostream>

#include "DataTypes.h"

class Map
{
public:
    Map(std::string name);
    ~Map();
    
    std::string GetName();
    void AddVertex(Vertex& v);
    void AddLinedef(Linedef& l);
    void RenderAutoMap();
    
private:
    std::string name;
    std::vector<Vertex> Vertexes;
    std::vector<Linedef> Linedefs;
    
    int XMin;
    int XMax;
    int YMin;
    int YMax;
    int AutoMapScaleFactor;
};
