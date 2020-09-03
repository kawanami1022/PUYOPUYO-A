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
		if (stage->puyo_.size() == 0)	stage->stgMode = STG_MODE::GENERATES;



		for (int id = 0; id < 2; id++)
		{

			for (auto&& Puyo : stage->puyo_)
			{
				try
				{

					if (stage->puyo_[id]->GetGridPos().x == Puyo->GetGridPos().x)
					{
						int MatchGridPosY = Puyo->GetGridPos().y * Puyo->blockSize + Puyo->offsetPos_.y + Puyo->blockSize / 2;
						int mag = (stage->gridCountY-1)-Puyo->GetGridPos().y;	// puyoのy座標によって移動倍率を求める

						Puyo->radious.x = Puyo->blockSize / 2 - offsetRadious.x;
						Puyo->radious.y = Puyo->blockSize / 2 - offsetRadious.y;
						Puyo->ROffPos_.y = offsetRadious.y * mag;
					}
				}
				catch (...)
				{
					std::cout << "accecssed the non - exisit puyo!" << std::endl;
				}
			}
		}

		for (auto&& ObsPuyo : stage->obsPuyo_)
		{
			if (stage->puyo_[0]->GetGridPos().x == ObsPuyo->GetGridPos().x||
				stage->puyo_[1]->GetGridPos().x == ObsPuyo->GetGridPos().x)
			{
				int MatchGridPosY = ObsPuyo->GetGridPos().y * ObsPuyo->blockSize + ObsPuyo->offsetPos_.y + ObsPuyo->blockSize / 2;
				int mag = (stage->gridCountY - 1) - ObsPuyo->GetGridPos().y;	// puyoのy座標によって移動倍率を求める

				ObsPuyo->radious.x = ObsPuyo->blockSize / 2 - offsetRadious.x;
				ObsPuyo->radious.y = ObsPuyo->blockSize / 2 - offsetRadious.y;
				ObsPuyo->ROffPos_.y = offsetRadious.y * mag;
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