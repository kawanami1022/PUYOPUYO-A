#pragma once
#include <algorithm>
#include <vector>
#include "../stage.h"
#include "../Puyo.h"
#include "../_debug/_DebugConOut.h"
struct FALL
{
	void operator()(Stage* stage) {
		Vector2 tmp;
		stage->stgMode = STG_MODE::ERASE;
		int id=stage->puyo_.size() - 1;

		std::for_each(stage->puyo_.crbegin(), stage->puyo_.crend(), 
			[&](auto&& puyo){
			tmp = puyo->GetGridPos();
			stage->setPermition(tmp, id);
			TRACE("%d\n", static_cast<int>(stage->stgData_[tmp.x][tmp.y + 1]))
			if (stage->stgData_[tmp.x][tmp.y + 1] == PUYO_TYPE::NON)
			{
				stage->stgMode = STG_MODE::FALL;
				puyo->drop();
			}
			id--;
		});
		TRACE("-----------------------\n")
		stage->SetStageData();
	}
};