#include "Map.h"


Map::Map(std::string name, Player* player, ViewRenderer* renderer, Things* thing)
: m_Name(name), m_Player(player), m_ViewRenderer(renderer), m_Things(thing), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MIN), m_AutoMapScaleFactor(15), m_LumpIndex(-1)
{
    m_pSectors = new std::vector<WADSector>();
    m_pSidedefs = new std::vector<WADSidedef>();
    m_pSegs = new std::vector<WADSeg>();
    m_pLinedefs = new std::vector<WADLinedef>();
}

Map::~Map()
{
    
}

std::string Map::GetName()
{
    return m_Name;
}

void Map::Init()
{
    BuildSectors();
    BuildSidedefs();
    BuildLinedefs();
    BuildSegs();
}

void Map::BuildSectors()
{
    WADSector wadsector;
    Sector sector;
    
    for (int i = 0; i < m_pSectors->size(); i++)
    {
        wadsector = m_pSectors->at(i);
        sector.FloorHeight = wadsector.FloorHeight;
        sector.CeilingHeight = wadsector.CeilingHeight;
        strncpy(sector.FloorTexture, wadsector.FloorTexture, 8);
        sector.FloorTexture[8] = '\n';
        strncpy(sector.CeilingTexture, wadsector.CeilingTexture, 8);
        sector.CeilingTexture[8] = '\n';
        sector.LightLevel = wadsector.LightLevel;
        sector.Type = wadsector.Type;
        sector.Tag = wadsector.Tag;
        m_Sectors.push_back(sector);
    }
    
    delete m_pSectors;
    m_pSectors = nullptr;
}

void Map::BuildSegs()
{
    WADSeg wadseg;
    Seg seg;
    
    for (int i = 0; i < m_pSegs->size(); i++)
    {
        wadseg = m_pSegs->at(i);

        seg.StartVertex = &m_Vertexes[wadseg.StartVertexID];
        seg.EndVertex = &m_Vertexes[wadseg.EndVertexID];
        
        seg.Angle = ((float)(wadseg.Angle << 16) * 8.38190317e-8);
        seg.Linedef = &m_Linedefs[wadseg.LinedefID];
        seg.Direction = wadseg.Direction;
        seg.Offset = wadseg.Offset;
        
        Sidedef* RightSidedef;
        Sidedef* LeftSidedef;
        
        RightSidedef = seg.Linedef->RightSidedef;
        LeftSidedef = seg.Linedef->LeftSidedef;
        
        if (RightSidedef)
        {
            seg.RightSector = RightSidedef->Sector;
        }
        else
        {
            seg.RightSector = nullptr;
        }
        
        if (LeftSidedef)
        {
            seg.LeftSector = LeftSidedef->Sector;
        }
        else
        {
            seg.LeftSector = nullptr;
        }
        
        m_Segs.push_back(seg);
    }
    
    delete m_pSegs;
    m_pSegs = nullptr;
}

void Map::BuildLinedefs()
{
    WADLinedef wadlinedef;
    Linedef linedef;
    
    for (int i = 0; i < m_pLinedefs->size(); i++)
    {
        wadlinedef = m_pLinedefs->at(i);
        
        linedef.StartVertex = &m_Vertexes[wadlinedef.StartVertex];
        linedef.EndVertex = &m_Vertexes[wadlinedef.EndVertex];
        linedef.Flags = wadlinedef.Flags;
        linedef.LineType = wadlinedef.LineType;
        linedef.SectorTag = wadlinedef.SectorTag;
        
        if (wadlinedef.RightSidedef = 0xFFFF)
        {
            linedef.RightSidedef = nullptr;
        }
        else
        {
            linedef.RightSidedef = &m_Sidedefs[wadlinedef.RightSidedef];
        }
        
        if (wadlinedef.LeftSidedef = 0xFFFF)
        {
            linedef.LeftSidedef = nullptr;
        }
        else
        {
            linedef.LeftSidedef = &m_Sidedefs[wadlinedef.LeftSidedef];
        }
        
        m_Linedefs.push_back(linedef);
    }
    
    delete m_pLinedefs;
    m_pLinedefs = nullptr;
}

void Map::BuildSidedefs()
{
    WADSidedef wadsidedef;
    Sidedef sidedef;
    
    for (int i = 0; i < m_Sidedefs.size(); i++)
    {
        wadsidedef = m_pSidedefs->at(i);
        
        sidedef.XOffset = wadsidedef.XOffset;
        sidedef.YOffset = wadsidedef.YOffset;
        strncpy(sidedef.UpperTexture, wadsidedef.UpperTexture, 8);
        sidedef.UpperTexture[9] = '\n';
        strncpy(sidedef.LowerTexture, wadsidedef.LowerTexture, 8);
        sidedef.LowerTexture[9] = '\n';
        strncpy(sidedef.MiddleTexture, wadsidedef.MiddleTexture, 8);
        sidedef.MiddleTexture[9] = '\n';
        sidedef.Sector = &m_Sectors[wadsidedef.SectorID];
        m_Sidedefs.push_back(sidedef);
    }
    
    delete m_pSidedefs;
    m_pSidedefs = nullptr;
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

void Map::AddLinedef(WADLinedef &l)
{
    m_pLinedefs->push_back(l);
}

void Map::AddNode(Node& n)
{
    m_Nodes.push_back(n);
}

void Map::AddSubsector(Subsector &ss)
{
    m_Subsectors.push_back(ss);
}

void Map::AddSeg(WADSeg& s)
{
    m_pSegs->push_back(s);
}

void Map::AddSidedef(WADSidedef &side)
{
    m_pSidedefs->push_back(side);
}

void Map::AddSector(WADSector &sec)
{
    m_pSectors->push_back(sec);
}

void Map::RenderAutoMap()
{
    m_ViewRenderer->SetDrawColor(255, 255, 255);
    
    for (Linedef &l : m_Linedefs)
    {
        Vertex vStart = *(l.StartVertex);
        Vertex vEnd = *(l.EndVertex);
        
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
        Seg& seg = m_Segs[subsector.FirstSegID + i];
        Angle V1Angle, V2Angle;
        
        if (m_Player->ClipVertexesInFOV(*(seg.StartVertex), *(seg.EndVertex), V1Angle, V2Angle))
        {
            m_ViewRenderer->AddWallInFOV(seg, V1Angle, V2Angle);
        }
    }
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

Things* Map::GetThing()
{
    return m_Things;
}
