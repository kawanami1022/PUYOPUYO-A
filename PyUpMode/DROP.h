#pragma once
#include <algorithm>
#include "../stage.h"
#include "../Puyo.h"

struct DROP
{
	void operator()(Stage* stage) {
		Vector2 tmp;

		if (stage->stgMode == STG_MODE::DROP)
		{
			stage->stgMode = STG_MODE::ERASE;
			std::for_each(stage->puyo_.crbegin(), stage->puyo_.crend(),
				[&](auto&& puyo) {
				tmp = puyo->GetGridPos();
				stage->setPermition(tmp);
				puyo->setMovePer(stage->dirPer);
				puyo->drop();
				//下方向に移動できないか確認する
				if (stage->dirPer.perBit.d == 0)
				{
					stage->stgMode = STG_MODE::DROP;
				}		// いなかったら削除状態に変更
			});
			if (stage->stgMode == STG_MODE::ERASE)
			{
				tmp = stage->puyo_[0]->GetGridPos();
				stage->puyo_[0]->SetMatchGrid(std::move((tmp + 1) * stage->blockSizeX));
			}
		}
	}
};