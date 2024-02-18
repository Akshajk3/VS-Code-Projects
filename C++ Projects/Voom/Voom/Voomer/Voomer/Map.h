#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "DataTypes.h"
#include "Settings.h"

class Map
{
public:
    Map(std::string name);
    ~Map();
    
    std::string GetName();
    void AddVertex(Vertex& v);
    void AddLinedef(Linedef& l);
    void RenderAutoMap(SDL_Renderer* renderer);
    
    int RemapX(int x, int out_min, int out_max);
    int RemapY(int y, int out_min, int out_max);
    
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
