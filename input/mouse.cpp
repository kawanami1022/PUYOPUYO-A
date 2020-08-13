#include <functional>
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

	_mouseInputTbl = { {InputID::Left,MOUSE_INPUT_LEFT},
					{InputID::Right,MOUSE_INPUT_RIGHT},
					{InputID::Down,MOUSE_INPUT_MIDDLE} };
	return true;
}

ContType mouse::GetType(void)
{
	return ContType::Mouse;
}

bool mouse::Hold(InputID mouseButton)
{
	return false;
}

bool mouse::push(InputID mouseButton)
{
	return false;
}

bool mouse::release(InputID mouseButton)
{
	return false;
}

bool mouse::separate(InputID mouseButton)
{
	return false;
}

Vector2 mouse::getMousePos()
{
	return Vector2();
}

void mouse::DebugDrow(int id)
{
	if(id==0)
	DrawFormatString(0, 0, 0xffffff, "inputMode: mouse");
	if(id==1)
	DrawFormatString(400,0, 0xffffff, "inputMode: mouse");

}
 