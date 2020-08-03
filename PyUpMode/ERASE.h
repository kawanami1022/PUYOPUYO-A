#pragma once
#include <iterator>
#include <list>
#include "../stage.h"
#include "../Puyo.h"
#include "../ObsPuyo.h"

struct ERASE
{
	void operator()(Stage* stage){
		Vector2 tmp;
		for(int i=1;i<stage->chainCount_;i++)
		{
			stage->obsPuyo_.emplace_back(ObsPuyo(stage->offset_, Vector2(i, 0)));
		}

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
					stage->chainCount_++;
					stage->DeletePuyo();
					stage->stgMode = STG_MODE::FALL;
					break;
				}
			}
		}

		stage->ErPyDelPos_.clear();
		stage->SetStageData();
	}
private:

};