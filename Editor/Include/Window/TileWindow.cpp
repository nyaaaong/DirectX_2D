
#include "TileWindow.h"

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

	return true;
}

void CTileWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}
