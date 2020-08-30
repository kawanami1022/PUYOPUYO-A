#pragma once
#include <utility>
#include "../Vector2.h"
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct IpTurnR
{
	void operator()(Stage* stage)
	{
		std::function<void()> func = [&]() {
			// ‰E
			if (stage->puyo_[0]->GetGridPos().x + 1 == stage->puyo_[1]->GetGridPos().x)
			{
				stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x,stage->puyo_[0]->pos_.y + stage->blockSize };
			}
			// ‰º
			else if (stage->puyo_[0]->GetGridPos().y + 1 == stage->puyo_[1]->GetGridPos().y)
			{
				stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x - stage->blockSize ,stage->puyo_[0]->pos_.y };
			}
			// ¶
			else if (stage->puyo_[0]->GetGridPos().x - 1 == stage->puyo_[1]->GetGridPos().x)
			{
				stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x  ,stage->puyo_[0]->pos_.y - stage->blockSize };
			}
			// ã
			else if (stage->puyo_[0]->GetGridPos().y - 1 == stage->puyo_[1]->GetGridPos().y)
			{
				stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x + stage->blockSize ,stage->puyo_[0]->pos_.y };
			}
			for (int i = 0; i < 2; i++)
			{
				Positoin2 tmpPos = stage->puyo_[i]->GetGridPos();
				if(stage->GetStageData(tmpPos)!=PUYO_TYPE::NON)
				{
					func();
				}
			}
		};
		func();
	}
};