#pragma once
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct MUNYOUN
{
	void operator()(Stage* stage)
	{
		Vector2 tmp;
		for (auto&& PUYO : stage->puyo_)
		{
			tmp = PUYO->GetGridPos();
			PUYO->munyonBox_.perBit = { 0,0,0,0 };
			//同色のpuyoがないか確認
			// 上
			if (stage->stgData_[tmp.x][tmp.y]== stage->stgData_[tmp.x][tmp.y-1])
				PUYO->munyonBox_.perBit.u = 1;
			// 下
			if (stage->stgData_[tmp.x][tmp.y] == stage->stgData_[tmp.x][tmp.y + 1])
				PUYO->munyonBox_.perBit.d = 1;
			// 右
			if (stage->stgData_[tmp.x][tmp.y] == stage->stgData_[tmp.x + 1][tmp.y])
				PUYO->munyonBox_.perBit.r= 1;
			// 左
			if (stage->stgData_[tmp.x][tmp.y] == stage->stgData_[tmp.x - 1][tmp.y])
				PUYO->munyonBox_.perBit.l = 1;
		}
		stage->stgMode = STG_MODE::ERASE;
	}
};