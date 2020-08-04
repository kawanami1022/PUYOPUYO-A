#pragma once
#include <iterator>
#include <algorithm>
#include <vector>
#include "../stage.h"
#include "../Puyo.h"
#include "../_debug/_DebugConOut.h"
struct FALL
{
	void operator()(Stage* stage) {
		Vector2 tmp;

		stage->stgMode = STG_MODE::PUYON;
		int id=stage->puyo_.size() - 1;

		// お邪魔ぷよカウンターが3つ以上
		// obsPuyo落下
		if (stage->ObsDropCnt_ > 3)
		{
			stage->ObsDropCnt_ = 0;
			int count = 0;
			for (auto&& ObsPuyo : stage->obsPuyo_)
			{
				tmp = ObsPuyo.GetGridPos();
				stage->setPermition(tmp, id);
				auto stg = std::next(stage->obsPuyo_.begin(), count);
				if (stg->GetGridPos().x == 1)
				{break;}
			}
		}
		else
		{
			std::for_each(stage->puyo_.crbegin(), stage->puyo_.crend(), 
				[&](auto&& puyo){
				tmp = puyo->GetGridPos();
				stage->setPermition(tmp, id);
				if (stage->stgData_[tmp.x][tmp.y + 1] == PUYO_TYPE::NON)
				{
					stage->stgMode = STG_MODE::FALL;
					puyo->drop();
				}
				id--;
			});
		}
		stage->SetStageData();
	}
};