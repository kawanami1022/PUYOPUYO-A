#include <DxLib.h>
#include "keyInput.h"

ContType KeyInput::GetType(void)
{
	return ContType::Key;
}

bool KeyInput::Setup(int no)
{
	if (no == 0)
	{
		_InputTbl = {
			{InputID::Up,KEY_INPUT_UP},
			{InputID::Down,KEY_INPUT_DOWN},
			{InputID::Left,KEY_INPUT_LEFT},
			{InputID::Right,KEY_INPUT_RIGHT},
			{InputID::Btn1,KEY_INPUT_NUMPAD1},
			{InputID::Btn2,KEY_INPUT_NUMPAD2},
		};
	}
	else
	{
		_InputTbl = {
			{InputID::Up,KEY_INPUT_W},
			{InputID::Down,KEY_INPUT_S},
			{InputID::Left,KEY_INPUT_A},
			{InputID::Right,KEY_INPUT_D},
			{InputID::Btn1,KEY_INPUT_COMMA},
			{InputID::Btn2,KEY_INPUT_E},
		};
	}
	return true;
}

void KeyInput::Update(void)
{
	GetHitKeyStateAll(_keyData.data());
	for (auto id:InputID())
	{
		_data[id][static_cast<int>(Trg::Old)] = _data[id][static_cast<int>(Trg::Now)];
		_data[id][static_cast<int>(Trg::Now)] = _keyData[_InputTbl[id]];
	}
}

bool KeyInput::push(InputID inputID)
{
	return (!_data[inputID][static_cast<int>(Trg::Old)] && _data[inputID][static_cast<int>(Trg::Now)]);
}

bool KeyInput::Hold(InputID)
{
	return false;
}

bool KeyInput::release(InputID)
{
	return false;
}

bool KeyInput::separate(InputID)
{
	return false;
}

