#pragma once
#include "../Vector2.h"
#include "../stage.h"
#include "../Puyo/Puyo.h"
struct IpLeft
{
	void operator()(Stage* stage)
	{

		std::array<Positoin2, 2> posCopy = { stage->puyo_[0]->pos_ ,stage->puyo_[1]->pos_ };

		posCopy[0].x -= stage->puyo_[0]->blockSize;
		posCopy[1].x -= stage->puyo_[1]->blockSize;

		for (int i = 0; i < 2; i++)
		{
			if (stage->GetStageData(stage->GetGridPos(posCopy[i])) != PUYO_TYPE::NON)return;
		}
		stage->puyo_[0]->pos_ = posCopy[0];
		stage->puyo_[1]->pos_ = posCopy[1];



	}
};