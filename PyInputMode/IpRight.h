#pragma once
#include "../Vector2.h"
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct IpRight
{
	void operator()(Stage* stage)
	{
		if (stage->puyo_[1]->dirPer_.perBit.r == 0)
		{
			stage->puyo_[0]->pos_.x += stage->puyo_[0]->blockSize;
			stage->puyo_[1]->pos_.x += stage->puyo_[1]->blockSize;
		}
	}
};