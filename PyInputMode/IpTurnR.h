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
			stage->controller_->PadForceFeedback(1000, 200);
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
				if (stage->puyo_[i]->GetGridPos() <= Vector2(0, 0) ||
					Vector2(stage->gridCountX - 1, stage->gridCountY - 1) <= stage->puyo_[i]->GetGridPos())
				{
					func();
				}
			}
		};
		func();
	}
};