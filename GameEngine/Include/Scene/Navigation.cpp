
#include "Navigation.h"
#include "../Component/Tile.h"

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
		Node->Center = Node->Pos + Node->Size * 0.5f;
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

	// ������ ����ϴ� ������ �������� �����Ƿ� ���� ã�� ���� ����ϴ� ������ �����͸�
	// �ʱ�ȭ�Ѵ�.
	size_t	Size = m_vecUseNode.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecUseNode[i]->NodeType = Nav_Node_Type::None;
		m_vecUseNode[i]->Cost = FLT_MAX;
		m_vecUseNode[i]->Dist = FLT_MAX;
		m_vecUseNode[i]->Total = FLT_MAX;
		m_vecUseNode[i]->Parent = nullptr;
	}

	NavNode* StartNode = m_vecNode[StartIndex];
	NavNode* EndNode = m_vecNode[EndIndex];

	if (EndNode->TileType == Tile_Type::Wall)
		return false;

	else if (StartNode == EndNode)
	{
		vecPath.push_back(End);
		return true;
	}

	StartNode->NodeType = Nav_Node_Type::Open;

	m_vecOpen.push_back(StartNode);

	m_vecUseNode.push_back(StartNode);

	while (!m_vecOpen.empty())
	{
		NavNode* Node = m_vecOpen.back();
		m_vecOpen.pop_back();

		Node->NodeType = Nav_Node_Type::Close;

		// 8������ Ÿ���� �˻��Ͽ� �ڳʸ� ������Ͽ� �־��ش�.
		FindNode(Node, EndNode, End, vecPath);

		// ��������� �����Ѵ�. ����� ���� ��尡 ���� ������ ��尡 �ǵ��� ������������
		// �����Ѵ�.
		if (!m_vecOpen.empty())
			std::sort(m_vecOpen.begin(), m_vecOpen.end(), SortNode);
	}



	return false;
}

void CNavigation::FindNode(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	for (int i = 0; i < (int)Node_Dir::End; ++i)
	{
		NavNode* Corner = GetCorner((Node_Dir)i, Node, EndNode, End, vecPath);

		if (!Corner)
			continue;





		// ã���� ��尡 �̹� ������Ͽ� �� ���� ��� ����� ���Ͽ� �� �� ���� ����� ��η� ��ü�Ѵ�.

	}
}

NavNode* CNavigation::GetCorner(Node_Dir Dir, NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	switch (m_NodeShape)
	{
	case Tile_Shape::Rect:
		switch (Dir)
		{
		case Node_Dir::T:
			return GetRectNodeTop(Node, EndNode, End, vecPath, false);
		case Node_Dir::RT:
			return GetRectNodeRightTop(Node, EndNode, End, vecPath);
		case Node_Dir::R:
			return GetRectNodeRight(Node, EndNode, End, vecPath, false);
		case Node_Dir::RB:
			return GetRectNodeRightBottom(Node, EndNode, End, vecPath);
		case Node_Dir::B:
			return GetRectNodeBottom(Node, EndNode, End, vecPath, false);
		case Node_Dir::LB:
			return GetRectNodeLeftBottom(Node, EndNode, End, vecPath);
		case Node_Dir::L:
			return GetRectNodeLeft(Node, EndNode, End, vecPath, false);
		case Node_Dir::LT:
			return GetRectNodeLeftTop(Node, EndNode, End, vecPath);
		}
		break;
	case Tile_Shape::Rhombus:
		switch (Dir)
		{
		case Node_Dir::T:
			return GetRhombusNodeTop(Node, EndNode, End, vecPath);
		case Node_Dir::RT:
			return GetRhombusNodeRightTop(Node, EndNode, End, vecPath);
		case Node_Dir::R:
			return GetRhombusNodeRight(Node, EndNode, End, vecPath);
		case Node_Dir::RB:
			return GetRhombusNodeRightBottom(Node, EndNode, End, vecPath);
		case Node_Dir::B:
			return GetRhombusNodeBottom(Node, EndNode, End, vecPath);
		case Node_Dir::LB:
			return GetRhombusNodeLeftBottom(Node, EndNode, End, vecPath);
		case Node_Dir::L:
			return GetRhombusNodeLeft(Node, EndNode, End, vecPath);
		case Node_Dir::LT:
			return GetRhombusNodeLeftTop(Node, EndNode, End, vecPath);
		}
		break;
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath, bool Digonal)
{
	// ���� �̵��Ҷ��� ��带 ��ĭ�� ���� �̵��� ��Ű�鼭 �ش� ����� �������� �����ְ� ������ ���� �շ��ְų�
	// ������ �����ְ� ���� ���� �շ������� �ش� ���� �ڳʰ� �ȴ�.
	int	IndexY = Node->IndexY;

	while (true)
	{
		++IndexY;

		if (IndexY + 1 >= m_CountY)
			return nullptr;

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRightTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	// ������ ���� �̵��Ҷ��� ��带 ��ĭ�� ������ ���� �̵��� ��Ű�鼭 �ش� ����� ���� �����ְ� ���� ���� �շ��ְų�
	// �Ʒ����� �����ְ� ������ �Ʒ��� �շ������� �ش� ���� �ڳʰ� �ȴ�.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		++IndexY;
		++IndexX;

		if (IndexY + 1 >= m_CountY || IndexX + 1 >= m_CountX)
			return nullptr;

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = IndexX - 1;
		int	CornerY = IndexY;

		if (CornerX >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = IndexY - 1;

		if (CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// ������ �� �밢�� üũ�� ���� �� ��尡 �ڳʰ� �ƴ϶�� ������ ����� ���� ������ üũ�Ͽ�
		// �ڳʰ� �ִ����� �Ǵ��Ѵ�.
		NavNode* FindNode = GetRectNodeTop(CheckNode, EndNode, End, vecPath);

		// ���� �˻��� ��带 ã�Ҵٸ� ������ ��带 �ڳʷ� üũ�Ѵ�.
		if (FindNode)
			return CheckNode;

		FindNode = GetRectNodeRight(CheckNode, EndNode, End, vecPath);

		if (FindNode)
			return CheckNode;
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRight(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath, bool Digonal)
{
	// ���������� �̵��Ҷ��� ���ΰ� 1�� �����ϸ� ���� �����ְ� ������ ���� �� �� �ְų�
	// �Ʒ��� �����ְ� ������ �Ʒ��� �� �� ���� ��� �ڳʰ� �ȴ�.
	int	IndexX = Node->IndexX;

	while (true)
	{
		++IndexX;

		if (IndexX + 1 >= m_CountX)
			return nullptr;

		NavNode* CheckNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRightBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	// ������ �Ʒ��� �̵��Ҷ��� ��带 ��ĭ�� ������ �Ʒ��� �̵��� ��Ű�鼭 �ش� ����� ������ �����ְ� ���� �Ʒ��� �շ��ְų�
	// ������ �����ְ� ������ ���� �շ������� �ش� ���� �ڳʰ� �ȴ�.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		--IndexY;
		++IndexX;

		if (IndexY - 1 < 0 || IndexX + 1 >= m_CountX)
			return nullptr;

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = IndexX - 1;
		int	CornerY = IndexY;

		if (CornerX >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = IndexY + 1;

		if (CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// ������ �Ʒ� �밢�� üũ�� ���� �� ��尡 �ڳʰ� �ƴ϶�� ������ ����� �Ʒ��� ������ üũ�Ͽ�
		// �ڳʰ� �ִ����� �Ǵ��Ѵ�.
		NavNode* FindNode = GetRectNodeBottom(CheckNode, EndNode, End, vecPath);

		// ���� �˻��� ��带 ã�Ҵٸ� ������ ��带 �ڳʷ� üũ�Ѵ�.
		if (FindNode)
			return CheckNode;

		FindNode = GetRectNodeRight(CheckNode, EndNode, End, vecPath);

		if (FindNode)
			return CheckNode;
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath, bool Digonal)
{
	// �Ʒ��� �̵��Ҷ��� ��带 ��ĭ�� �Ʒ��� �̵��� ��Ű�鼭 �ش� ����� �������� �����ְ� ������ �Ʒ��� �շ��ְų�
	// ������ �����ְ� ���� �Ʒ��� �շ������� �ش� ���� �ڳʰ� �ȴ�.
	int	IndexY = Node->IndexY;

	while (true)
	{
		--IndexY;

		if (IndexY - 1 < 0)
			return nullptr;

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeftBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeft(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath, bool Digonal)
{
	// �������� �̵��Ҷ��� ���ΰ� 1�� �����ϸ� ���� �����ְ� ���� ���� �� �� �ְų�
	// �Ʒ��� �����ְ� ���� �Ʒ��� �� �� ���� ��� �ڳʰ� �ȴ�.
	int	IndexX = Node->IndexX;

	while (true)
	{
		--IndexX;

		if (IndexX - 1 < 0)
			return nullptr;

		NavNode* CheckNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
			return CheckNode;

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
			return nullptr;

		else if (CheckNode->TileType == Tile_Type::Wall)
			return nullptr;

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeftTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRightTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRight(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRightBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeftBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeft(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeftTop(NavNode* Node, NavNode* EndNode, const Vector3& End, std::vector<Vector3>& vecPath)
{
	return nullptr;
}

bool CNavigation::SortNode(NavNode* Src, NavNode* Dest)
{
	return Src->Total > Dest->Total;
}
