#pragma once
#include <iterator>
#include <algorithm>
#include <vector>
#include "../stage.h"
#include "../Puyo/Puyo.h"
#include "../_debug/_DebugConOut.h"
struct FALL
{
	void operator()(Stage* stage) {
		Vector2 tmp;

		stage->stgMode = STG_MODE::PUYON;
		int id=STCI(stage->puyo_.size() - 1);

		std::for_each(stage->puyo_.crbegin(), stage->puyo_.crend(), 
			[&](auto&& puyo){
			tmp = puyo->GetGridPos();
			stage->setPermition((*puyo));
			if (stage->stgData_[tmp.x][tmp.y + 1] == PUYO_TYPE::NON)
			{
				stage->stgMode = STG_MODE::FALL;
				puyo->pos_.y+=8;
			}
			if (stage->stgMode == STG_MODE::PUYON)
				puyo->SetMatchGrid();
			id--;
		});


		stage->SetStageData();
	}
};