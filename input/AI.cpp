#include <cmath>
#include <functional>
#include <DxLib.h>
#include "AI.h"
#include "../DxLibForHomeBrew/DxLib_Draw.h"

void AI::Update()
{
	if (SetStgDataFlag_)
	{
		InputPatten_.clear();
		IdntSmColor();
		SetInputPattern();
		SetStgDataFlag_ = false;
	}

	if (!InputPatten_.empty())
	{
		if (frame_ % 30 == 0)
		{
			_data[InputPatten_.front()][static_cast<int>(Trg::Now)] = InputStateContainer_[InputPatten_.front()].first;
			_data[InputPatten_.front()][static_cast<int>(Trg::Old)] = InputStateContainer_[InputPatten_.front()].second;
			InputPatten_.pop_front();
		}
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
	PyLdPoint_ = { { 0,0 },{ 0,0 } };
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

// 同色のpuyoが一番多い場所を識別
void AI::IdntSmColor()
{
	int samePuyoColorMax = 0;		// 同色puyo
	int checkSamePyClr = 0;
	std::pair<Positoin2, Positoin2> SetPos = { { 0,0 },{ 0,0 } };



	// 
	std::function<bool(Vector2)> SetScPos = [&](Vector2 setPos) {
		if (!(setPos.x <= 0 || setPos.y <= 0 || gridCountX_ - 1<= setPos.x || gridCountY_ - 1 <= setPos.x))
		{
			if (stgData_[setPos.x][setPos.y] == PUYO_TYPE::NON)
			{
				SetPos.second = setPos;
				return true;
			}
			else {
				SetScPos(Vector2(setPos.x,setPos.y-1));
			}
		}
		else{return false;}
	};


	// 同色puyoカウンター
	std::function<void(Vector2, PUYO_TYPE)> CountSmPuyo = [&](Vector2 setPos,PUYO_TYPE pyType) {
		//
		std::list<Positoin2> posList=
		{ { setPos.x,setPos.y - 1 },
		{ setPos.x + 1,setPos.y },
		{ setPos.x,setPos.y + 1 },
		{ setPos.x - 1,setPos.y } };

		for (auto POSLIST : posList)
		{
			if (stgData_[POSLIST.x][POSLIST.y] == pyType) {
				checkSamePyClr++;
			}
		}

	};

	for (int x = 1; x < gridCountX_ - 1; x++)
	{
		// それぞれのy軸ごとの一番下にあるPUYO_TYPE::NONの場所を調べる
		for (int y = 1; y < gridCountY_; y++)
		{


			// PUYO_TYPE::NON以外が入っていないか確認
			if (stgData_[x][y] != PUYO_TYPE::NON)
			{
				SetPos.first = { x,y - 1 };
				std::list<Positoin2> pos =
				{ { SetPos.first.x,SetPos.first.y - 1 },
				{ SetPos.first.x + 1,SetPos.first.y },
				{  SetPos.first.x,SetPos.first.y + 1 },
				{ SetPos.first.x - 1,SetPos.first.y } };
				
				for (auto&& POSLIST : pos)
				{
					SetPos.second = POSLIST;
					if (SetScPos(SetPos.second))
					{
						CountSmPuyo(SetPos.first, CntlPuyoType_.first);
						CountSmPuyo(SetPos.second, CntlPuyoType_.second);
					}
					//checkSamePyClrがsamePuyoColor_よりも多かったら座標を更新
					if (checkSamePyClr > samePuyoColorMax)
					{
						samePuyoColorMax = checkSamePyClr;
						PyLdPoint_ = SetPos;		// 操作ぷよの着地点を取得
					}
						checkSamePyClr = 0;
				}
	
				break;
			}
		}
	}
}

void AI::SetInputPattern()
{	
	
	std::pair<Positoin2, Positoin2> GenPyPos = { { 3,1 },{ 4,1 } };// Puyoの生成場所
	std::pair< Positoin2, Positoin2>GenAndLdPosDis =
	{ {GenPyPos.first - PyLdPoint_.first},{GenPyPos.second - PyLdPoint_.second} };

	int InputCounter = abs(GenAndLdPosDis.first.x);

	// 左移動
	if (GenAndLdPosDis.first.x < 0)
	{
		for (int i = 0; i < InputCounter; i++)
		{
			InputPatten_.push_back(InputID::Left);
		}
	}

	// 右移動
	if (GenAndLdPosDis.first.x > 0)
	{
		for (int i = 0; i < InputCounter; i++)
		{
			InputPatten_.push_back(InputID::Right);
		}
	}
}

void AI::ResetFrame()
{
}


