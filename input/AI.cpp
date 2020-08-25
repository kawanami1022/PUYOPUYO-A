#include <DxLib.h>
#include "AI.h"
#include "../stage.h"
#include "../Puyo/Puyo.h"
#include "../Puyo/nextPuyo.h"
#include "../Puyo/ObsPuyo.h"

void AI::Update()
{
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

void AI::SetStgData(std::vector<PUYO_TYPE> stgDataBase, std::shared_ptr<Puyo> nextPuyo)
{
	stgDataBase_ = stgDataBase;
	nextPuyo_ = nextPuyo;
	for (int i = 0; i < gridCountX_; i++)
	{
		stgData_.emplace_back(&stgDataBase_[i * gridCountY_]);
	}
}

