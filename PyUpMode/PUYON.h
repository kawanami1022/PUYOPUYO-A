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
		for (int id = 0; id < 2; id++)
		{

			puyoMatchGrid[id].y= stage->puyo_[id]->GetGridPos().y * stage->puyo_[id]->blockSize + stage->puyo_[id]->offsetPos_.y + stage->puyo_[id]->blockSize / 2,


			stage->puyo_[id]->radious.y = stage->puyo_[id]->blockSize/2- offsetRadious.y;
			stage->puyo_[id]->pos_.y = puyoMatchGrid[id].y + offsetRadious.y;

			for (auto&& PUYO : stage->puyo_)
			{
				if (stage->puyo_[id]->GetGridPos().x == PUYO->GetGridPos().x)
				{
					PUYO->radious.y = PUYO->blockSize / 2 - offsetRadious.y;
					PUYO->pos_.y = puyoMatchGrid[id].y + offsetRadious.y;
				}
			}


			if (offsetRadious.y <=0)
			{
				stage->puyo_[id]->radious.y = stage->puyo_[id]->blockSize/2;
				stage->stgMode = STG_MODE::ERASE;
			}
		}


	}
private:
	int frame;
};