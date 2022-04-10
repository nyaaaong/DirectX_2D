
#include "Excel_BulletKing.h"

CExcel_BulletKing::CExcel_BulletKing()
{
}

CExcel_BulletKing::~CExcel_BulletKing()
{
}

bool CExcel_BulletKing::Init()
{
	if (!CExcel::Load(L"Boss.xlsx", L"Character"))
		return false;

	libxl::Sheet* sheet = book->getSheet(0);

	if (!sheet)
		return false;

	float	Number[3] = {};
	int		NumberIndex = 0;

	for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
	{
		// 무료버전은 맨 처음 string이 존재하기 때문에 한줄 건너띄워서 검사하게 해준다.
		for (int col = sheet->firstCol() + 1; col < sheet->lastCol(); ++col)
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
					Number[NumberIndex] = static_cast<float>(sheet->readNum(row, col));
					++NumberIndex;
					break;
				}
				case libxl::CELLTYPE_STRING:
				{
					//sheet->readStr(row, col);
					break;
				}
				case libxl::CELLTYPE_BOOLEAN:
				{
					//bool b = sheet->readBool(row, col);
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

	m_BulletKingInfo.HP = Number[0];
	m_BulletKingInfo.MoveSpeed = Number[1];
	m_BulletKingInfo.Damage = Number[2];

	return true;
}
