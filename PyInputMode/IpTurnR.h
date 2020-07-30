#pragma once
#include <utility>
#include "../Vector2.h"
#include "../stage.h"
#include "../Puyo.h"

struct IpTurnR
{
	void operator()(Stage* stage)
	{
		// �E
		if (stage->puyo_[0]->GetGridPos().x + 1 == stage->puyo_[1]->GetGridPos().x)
		{
			stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x,stage->puyo_[0]->pos_.y + stage->blockSize };
			std::swap(stage->puyo_[1], stage->puyo_[0]);
		}
		// ��
		else if (stage->puyo_[0]->GetGridPos().y + 1 == stage->puyo_[1]->GetGridPos().y)
		{
			stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x - stage->blockSize ,stage->puyo_[0]->pos_.y };
			std::swap(stage->puyo_[1], stage->puyo_[0]);
		}
		// ��
		else if (stage->puyo_[0]->GetGridPos().x - 1 == stage->puyo_[1]->GetGridPos().x)
		{
			stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x  ,stage->puyo_[0]->pos_.y - stage->blockSize };
		}
		// ��
		else if (stage->puyo_[0]->GetGridPos().y - 1 == stage->puyo_[1]->GetGridPos().y)
		{
			stage->puyo_[1]->pos_ = { stage->puyo_[0]->pos_.x + stage->blockSize ,stage->puyo_[0]->pos_.y };
		}

	}
};