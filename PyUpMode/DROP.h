#pragma once
#include <algorithm>
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct DROP
{
	void operator()(Stage* stage) {
		Vector2 tmp;
		stage->GetChainCount_ = 0;

		if (stage->stgMode == STG_MODE::DROP)
		{
			stage->stgMode = STG_MODE::FALL;
			stage->setPermition(stage->puyo_[0]->GetGridPos(), 0);
			stage->setPermition(stage->puyo_[1]->GetGridPos(), 1);
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
				stage->puyo_[0]->SetMatchGrid(std::move((tmp + 1) * stage->blockSize));
				tmp = stage->puyo_[1]->GetGridPos();
				stage->puyo_[1]->SetMatchGrid(std::move((tmp + 1) * stage->blockSize));
			}
		}
	}
};