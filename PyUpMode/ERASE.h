#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct ERASE
{
	void operator()(Stage* stage){
		Vector2 tmp;
		stage->stgMode = STG_MODE::GENERATES;
		stage->SetStageData();
		for (int i = stage->gridCountX * stage->gridCountY; 0 < i; i--)
		{
			if (stage->stgData_[i % stage->gridCountX ][i / stage->gridCountX] != PUYO_TYPE::NON &&
				stage->stgData_[i % stage->gridCountX][i / stage->gridCountX] != PUYO_TYPE::WALL)
			{
				tmp = { i % stage->gridCountX ,i / stage->gridCountX };
				if (stage->ErasePuyo(std::move(tmp)))
				{
					stage->DeletePuyo();
					stage->stgMode = STG_MODE::FALL;
					break;
				}
			}
		}

		stage->ErPyDelPos_.clear();
		stage->SetStageData();
	}
};