#pragma once
#include <algorithm>
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct DROP
{
	void operator()(Stage* stage) {
		Vector2 tmp;


		stage->GetChainCount_ = 0;
		stage->SetPuyoGuide();
		if (stage->stgMode == STG_MODE::DROP)
		{
			stage->stgMode = STG_MODE::FALL;
			stage->setPermition((*stage->puyo_[0]));
			stage->setPermition((*stage->puyo_[1]));
			stage->puyo_[0]->drop();
			stage->puyo_[1]->drop();

			//‰º•ûŒü‚ÉˆÚ“®‚Å‚«‚È‚¢‚©Šm”F‚·‚é
			if (stage->puyo_[0]->dirPer_.perBit.d == 0&&stage->puyo_[1]->dirPer_.perBit.d==0)
			{
				stage->stgMode = STG_MODE::DROP;
				
			}		// ‚¢‚È‚©‚Á‚½‚çíœó‘Ô‚É•ÏX
			if (stage->stgMode == STG_MODE::FALL)
			{
				tmp = stage->puyo_[0]->GetGridPos();
				stage->puyo_[0]->SetMatchGrid();
				tmp = stage->puyo_[1]->GetGridPos();
				stage->puyo_[1]->SetMatchGrid();
			}
		}
	}
};