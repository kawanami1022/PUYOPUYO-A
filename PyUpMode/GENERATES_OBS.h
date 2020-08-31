#pragma once
#include "../stage.h"
#include "../Puyo/Puyo.h"
struct GENERATES_OBS
{
	void operator()(Stage* stage)
	{
		Vector2 tmp;
		if (!stage->obsPuyoList_.empty())
		{

		}
		// お邪魔ぷよカウンターが3つ以上
		// obsPuyo落下
		for (auto&& ObsPuyoList_ : stage->obsPuyoList_)
		{
			ObsPuyoList_.DropCount--;
			tmp = ObsPuyoList_.GetGridPos();
			stage->obsPuyo_.emplace_back(std::make_unique<ObsPuyo>(stage->offset_, (tmp, tmp), stage->GrHandle_[STCI(PUYO_TYPE::OBS)]));
		}
		stage->obsPuyoList_.clear();
		auto rmObs = std::remove_if(stage->obsPuyoList_.begin(), stage->obsPuyoList_.end(), [&](auto&& obsPy)
			{
				return obsPy.DropCount <= 0;
			});

		stage->obsPuyoList_.erase(rmObs, stage->obsPuyoList_.end());
		stage->stgMode = STG_MODE::DROP_OBS;
	}
};