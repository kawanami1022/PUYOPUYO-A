#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		stage->stgMode = STG_MODE::DROP;
		for (int x = 0; x < stage->gridCountX-1; x++) {
			if (stage->stgData_[x][1] != PUYO_TYPE::NON || stage->stgData_[x][1] != PUYO_TYPE::WALL)
			{
				stage->makePuyo();
				break;
			}
		}
	}
};