#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataTypes.h"
#include "Player.h"
#include "ViewRenderer.h"
#include "Thing.h"

#include <SDL2/SDL.h>

class Map
{
public:
    Map(std::string Name, Player* player, ViewRenderer* renderer, Things* things);
    ~Map();
    
    std::string GetName();
    void AddVertex(Vertex& v);
    void AddLinedef(WADLinedef& l);
    void AddNode(Node& n);
    void AddSubsector(Subsector& ss);
    void AddSeg(WADSeg& s);
    void AddSidedef(WADSidedef& side);
    void AddSector(WADSector& sec);
    void RenderAutoMap();
    void Render3DView();
    void Init();

    void SetLumpIndex(int Index);
    
    int GetXMin();
    int GetXMax();
    int GetYMin();
    int GetYMax();
    int GetLumpIndex();
    
    Things* GetThing();
    
protected:
    void BuildSectors();
    void BuildSidedefs();
    void BuildSegs();
    void BuildLinedefs();
    
    void RenderBSPNodes();
    void RenderAutoMapNode(int NodeID);
    void RenderBSPNodes(int NodeID);
    void RenderSubsector(int SubsectorID);
    
    bool IsPointOnLeftSide(int XPosition, int YPosition, int NodeID);
    
    std::string m_Name;
    std::vector<Vertex> m_Vertexes;
    std::vector<Sector> m_Sectors;
    std::vector<Sidedef> m_Sidedefs;
    std::vector<Linedef> m_Linedefs;
    std::vector<Node> m_Nodes;
    std::vector<Subsector> m_Subsectors;
    std::vector<Seg> m_Segs;
    
    std::vector<WADSector>* m_pSectors;
    std::vector<WADSidedef>* m_pSidedefs;
    std::vector<WADLinedef>* m_pLinedefs;
    std::vector<WADSeg>* m_pSegs;
    
    int m_XMin;
    int m_XMax;
    int m_YMin;
    int m_YMax;
    int m_RenderXSize;
    int m_RenderYSize;
    int m_AutoMapScaleFactor;
    int m_LumpIndex;
    
    Player* m_Player;
    Things* m_Things;
    ViewRenderer* m_ViewRenderer;
};
