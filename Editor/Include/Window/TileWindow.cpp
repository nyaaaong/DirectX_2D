
#include "TileWindow.h"
#include "IMGUISameLine.h"
#include "IMGUIImage.h"

CTileWindow::CTileWindow()
{
}

CTileWindow::~CTileWindow()
{
}

bool CTileWindow::Init()
{
	if (!CIMGUIWindow::Init())
		return false;

	for (int i = 0; i < 10; ++i)
	{
		CIMGUIImage* TestImage = AddWidget<CIMGUIImage>("TestImg", 54.f, 54.f);
		TestImage->MouseCheck(true);

		m_vecTile.push_back(TestImage);

		CIMGUISameLine* Line = AddWidget<CIMGUISameLine>("Line");
	}

	return true;
}

void CTileWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTile[i])
		{
			if (m_vecTile[i]->IsClicked())
				int a = 0;

			else if (m_vecTile[i]->IsHovered())
				int a = 0;
		}
	}
}
