#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataTypes.h"
#include "Player.h"
#include "ViewRenderer.h"

#include <SDL2/SDL.h>

class Map
{
public:
    Map(std::string Name, Player* player, ViewRenderer* renderer);
    ~Map();
    
    std::string GetName();
    void AddVertex(Vertex& v);
    void AddLinedef(Linedef& l);
    void AddThing(Thing& t);
    void AddNode(Node& n);
    void AddSubsector(Subsector& ss);
    void AddSeg(Seg& s);
    void RenderAutoMap();
    void Render3DView();

    void SetLumpIndex(int Index);
    
    int GetXMin();
    int GetXMax();
    int GetYMin();
    int GetYMax();
    int GetLumpIndex();
    
protected:
    
    void RenderBSPNodes();
    void RenderAutoMapNode(int NodeID);
    void RenderBSPNodes(int NodeID);
    void RenderSubsector(int SubsectorID);
    
    bool IsPointOnLeftSide(int XPosition, int YPosition, int NodeID);
    
    std::string m_Name;
    std::vector<Vertex> m_Vertexes;
    std::vector<Linedef> m_Linedefs;
    std::vector<Thing> m_Things;
    std::vector<Node> m_Nodes;
    std::vector<Subsector> m_Subsectors;
    std::vector<Seg> m_Segs;
    
    int m_XMin;
    int m_XMax;
    int m_YMin;
    int m_YMax;
    int m_RenderXSize;
    int m_RenderYSize;
    int m_AutoMapScaleFactor;
    int m_LumpIndex;
    
    Player* m_Player;
    ViewRenderer* m_ViewRenderer;
};
