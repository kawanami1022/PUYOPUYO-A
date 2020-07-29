#pragma once
#include "../Vector2.h"
#include "../stage.h"
#include "../Puyo.h"
struct IpLeft
{
	void operator()(Stage* stage)
	{
		if (stage->puyo_[0]->dirPer_.perBit.l == 0)
		{
			stage->puyo_[0]->pos_.x -= stage->puyo_[0]->blockSize;
			stage->puyo_[1]->pos_.x -= stage->puyo_[1]->blockSize;
		}
	}
};