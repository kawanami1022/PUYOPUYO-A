#include <functional>
#include <DxLib.h>
#include "AI.h"


void AI::Update()
{
	if (SetStgDataFlag_)
	{
		IdntSmColor();
		SetInputPattern();
		SetStgDataFlag_ = false;
	}
	frame_++;
}

ContType AI::GetType(void)
{
	return ContType();
}

bool AI::Setup(int no)
{
	InputStateContainer_ =
	{ {InputID::Up,std::make_pair(0,0)},
	{InputID::Down,std::make_pair(1,1)},
	{InputID::Left,std::make_pair(1,0)},
	{InputID::Right,std::make_pair(1,0)},
	{InputID::TURN_L,std::make_pair(1,0)},
	{InputID::TURN_R,std::make_pair(1,0)} };

	gridCountX_ = 8;
	gridCountY_ = 15;
	frame_ = 0;
	PyLdPoint_ = { 0,0 };
	return false;
}

bool AI::push(InputID inputID)
{
	return false;
}

bool AI::release(InputID inputID)
{
	return false;
}

bool AI::Hold(InputID inputID)
{
	return false;
}

bool AI::separate(InputID inputID)
{
	return false;
}

void AI::DebugDrow(int id)
{
	if (id == 0)
		DrawFormatString(0, 0, 0xffffff, "inputMode: AI");
	if (id == 1)
		DrawFormatString(400, 0, 0xffffff, "inputMode: AI");
}

void AI::changeInputTbl(int, InputID)
{
}

void AI::PadForceFeedback(int, int)
{

}

// ���F��puyo������
void AI::IdntSmColor()
{
	int samePuyoColor_=0;		// ���Fpuyo
	Vector2 SetPos = { 0,0 };

	auto func = [&]() {
		//��
		if (stgData_[SetPos.x][SetPos.y - 1] == PUYO_TYPE::NON)
		{

		}
		//�E
		if (stgData_[SetPos.x + 1][SetPos.y] == PUYO_TYPE::NON)
		{

		}
		//��
		if (stgData_[SetPos.x][SetPos.y - 1] == PUYO_TYPE::NON)
		{

		}
		//��
		if (stgData_[SetPos.x - 1][SetPos.y] == PUYO_TYPE::NON)
		{

		}
	};

	for (int x = 1; x < gridCountX_ - 1; x++)
	{
		// ���ꂼ���y�����Ƃ̈�ԉ��ɂ���PUYO_TYPE::NON�̏ꏊ�𒲂ׂ�
		for (int y = 1; y < gridCountY_; y++)
		{
			if (stgData_[x][y] != PUYO_TYPE::NON)
			{
				SetPos = { x,y - 1 };
				stgData_[SetPos.x][SetPos.y] = CntlPuyoType_.first;
				// PUYO_TYPE::NON�ȊO�������Ă��Ȃ����m�F

				func();
				break;
			}
		}
	}
}

void AI::SetInputPattern()
{
}

void AI::ResetFrame()
{
}


