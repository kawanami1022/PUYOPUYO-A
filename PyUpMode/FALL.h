#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct FALL
{
	void operator()(Stage* stage) {
		Vector2 tmp;
		
		stage->stgMode = STG_MODE::GENERATES;
		for (int i = stage->gridCountX * stage->gridCountY - 1; 0 < i; i--)
		{
			if (stage->stgData_[i % stage->gridCountX][i / stage->gridCountX] != PUYO_TYPE::NON && 
				stage->stgData_[i % stage->gridCountX][i / stage->gridCountX] != PUYO_TYPE::WALL)
			{
				//setPermition(tmp);
				//check enable to down
				if (stage->stgData_[i % stage->gridCountX][i / stage->gridCountX + 1] == PUYO_TYPE::NON) {
					stage->stgMode = STG_MODE::FALL;
					stage->FallPyPos_.emplace_back(Vector2(i % stage->gridCountX, i / stage->gridCountX));

				}		// ‚¢‚È‚©‚Á‚½‚ç¶¬ó‘Ô‚É•ÏX
			}
		};
		for (auto&& Puyo : stage->puyo_)
		{
			for (auto&& FallPuyo : stage->FallPyPos_)
			{
				if (FallPuyo == Puyo->GetGridPos())
				{
					tmp = FallPuyo;
					stage->setPermition(tmp);
					Puyo->setMovePer(stage->dirPer);
					Puyo->drop();
				}
			}
		}
		stage->SetStageData();
	}
};