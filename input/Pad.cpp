#include "Pad.h"

ContType Pad::GetType(void)
{
	return ContType::Pad;
}

void Pad::Update()
{
	if (frame % 180 == 0)joyPadNum_ = ReSetupJoypad();
	int joyPadNum = GetJoypadNum();		// ジョイパッドが接続されてる状態を取得する
	GetJoypadXInputState(DX_INPUT_PAD1, &_xInputData.data()[0]);
	for (auto _id : InputID())
	{
		_data[_id][static_cast<int>(Trg::Old)] = _data[_id][static_cast<int>(Trg::Now)];
		_data[_id][static_cast<int>(Trg::Now)] = _xInputData.data()->Buttons[_xInputTbl[_id]];
	}
	frame++;
}

bool Pad::push(InputID button)
{
	return (_data[button][static_cast<int>(Trg::Now)]==1) && (_data[button][static_cast<int>(Trg::Old)]==0);
}

bool Pad::release(InputID button)
{
	return false;
}

bool Pad::Hold(InputID button)
{
	return false;
}

bool Pad::separate(InputID button)
{
	return false;
}

bool Pad::Setup(int no)
{
	frame = 0;
	_xInputTbl = { {InputID::Up,XINPUT_BUTTON_DPAD_UP},
				{InputID::Down, XINPUT_BUTTON_DPAD_DOWN},
				{InputID::Left,XINPUT_BUTTON_DPAD_LEFT},
				{InputID::Right,XINPUT_BUTTON_DPAD_RIGHT},
				{InputID::TURN_L,XINPUT_BUTTON_A},
				{InputID::TURN_R,XINPUT_BUTTON_B},
				{InputID::SPACE,XINPUT_BUTTON_A} };
	joyPadNum_ = GetJoypadNum();
	return true;
}

void Pad::DebugDrow(int id)
{
	if(id==0)
	DrawFormatString(0, 0, 0xffffff, "inputMode: Pad");
	if (id == 1)
		DrawFormatString(400, 0, 0xffffff, "inputMode: Pad");
}

