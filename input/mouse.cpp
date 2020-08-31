#include <functional>
#include <DxLib.h>
#include "mouse.h"


void mouse::Update()
{
	GetMousePoint(&pos.x, &pos.y);
	mouseWheel_ = GetMouseWheelRotVol();
	int mouseInput = GetMouseInput();
	for (auto id_:InputID())
	{
		_data[id_][static_cast<int>(Trg::Old)] = _data[id_][static_cast<int>(Trg::Now)];
		_data[id_][static_cast<int>(Trg::Now)] = _mouseInputTbl[id_] & mouseInput;
	}
	for (auto id_ : InputID())
	{
		if (id_ >= InputID::TURN_L)
		{
			_data[id_][static_cast<int>(Trg::Old)] = _data[id_][static_cast<int>(Trg::Now)];
			_data[id_][static_cast<int>(Trg::Now)] = GetMouseWheelFlag(id_);
		}
	}
	frame_++;
}
bool mouse::Setup(int no)
{
	frame_ = 0;
	_mouseInputTbl = { {InputID::Left,MOUSE_INPUT_LEFT},
					{InputID::Right,MOUSE_INPUT_RIGHT},
					{InputID::Down,MOUSE_INPUT_MIDDLE},
					{InputID::TURN_L,NULL}, 
					{InputID::TURN_R,NULL}, };
	joyPadNum_ = GetJoypadNum();
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

void mouse::changeInputTbl(int inputButton, InputID inputID)
{
	_mouseInputTbl[inputID] = inputButton;
}

void mouse::PadForceFeedback(int Power, int Time)
{
}

Vector2 mouse::getMousePos()
{
	return Vector2();
}

InputID mouse::GetInputID()
{
	int idx = mouseWheel_;
	if (idx >= 1) return InputID::TURN_L;
	if (idx <= -1) return InputID::TURN_R;
	return InputID();
}

int mouse::GetMouseWheelFlag(InputID inputID)
{
	if (inputID == GetInputID())
		return 1;
	return 0;
}

void mouse::DebugDrow(int id, Texture& texture)
{
	if(id==0)
		DrawGraph(0, 0, texture.GetHandle(), true);
	if(id==1)
		DrawGraph(400, 0, texture.GetHandle(), true);

}
 