
#include "Excel_Player.h"

CExcel_Player::CExcel_Player()
{
}

CExcel_Player::~CExcel_Player()
{
}

bool CExcel_Player::Init()
{
	if (!CExcel::Load(L"Player.xlsx", L"Character"))
		return false;

	libxl::Sheet* sheet = book->getSheet(0);

	if (!sheet)
		return false;

	for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
	{
		for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
		{
			libxl::CellType	cellType = sheet->cellType(row, col);

			if (!sheet->isFormula(row, col)) // - 수식이 없는 경우
			{
				switch (cellType)
				{
				case libxl::CELLTYPE_EMPTY:
					break;
				case libxl::CELLTYPE_NUMBER:
				{
					double d = sheet->readNum(row, col);
					break;
				}
				case libxl::CELLTYPE_STRING:
				{
					const wchar_t* s = sheet->readStr(row, col);
					break; 
				}
				case libxl::CELLTYPE_BOOLEAN:
				{
					bool b = sheet->readBool(row, col);
					break;
				}
				case libxl::CELLTYPE_BLANK:
					break;
				case libxl::CELLTYPE_ERROR:
					break;
				case libxl::CELLTYPE_STRICTDATE:
					break;
				}
			}

		}
	}

	return true;
}
