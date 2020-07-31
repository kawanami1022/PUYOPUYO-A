#include <DxLib.h>
#include "mouse.h"

void mouse::Update()
{
	GetMousePoint(&pos.x, &pos.y);

	int mouseInput = GetMouseInput();
	for (auto id_:InputID())
	{
		_data[id_][static_cast<int>(Trg::Old)] = _data[id_][static_cast<int>(Trg::Now)];
		_data[id_][static_cast<int>(Trg::Now)] = _mouseInputTbl[id_] & mouseInput;
	}
}
bool mouse::Setup(int no)
{
	_mouseInputTbl = { {InputID::Down,MOUSE_INPUT_LEFT},
				{InputID::Right,MOUSE_INPUT_RIGHT},
				{InputID::Left,MOUSE_INPUT_MIDDLE} };
	return true;
}

ContType mouse::GetType(void)
{
	return ContType::Mouse;
}

bool mouse::Hold(int mouseButton)
{
	return false;
}

bool mouse::Push(int mouseButton)
{
	return false;
}

bool mouse::Release(int mouseButton)
{
	return false;
}

bool mouse::separate(int mouseButton)
{
	return false;
}

Vector2 mouse::getMousePos()
{
	return Vector2();
}
