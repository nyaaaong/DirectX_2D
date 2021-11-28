#include "Input.h"
#include "Device.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_hInst(0),
	m_hWnd(0),
	m_Input(nullptr),
	m_Keyboard(nullptr),
	m_Mouse(nullptr),
	m_KeyArray{},
	m_MouseState{},
	m_InputType((Input_Type)0),
	m_Ctrl(false),
	m_Alt(false),
	m_Shift(false)
{
	m_vecKeyState.resize(256);

	for (int i = 0; i < 256; ++i)
	{
		m_vecKeyState[i].Key = (unsigned char)i;
	}
}

CInput::~CInput()
{
	auto	iter = m_mapKeyInfo.begin();
	auto	iterEnd = m_mapKeyInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	SAFE_RELEASE(m_Keyboard);
	SAFE_RELEASE(m_Mouse);
	SAFE_RELEASE(m_Input);
}

bool CInput::CreateKey(const std::string& Name, unsigned char Key)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (Info)
		return false;

	Info = new KeyInfo;

	Info->Name = Name;

	unsigned char	ConvertkeyValue = ConvertKey(Key);

	Info->State.Key = ConvertkeyValue;

	m_mapKeyInfo.insert(std::make_pair(Name, Info));

	bool	Add = false;

	size_t	Size = m_vecAddKey.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecAddKey[i] == ConvertkeyValue)
		{
			Add = true;
			break;
		}
	}

	if (!Add)
		m_vecAddKey.push_back(ConvertkeyValue);

	return true;
}

bool CInput::SetCtrlKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Ctrl = State;

	return true;
}

bool CInput::SetAltKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Alt = State;

	return true;
}

bool CInput::SetShiftKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Shift = State;

	return true;
}

KeyInfo* CInput::FindKeyInfo(const std::string& Name)
{
	auto	iter = m_mapKeyInfo.find(Name);

	if (iter == m_mapKeyInfo.end())
		return nullptr;

	return iter->second;
}

bool CInput::InitWindow()
{
	return true;
}

bool CInput::InitDirectInput()
{
	if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_Keyboard, nullptr)))
		return false;

	if (FAILED(m_Keyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;

	if (FAILED(m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr)))
		return false;

	if (FAILED(m_Mouse->SetDataFormat(&c_dfDIMouse)))
		return false;

	return true;
}

bool CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hInst = hInst;
	m_hWnd = hWnd;

	m_InputType = Input_Type::Direct;



	HRESULT	result = DirectInput8Create(m_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_Input, nullptr);

	if (FAILED(result))
		m_InputType = Input_Type::Window;

	switch (m_InputType)
	{
	case Input_Type::Direct:
		if (!InitDirectInput())
			return false;
		break;
	case Input_Type::Window:
		if (!InitWindow())
			return false;
		break;
	}


	return true;
}

void CInput::Update(float DeltaTime)
{
	if (m_InputType == Input_Type::Direct)
	{
		ReadDirectInputKeyboard();
		ReadDirectInputMouse();
	}

	// 키 상태를 업데이트 해준다.
	UpdateKeyState();

	// 키보드 키 입력처리를 한다.
	UpdateKeyInfo(DeltaTime);

	// 마우스 입력처리를 한다.
	UpdateMouse(DeltaTime);
}

void CInput::ReadDirectInputKeyboard()
{
	HRESULT	result = m_Keyboard->GetDeviceState(256, m_KeyArray);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_Keyboard->Acquire();
	}
}

void CInput::ReadDirectInputMouse()
{
	HRESULT	result = m_Mouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_Mouse->Acquire();
	}
}

void CInput::UpdateMouse(float DeltaTime)
{
	POINT	MouseWindowPos;

	GetCursorPos(&MouseWindowPos);
	ScreenToClient(m_hWnd, &MouseWindowPos);

	Vector2	Ratio = CDevice::GetInst()->GetViewportAspectRatio();

	Vector2	MousePos = Vector2(MouseWindowPos.x * Ratio.x, MouseWindowPos.y * Ratio.y);

	m_MouseMove = MousePos - m_MousePos;

	m_MousePos = MousePos;
}

void CInput::UpdateKeyState()
{
	switch (m_InputType)
	{
	case Input_Type::Direct:
		if (m_KeyArray[DIK_LCONTROL] & 0x80)
			m_Ctrl = true;

		else
			m_Ctrl = false;

		if (m_KeyArray[DIK_LALT] & 0x80)
			m_Alt = true;

		else
			m_Alt = false;

		if (m_KeyArray[DIK_LSHIFT] & 0x80)
			m_Shift = true;

		else
			m_Shift = false;
		break;
	case Input_Type::Window:
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
			m_Ctrl = true;

		else
			m_Ctrl = false;

		if (GetAsyncKeyState(VK_MENU) & 0x8000)
			m_Alt = true;

		else
			m_Alt = false;

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			m_Shift = true;

		else
			m_Shift = false;
		break;
	}

	// 등록된 키를 반복하며 해당 키가 눌러졌는지를 판단한다.
	size_t	Size = m_vecAddKey.size();

	for (size_t i = 0; i < Size; ++i)
	{
		unsigned char Key = m_vecAddKey[i];

		bool	KeyPush = false;

		switch (m_InputType)
		{
		case Input_Type::Direct:
			switch (Key)
			{
			case DIK_MOUSELBUTTON:
				if (m_MouseState.rgbButtons[0] & 0x80)
					KeyPush = true;
				break;
			case DIK_MOUSERBUTTON:
				if (m_MouseState.rgbButtons[1] & 0x80)
					KeyPush = true;
				break;
			case DIK_MOUSEWHEEL:
				break;
			default:	// 키보드 키를 알아볼 경우
				if (m_KeyArray[Key] & 0x80)
					KeyPush = true;
				break;
			}
			break;
		case Input_Type::Window:
			if (GetAsyncKeyState(Key) & 0x8000)
			{
				KeyPush = true;
			}
			break;
		}

		if (KeyPush)
		{
			if (!m_vecKeyState[Key].State[KeyState_Down] &&
				!m_vecKeyState[Key].State[KeyState_Push])
			{
				m_vecKeyState[Key].State[KeyState_Down] = true;
				m_vecKeyState[Key].State[KeyState_Push] = true;
			}

			else
				m_vecKeyState[Key].State[KeyState_Down] = false;
		}

		else if (m_vecKeyState[Key].State[KeyState_Push])
		{
			m_vecKeyState[Key].State[KeyState_Up] = true;
			m_vecKeyState[Key].State[KeyState_Down] = false;
			m_vecKeyState[Key].State[KeyState_Push] = false;
		}

		else if (m_vecKeyState[Key].State[KeyState_Up])
		{
			m_vecKeyState[Key].State[KeyState_Up] = false;
		}
	}
}

void CInput::UpdateKeyInfo(float DeltaTime)
{
	auto	iter = m_mapKeyInfo.begin();
	auto	iterEnd = m_mapKeyInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		unsigned char Key = iter->second->State.Key;

		if (m_vecKeyState[Key].State[KeyState_Down] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			if (iter->second->Callback[KeyState_Down])
				iter->second->Callback[KeyState_Down](DeltaTime);
		}


		if (m_vecKeyState[Key].State[KeyState_Push] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			if (iter->second->Callback[KeyState_Push])
				iter->second->Callback[KeyState_Push](DeltaTime);
		}


		if (m_vecKeyState[Key].State[KeyState_Up] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			if (iter->second->Callback[KeyState_Up])
				iter->second->Callback[KeyState_Up](DeltaTime);
		}
	}
}

unsigned char CInput::ConvertKey(unsigned char Key)
{
	if (m_InputType == Input_Type::Direct)
	{
		switch (Key)
		{
		case VK_ESCAPE:
			return DIK_ESCAPE;
		case '1':
			return DIK_1;
		case '2':
			return DIK_2;
		case '3':
			return DIK_3;
		case '4':
			return DIK_4;
		case '5':
			return DIK_5;
		case '6':
			return DIK_6;
		case '7':
			return DIK_7;
		case '8':
			return DIK_8;
		case '9':
			return DIK_9;
		case '0':
			return DIK_0;
		case VK_OEM_MINUS:
			return DIK_MINUS;
		case '=':
			return DIK_EQUALS;
		case VK_BACK:
			return DIK_BACK;
		case VK_TAB:
			return DIK_TAB;
		case 'Q':
			return DIK_Q;
		case 'W':
			return DIK_W;
		case 'E':
			return DIK_E;
		case 'R':
			return DIK_R;
		case 'T':
			return DIK_T;
		case 'Y':
			return DIK_Y;
		case 'U':
			return DIK_U;
		case 'I':
			return DIK_I;
		case 'O':
			return DIK_O;
		case 'P':
			return DIK_P;
		case '[':
			return DIK_LBRACKET;
		case ']':
			return DIK_RBRACKET;
		case VK_RETURN:
			return DIK_RETURN;
		case VK_CONTROL:
			return DIK_LCONTROL;
		case 'A':
			return DIK_A;
		case 'S':
			return DIK_S;
		case 'D':
			return DIK_D;
		case 'F':
			return DIK_F;
		case VK_SPACE:
			return DIK_SPACE;
		case VK_LBUTTON:
			return DIK_MOUSELBUTTON;
		case VK_RBUTTON:
			return DIK_MOUSERBUTTON;
		case 'G':
			return DIK_G;
		case 'H':
			return DIK_H;
		case 'J':
			return DIK_J;
		case 'K':
			return DIK_K;
			/*case DIK_L:
				return 'L';
			case DIK_SEMICOLON:
				return ';';
			case DIK_APOSTROPHE:
				return '\'';
			case DIK_GRAVE:
				return '`';
			case DIK_LSHIFT:
				return VK_SHIFT;
			case DIK_BACKSLASH:
				return '\\';
			case DIK_Z:
				return 'Z';
			case DIK_X:
				return 'X';
			case DIK_C:
				return 'C';
			case DIK_V:
				return 'V';
			case DIK_B:
				return 'B';
			case DIK_N:
				return 'N';
			case DIK_M:
				return 'M';
			case DIK_COMMA:
				return ',';
			case DIK_PERIOD:
				return '.';
			case DIK_SLASH:
				return '/';
			case DIK_RSHIFT:
				return VK_RSHIFT;
			case DIK_MULTIPLY:
				return VK_MULTIPLY;
			case DIK_LMENU:
				return VK_LMENU;
			case DIK_CAPITAL:
				return VK_CAPITAL;
			case DIK_F1:
				return VK_F1;
			case DIK_F2:
				return VK_F2;
			case DIK_F3:
				return VK_F3;
			case DIK_F4:
				return VK_F4;
			case DIK_F5:
				return VK_F5;
			case DIK_F6:
				return VK_F6;
			case DIK_F7:
				return VK_F7;
			case DIK_F8:
				return VK_F8;
			case DIK_F9:
				return VK_F9;
			case DIK_F10:
				return VK_F10;
			case DIK_NUMLOCK:
				break;
			case DIK_SCROLL:
				break;
			case DIK_NUMPAD7:
				break;
			case DIK_NUMPAD8:
				break;
			case DIK_NUMPAD9:
				break;
			case DIK_SUBTRACT:
				break;
			case DIK_NUMPAD4:
				break;
			case DIK_NUMPAD5:
				break;
			case DIK_NUMPAD6:
				break;
			case DIK_ADD:
				break;
			case DIK_NUMPAD1:
				break;
			case DIK_NUMPAD2:
				break;
			case DIK_NUMPAD3:
				break;
			case DIK_NUMPAD0:
				break;
			case DIK_DECIMAL:
				break;
			case DIK_OEM_102:
				break;
			case DIK_F11:
				return VK_F11;
			case DIK_F12:
				return VK_F12;
			case DIK_F13:
				break;
			case DIK_F14:
				break;
			case DIK_F15:
				break;
			case DIK_NEXTTRACK:
				break;
			case DIK_NUMPADENTER:
				break;
			case DIK_RCONTROL:
				return VK_RCONTROL;
			case DIK_MUTE:
				break;
			case DIK_CALCULATOR:
				break;
			case DIK_PLAYPAUSE:
				break;
			case DIK_MEDIASTOP:
				break;
			case DIK_VOLUMEDOWN:
				break;
			case DIK_VOLUMEUP:
				break;
			case DIK_WEBHOME:
				break;
			case DIK_DIVIDE:
				break;
			case DIK_SYSRQ:
				break;
			case DIK_RMENU:
				return VK_RMENU;
			case DIK_PAUSE:
				break;
			case DIK_HOME:
				return VK_HOME;
			case DIK_UP:
				return VK_UP;
			case DIK_PRIOR:
				return VK_PRIOR;
			case DIK_LEFT:
				return VK_LEFT;
			case DIK_RIGHT:
				return VK_RIGHT;
			case DIK_END:
				return VK_END;
			case DIK_DOWN:
				return VK_DOWN;
			case DIK_NEXT:
				return VK_NEXT;
			case DIK_INSERT:
				return VK_INSERT;
			case DIK_DELETE:
				return VK_DELETE;
			case DIK_LWIN:
				break;
			case DIK_RWIN:
				break;
			case DIK_APPS:
				break;
			case DIK_POWER:
				break;
			case DIK_SLEEP:
				break;
			case DIK_WAKE:
				break;
			case DIK_WEBSEARCH:
				break;
			case DIK_WEBFAVORITES:
				break;
			case DIK_WEBREFRESH:
				break;
			case DIK_WEBSTOP:
				break;
			case DIK_WEBFORWARD:
				break;
			case DIK_WEBBACK:
				break;
			case DIK_MYCOMPUTER:
				break;
			case DIK_MAIL:
				break;
			case DIK_MEDIASELECT:
				break;
			case DIK_MOUSELBUTTON:
				return VK_LBUTTON;
			case DIK_MOUSERBUTTON:
				return VK_RBUTTON;
			case DIK_MOUSEWHEEL:
				return DIK_MOUSEWHEEL;*/
		}

		return 0xff;
	}

	return Key;
}

void CInput::ClearCallback()
{
	auto	iter = m_mapKeyInfo.begin();
	auto	iterEnd = m_mapKeyInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < KeyState_Max; ++i)
		{
			iter->second->Callback[i] = nullptr;
		}
	}
}
