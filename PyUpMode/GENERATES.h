#pragma once
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		Vector2 tmp;

		if(stage->controller_->GetType()==ContType::AI)
		{
			stage->controller_->SetStgData(stage->stgDataBase_, stage->nextPuyo_);
		}


		stage->stgMode = STG_MODE::DROP;

		// お邪魔ぷよカウンターが3つ以上
		// obsPuyo落下
		for (auto&& ObsPuyoList_ : stage->obsPuyoList_)
		{
			ObsPuyoList_.DropCount--;
			tmp = ObsPuyoList_.GetGridPos();
			//stage->puyo_.emplace_back(std::make_unique<Puyo>(stage->offset_, (tmp,tmp), PUYO_TYPE::OBS, stage->GrHandle_[S(PUYO_TYPE::OBS)]));
			stage->obsPuyo_.emplace_back(std::make_unique<ObsPuyo>(stage->offset_, (tmp,tmp), stage->GrHandle_[STCI(PUYO_TYPE::OBS)]));
		}
		stage->obsPuyoList_.clear();
		auto rmObs = std::remove_if(stage->obsPuyoList_.begin(), stage->obsPuyoList_.end(), [&](auto&& obsPy)
		{
			return obsPy.DropCount <= 0;
		});

		stage->obsPuyoList_.erase(rmObs, stage->obsPuyoList_.end());

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