#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataTypes.h"

class Map
{
public:
    Map(std::string Name);
    ~Map();
    
    std::string GetName();
    void AddVertex(Vertex& v);
    void AddLinedef(Linedef& l);
    
protected:
    std::string m_Name;
    std::vector<Vertex> m_Vertexes;
    std::vector<Linedef> m_Linedefs;
};
