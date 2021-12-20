
#include "Excel.h"
#include "../PathManager.h"

CExcel::CExcel()	:
	book(nullptr)
{
}

CExcel::~CExcel()
{
	if (book)
		book->release();
}

bool CExcel::Init()
{
	return true;
}

bool CExcel::Load(const wchar_t* FileName, const wchar_t* MiddlePath)
{
	const PathInfo* ExcelPath = CPathManager::GetInst()->FindPath(EXCEL_PATH);

	if (!ExcelPath)
		return false;

	wchar_t	FullPath[MAX_PATH] = {};
	wchar_t Middle[MAX_PATH] = {};

	lstrcpy(Middle, MiddlePath);
	lstrcat(Middle, L"\\");

	lstrcpy(FullPath, ExcelPath->Path);
	lstrcat(FullPath, Middle);
	lstrcat(FullPath, FileName);

	int Idx = lstrlen(FileName) - 1; // 널문자 바로 전인 확장자의 맨 오른쪽 단어를 구한다

	if (FileName[Idx] == L'x' ||
		FileName[Idx] == L'X')
		book = xlCreateXMLBook();	// xlsx

	else
		book = xlCreateBook();		// xls

	if (!book->load(FullPath))
		return false;

	return true;
}
