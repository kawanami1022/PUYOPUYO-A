#pragma once
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		Vector2 tmp;

		if (stage->controller_->GetType() == ContType::AI)
		{
			stage->controller_->SetStgData(
				stage->stgDataBase_, stage->nextPuyo_,
				std::make_pair(stage->nextPuyo_[0]->puyoType_, stage->nextPuyo_[1]->puyoType_));
		}

		stage->stgMode = STG_MODE::DROP;

		for (int x = 0; x < stage->gridCountX-1; x++) {
			if (stage->stgData_[x][1] != PUYO_TYPE::NON || stage->stgData_[x][1] != PUYO_TYPE::WALL)
			{
				stage->makePuyo();
				stage->setNextPuyo();
				break;
			}
		}
		stage->controller_->ResetJoyPadNum();
	}
};