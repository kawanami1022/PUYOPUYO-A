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
		int idx = 0;

		for (auto&& Puyo : stage->puyo_)
		{
			if (offsetRadious.y <= 0)
			{

				Puyo->radious.y = Puyo->blockSize / 2;
				stage->stgMode = STG_MODE::MUNYON;
				idx++;
				if (idx == 2)break;
			}
		}
	

	}
private:
	int frame;
};