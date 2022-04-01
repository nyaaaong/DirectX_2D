
#include "Excel_Monster.h"

CExcel_Monster::CExcel_Monster()	:
	m_MonsterSize(0)
{
	m_vecMonsterInfo.reserve((size_t)Object_Type::Max);
}

CExcel_Monster::~CExcel_Monster()
{
}

bool CExcel_Monster::Init()
{
	if (!CExcel::Load(L"Monster.xlsx", L"Character"))
		return false;

	libxl::Sheet* sheet = book->getSheet(0);

	if (!sheet)
		return false;

	float	Info[3] = {};
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
					Info[NumberIndex] = static_cast<float>(sheet->readNum(row, col));
					++NumberIndex;

					if (NumberIndex == 3)
					{
						NumberIndex = 0;

						CharacterInfo	NewInfo;
						NewInfo.HP = Info[0];
						NewInfo.MoveSpeed = Info[1];
						NewInfo.Damage = Info[2];

						m_vecMonsterInfo.push_back(NewInfo);
						++m_MonsterSize;
					}
					break;
				}
				case libxl::CELLTYPE_STRING:
				{
					//const wchar_t* s = sheet->readStr(row, col);
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

	return true;
}