#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		stage->stgMode = STG_MODE::DROP;
		stage->GetChainCount_ = 0;

		
		if (stage->obsPuyo_.size() >0)
		{
			stage->ObsDropCnt_++;
		}

		// お邪魔ぷよカウンターが3つ以上
		// obsPuyo落下
		if (stage->ObsDropCnt_ > 3)
		{
			stage->ObsDropCnt_ = 0;
			int count = 0;
			for (auto&& ObsPuyo : stage->obsPuyo_)
			{
			}
		}
		for (int x = 0; x < stage->gridCountX-1; x++) {
			if (stage->stgData_[x][1] != PUYO_TYPE::NON || stage->stgData_[x][1] != PUYO_TYPE::WALL)
			{
				stage->makePuyo();
				break;
			}
		}
	}
};