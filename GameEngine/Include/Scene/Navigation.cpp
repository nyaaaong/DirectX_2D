
#include "Navigation.h"

CNavigation::CNavigation()
{
}

CNavigation::~CNavigation()
{
}

void CNavigation::CreateNavigationNode(CTileMapComponent* TileMap)
{
	m_TileMap = TileMap;

	m_NodeShape = TileMap->GetTileShape();
	m_CountX = TileMap->GetTileCountX();
	m_CountY = TileMap->GetTileCountY();
	m_TileSize = TileMap->GetTileSize();

	int	Count = m_CountX * m_CountY;

	for (int i = 0; i < Count; ++i)
	{
		NavNode* Node = DBG_NEW NavNode;

		Node->TileType = TileMap->GetTile(i)->GetTileType();
		Node->Pos = TileMap->GetTile(i)->GetPos();
		Node->Size = m_TileSize;
		Node->IndexX = TileMap->GetTile(i)->GetIndexX();
		Node->IndexY = TileMap->GetTile(i)->GetIndexY();
		Node->Index = TileMap->GetTile(i)->GetIndex();

		m_vecNode.push_back(Node);
	}
}

bool CNavigation::FindPath(const Vector3& Start, const Vector3& End, std::vector<Vector3>& vecPath)
{
	vecPath.clear();

	int	StartIndex = m_TileMap->GetTileIndex(Start);
	
	if (StartIndex == -1)
		return false;

	int	EndIndex = m_TileMap->GetTileIndex(End);

	if (EndIndex == -1)
		return false;



	return false;
}
