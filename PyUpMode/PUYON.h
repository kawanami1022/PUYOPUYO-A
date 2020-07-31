#pragma once
#pragma once
#include <cmath>
#include "../stage.h"
#include "../Puyo.h"

struct PUYON
{
	PUYON(){
		frame = 3*6;}
	void operator()(Stage* stage) {
		frame++;
		Vector2 offsetRadious(0, abs((frame) % 12 - 6));
		Vector2 puyoMatchGrid[2];
		puyoMatchGrid[0].y= stage->puyo_[0]->GetGridPos().y * stage->puyo_[0]->blockSize + stage->puyo_[0]->offsetPos_.y + stage->puyo_[0]->blockSize / 2,
		puyoMatchGrid[1].y= stage->puyo_[1]->GetGridPos().y * stage->puyo_[1]->blockSize + stage->puyo_[1]->offsetPos_.y + stage->puyo_[1]->blockSize / 2,

		stage->puyo_[0]->radious.y = stage->puyo_[0]->blockSize/2- offsetRadious.y;
		stage->puyo_[1]->radious.y = stage->puyo_[1]->blockSize/2 - offsetRadious.y;
		stage->puyo_[0]->pos_.y = puyoMatchGrid[0].y + offsetRadious.y;
		stage->puyo_[1]->pos_.y = puyoMatchGrid[1].y + offsetRadious.y;
		if (offsetRadious.y <=0)
		{
			stage->puyo_[0]->radious.y = stage->puyo_[0]->blockSize/2;
			stage->puyo_[1]->radious.y = stage->puyo_[1]->blockSize/2;
			stage->stgMode = STG_MODE::ERASE;
		}
	}
private:
	int frame;
};