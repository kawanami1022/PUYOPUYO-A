#include <DxLib.h>
#include "mouse.h"

void mouse::Update()
{
	GetMousePoint(&pos.x, &pos.y);
	_mouseInputData[MOUSE_INPUT_LEFT] = GetMouseInput()& MOUSE_INPUT_LEFT;
	_mouseInputData[MOUSE_INPUT_RIGHT] = GetMouseInput() & MOUSE_INPUT_RIGHT;
	_mouseInputData[MOUSE_INPUT_MIDDLE] = GetMouseInput()& MOUSE_INPUT_MIDDLE;
	for (auto _id:InputID())
	{
		_data[_id][static_cast<int>(Trg::Old)] = _data[_id][static_cast<int>(Trg::Now)];
		_data[_id][static_cast<int>(Trg::Now)] = _mouseInputData[_mouseInputTbl[_id]];
	}
}

mouse::mouse()
{
}

mouse::~mouse()
{
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
