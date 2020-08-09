#pragma once
#pragma once
#include <iostream>
#include <cmath>
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct PUYON
{
	PUYON(){
		frame = 3*6;}
	void operator()(Stage* stage) {
		frame++;
<<<<<<< HEAD
		Vector2 offsetRadious(abs((frame/2) % 6 - 3), abs((frame) % 12 - 6));

		for (int id = 0; id < 2; id++)
		{

			for (auto&& Puyo : stage->puyo_)
			{

				if (stage->puyo_[id]->GetGridPos().x == Puyo->GetGridPos().x)
				{
					int MatchGridPosY = Puyo->GetGridPos().y * Puyo->blockSize + Puyo->offsetPos_.y + Puyo->blockSize / 2;
					int mag = (stage->gridCountY-1)-Puyo->GetGridPos().y;	// puyo‚ÌyÀ•W‚É‚æ‚Á‚ÄˆÚ“®”{—¦‚ð‹‚ß‚é

					Puyo->radious.x = Puyo->blockSize / 2 - offsetRadious.x;
					Puyo->radious.y = Puyo->blockSize / 2 - offsetRadious.y;
					Puyo->ROffPos_.y = offsetRadious.y * mag * 2;
				}
			}
		}
		if (offsetRadious.y <=0)
		{
			stage->puyo_[0]->radious.y = stage->puyo_[0]->blockSize/2;
			stage->puyo_[1]->radious.y = stage->puyo_[1]->blockSize/2;
			stage->stgMode = STG_MODE::MUNYON;
		}
		
=======
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

>>>>>>> master

	}
private:
	int frame;
};