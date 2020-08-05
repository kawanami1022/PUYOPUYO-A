#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		Vector2 tmp;
		stage->stgMode = STG_MODE::DROP;

		//for (int i = 1; i < SetChainCount_; i++)
		//{
		//	obsPuyo_.push_front(ObsPuyo(offset_, Vector2(i, 0)));
		//}

		// お邪魔ぷよカウンターが3つ以上
		// obsPuyo落下
		for (auto&& ObsPuyo : stage->obsPuyo_)
		{
			ObsPuyo.DropCount--;
			if (ObsPuyo.DropCount == 0)
			{
				tmp = ObsPuyo.GetGridPos();
				stage->puyo_.emplace_back(std::make_unique<Puyo>(stage->offset_, (tmp,tmp), PUYO_TYPE::OBS));
			}
		}
		auto rmObs = std::remove_if(stage->obsPuyo_.begin(), stage->obsPuyo_.end(), [&](auto&& obsPy)
		{
			return obsPy.DropCount <= 0;
		});

		stage->obsPuyo_.erase(rmObs, stage->obsPuyo_.end());

		for (int x = 0; x < stage->gridCountX-1; x++) {
			if (stage->stgData_[x][1] != PUYO_TYPE::NON || stage->stgData_[x][1] != PUYO_TYPE::WALL)
			{
				stage->makePuyo();
				break;
			}
		}
	}
};