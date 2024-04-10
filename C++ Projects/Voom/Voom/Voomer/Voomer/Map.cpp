#include "Map.h"


Map::Map(std::string name, Player* player, ViewRenderer* renderer)
 : m_Name(name), m_Player(player), m_ViewRenderer(renderer), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MIN), m_AutoMapScaleFactor(15), m_LumpIndex(-1)
{

}

Map::~Map()
{
    
}

std::string Map::GetName()
{
    return m_Name;
}

void Map::AddVertex(Vertex &v)
{
    m_Vertexes.push_back(v);
    
    if (m_XMin > v.xPos)
        m_XMin = v.xPos;
    else if (m_XMax < v.xPos)
        m_XMax = v.xPos;
    
    if (m_YMin > v.yPos)
        m_YMin = v.yPos;
    else if (m_YMax < v.yPos)
        m_YMax = v.yPos;
}

void Map::AddLinedef(Linedef &l)
{
    m_Linedefs.push_back(l);
}

void Map::AddThing(Thing &t)
{
    if (t.Type == m_Player->GetID())
    {
        m_Player->SetXPosition(t.XPosition);
        m_Player->SetYPosition(t.YPosition);
        m_Player->SetAngle(t.Angle);
    }
    
    m_Things.push_back(t);
}

void Map::AddNode(Node& n)
{
    m_Nodes.push_back(n);
}

void Map::AddSubsector(Subsector &ss)
{
    m_Subsectors.push_back(ss);
}

void Map::AddSeg(Seg& s)
{
    m_Segs.push_back(s);
}

void Map::RenderAutoMap()
{
    m_ViewRenderer->SetDrawColor(255, 255, 255);
    
    for (Linedef &l : m_Linedefs)
    {
        Vertex vStart = m_Vertexes[l.StartVertex];
        Vertex vEnd = m_Vertexes[l.EndVertex];
        
        m_ViewRenderer->DrawLine(vStart.xPos, vStart.yPos, vEnd.xPos, vEnd.yPos);
    }
}

void Map::Render3DView()
{
    RenderBSPNodes();
}

void Map::RenderAutoMapNode(int NodeID)
{
    Node node = m_Nodes[NodeID];
    
    m_ViewRenderer->SetDrawColor(0, 255, 0);
    m_ViewRenderer->DrawRect(node.RightBoxLeft, node.RightBoxTop, node.RightBoxRight, node.RightBoxBottom);
    
    m_ViewRenderer->SetDrawColor(255, 0, 0);
    m_ViewRenderer->DrawRect(node.LeftBoxLeft, node.LeftBoxTop, node.LeftBoxRight, node.LeftBoxBottom);
    
    m_ViewRenderer->SetDrawColor(0, 0, 255);
    m_ViewRenderer->DrawRect(node.XPartition, node.YPartition, node.XPartition + node.ChangeXPartition, node.YPartition + node.ChangeYPartition);
}

void Map::RenderBSPNodes(int NodeID)
{
    if (NodeID & SUBSECTORIDENTIFIER)
    {
        RenderSubsector(NodeID & (~SUBSECTORIDENTIFIER));
        return;
    }
    
    bool isOnLeft = IsPointOnLeftSide(m_Player->GetXPosition(), m_Player->GetYPosition(), NodeID);
    
    if (isOnLeft)
    {
        RenderBSPNodes(m_Nodes[NodeID].LeftChildID);
        RenderBSPNodes(m_Nodes[NodeID].RightChildID);
    }
    else
    {
        RenderBSPNodes(m_Nodes[NodeID].RightChildID);
        RenderBSPNodes(m_Nodes[NodeID].LeftChildID);
    }
}

void Map::RenderBSPNodes()
{
    RenderBSPNodes(m_Nodes.size() - 1);
}

void Map::RenderSubsector(int SubsectorID)
{
    Subsector subsector = m_Subsectors[SubsectorID];
    m_ViewRenderer->SetDrawColor(rand() % 255, rand() % 255, rand() % 255);
    
    for (int i = 0; i < subsector.SegCount; i++)
    {
        Seg seg = m_Segs[subsector.FirstSegID + i];
        Angle V1Angle, V2Angle;
        
        if (m_Player->ClipVertexesInFOV(m_Vertexes[seg.StartVertexID], m_Vertexes[seg.EndVertexID], V1Angle, V2Angle))
        {
            
            m_ViewRenderer->AddWallInFOV(seg, V1Angle, V2Angle);
        }
    }
    
    //SDL_RenderPresent(m_Renderer);
    //SDL_Delay(100);
}

bool Map::IsPointOnLeftSide(int XPosition, int YPosition, int NodeID)
{
    int dx = XPosition - m_Nodes[NodeID].XPartition;
    int dy = YPosition - m_Nodes[NodeID].YPartition;
    
    return (((dx * m_Nodes[NodeID].ChangeYPartition) - (dy * m_Nodes[NodeID].ChangeXPartition)) <= 0);
}

void Map::SetLumpIndex(int Index)
{
    m_LumpIndex = Index;
}

int Map::GetLumpIndex()
{
    return m_LumpIndex;
}

int Map::GetXMin()
{
    return m_XMin;
}

int Map::GetXMax()
{
    return m_XMax;
}

int Map::GetYMin()
{
    return m_YMin;
}

int Map::GetYMax()
{
    return m_YMax;
}
