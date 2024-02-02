#include "Map.h"

Map::Map(SDL_Renderer* renderer, std::string name, Player* player)
	: m_Renderer(renderer), m_Name(name), m_XMin(INT_MAX), m_XMax(INT_MIN), m_YMin(INT_MAX), m_YMax(INT_MIN), m_iAutoMapScaleFactor(15), m_Player(player), m_iLumpIndex(-1)
{
	SDL_RenderGetLogicalSize(m_Renderer, &iRenderXSize, &iRenderYSize);
	--iRenderXSize;
	--iRenderYSize;
}

Map::~Map()
{

}

void Map::AddVertex(Vertex& v)
{
	m_Vertexes.push_back(v);

	if (m_XMin > v.x_pos)
	{
		m_XMin = v.x_pos;
	}
	else if (m_XMax < v.x_pos)
	{
		m_XMax = v.x_pos;
	}
	if (m_YMin > v.y_pos)
	{
		m_YMin = v.y_pos;
	}
	else if (m_YMax < v.y_pos)
	{
		m_YMax = v.y_pos;
	}
}

void Map::AddLinedef(Linedef& l)
{
	m_Linedefs.push_back(l);
}

std::string Map::GetName()
{
	return m_Name;
}

void Map::RenderAutoMap()
{	
	RenderAutoMapWalls();
	RenderAutoMapPlayer();
	RenderAutoMapNodes();
}

void Map::RenderAutoMapWalls()
{	
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for (Linedef& l : m_Linedefs)
	{
		Vertex vStart = m_Vertexes[l.StartVertex];
		Vertex vEnd = m_Vertexes[l.EndVertex];

		SDL_RenderDrawLine(m_Renderer,
			RemapXToScreen(vStart.x_pos),
			RemapYToScreen(vStart.y_pos),
			RemapXToScreen(vEnd.x_pos),
			RemapYToScreen(vEnd.y_pos));
	}
}

void Map::RenderAutoMapPlayer()
{
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	std::pair<int, int> Direction[] = {
		std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(+1, -1),	// Above Row
		std::make_pair(-1, 0), std::make_pair(0, 0), std::make_pair(+1, 0),		// Center Row
		std::make_pair(-1, +1), std::make_pair(0, +1), std::make_pair(+1, +1)	// Bottom Row
	};

	for (int i = 0; i < 9; i++)
	{
		SDL_RenderDrawPoint(m_Renderer,
			RemapXToScreen(m_Player->GetXPosition()) + Direction[i].first,
			RemapYToScreen(m_Player->GetYPosition()) + Direction[i].second);
	}
}

void Map::RenderAutoMapNodes()
{
	Node node = m_Nodes[m_Nodes.size()-1];

	SDL_Rect RightRect = {
		RemapXToScreen(node.RightBoxLeft),
		RemapYToScreen(node.RightBoxTop),
		RemapXToScreen(node.RightBoxRight) - RemapXToScreen(node.RightBoxLeft) + 1,
		RemapYToScreen(node.RightBoxBottom) - RemapYToScreen(node.RightBoxTop) + 1
	};

	SDL_Rect LeftRect = {
		RemapXToScreen(node.LeftBoxLeft),
		RemapYToScreen(node.LeftBoxTop),
		RemapXToScreen(node.LeftBoxRight) - RemapXToScreen(node.LeftBoxLeft) + 1,
		RemapYToScreen(node.LeftBoxBottom) - RemapYToScreen(node.LeftBoxTop) + 1
	};

	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(m_Renderer, &RightRect);
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(m_Renderer, &LeftRect);

	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(m_Renderer,
		RemapXToScreen(node.XPartition),
		RemapYToScreen(node.YPartition),
		RemapXToScreen(node.XPartition + node.ChangeXPartition),
		RemapYToScreen(node.YPartition + node.ChangeYPartition));
}

void Map::RenderBSPNode(int NodeID)
{
	if (NodeID & SUBSECTORIDENTIFIER)
	{
		RenderSubsector(NodeID & (~SUBSECTORIDENTIFIER));
		return;
	}
}

void Map::RenderSubsector(int SubsectorID)
{

}

void Map::AddThing(Thing& thing)
{
	
	if (thing.Type == m_Player->GetID())
	{
		m_Player->SetXPosition(thing.XPos);
		m_Player->SetYPosition(thing.YPos);
		m_Player->SetAngle(thing.Angle);
	}

	m_Things.push_back(thing);
}

void Map::AddNode(Node& node)
{
	m_Nodes.push_back(node);
}

void Map::SetLumpIndex(int iIndex)
{
	m_iLumpIndex = iIndex;
}

int Map::GetLumpIndex()
{
	return m_iLumpIndex;
}

int Map::RemapXToScreen(int XMapPosition)
{
	return (XMapPosition + (-m_XMin)) / m_iAutoMapScaleFactor;
}

int Map::RemapYToScreen(int YMapPosition)
{
	return iRenderYSize - (YMapPosition + (-m_YMin)) / m_iAutoMapScaleFactor;
}

bool Map::IsPointOnLeftSide(int XPosition, int YPosition, int NodeID)
{
	int dx = XPosition - m_Nodes[NodeID].XPartition;
	int dy = YPosition - m_Nodes[NodeID].YPartition;

	return (((dx * m_Nodes[NodeID].ChangeYPartition) - (dy * m_Nodes[NodeID].ChangeXPartition)) <= 0);
}