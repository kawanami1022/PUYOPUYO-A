#include "Pad.h"

ContType Pad::GetType(void)
{
	return ContType::Pad;
}

void Pad::Update()
{
	int joyPadNum = GetJoypadNum();		// �W���C�p�b�h���ڑ�����Ă��Ԃ��擾����
	GetJoypadXInputState(PadIdList_[id_], &_xInputData.data()[0]);
	for (auto _id : InputID())
	{
		_data[_id][static_cast<int>(Trg::Old)] = _data[_id][static_cast<int>(Trg::Now)];
		_data[_id][static_cast<int>(Trg::Now)] = _xInputData.data()->Buttons[_xInputTbl[_id]];
	}
	frame_++;
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
	frame_ = 0;
	id_ = no;
	PadIdList_ = { DX_INPUT_PAD1 ,DX_INPUT_PAD2 };
	_xInputTbl = { {InputID::Up,XINPUT_BUTTON_DPAD_UP},
				{InputID::Down, XINPUT_BUTTON_DPAD_DOWN},
				{InputID::Left,XINPUT_BUTTON_DPAD_LEFT},
				{InputID::Right,XINPUT_BUTTON_DPAD_RIGHT},
				{InputID::TURN_L,XINPUT_BUTTON_A},
				{InputID::TURN_R,XINPUT_BUTTON_B} };
	joyPadNum_ = GetJoypadNum();
	return true;
}

void Pad::changeInputTbl(int inputButton, InputID inputID)
{
	_xInputTbl[inputID] = inputButton;
}

void Pad::PadForceFeedback(int Power, int Time)
{
	StartJoypadVibration(id_+1, Power, Time);
}


void Pad::DebugDrow(int id, Texture& texture)
{
	if(id==0)
		DrawGraph(0, 0, texture.GetHandle(), true);
	if (id == 1)
		DrawGraph(400, 0, texture.GetHandle(), true);
}

