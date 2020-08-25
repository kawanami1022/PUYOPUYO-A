#pragma once
#include "../Puyo/Puyo.h"
#include "../stage.h"

struct DRAWPLAYING
{
	void operator()(Stage& stg)
	{
		stg.controller_->DebugDrow(stg.id_);

		for (int y = 0; y < stg.gridCountY; y++)
		{
			for (int x = 0; x < stg.gridCountX; x++)
			{
				if (stg.stgData_[x][y] == PUYO_TYPE::WALL)
					DrawGraph(stg.offset_.x + x * stg.blockSize,
						stg.offset_.y + y * stg.blockSize, stg.GrHandle_[STCI(PUYO_TYPE::WALL)], true);
			}
		}

		DrawLine(stg.offset_.x, stg.offset_.y + stg.blockSize * stg.gridCountY,
			stg.offset_.x + stg.gridCountX * stg.blockSize, stg.offset_.y + stg.blockSize * stg.gridCountY,
			0xffffff, false);
		int idx = 0;
		for (auto&& PUYO : stg.puyo_)
		{
			PUYO->draw();
			DrawFormatString(PUYO->pos_.x, PUYO->pos_.y, 0xffffff, "%d", idx);
			
			idx++;
		}

		if(stg.puyo_.size()>0)DrawGraph(stg.puyo_[0]->pos_.x - 20, stg.puyo_[0]->pos_.y - 20, stg.GrHandle_[9], true);

		for (auto&& OBSPUYOLIST : stg.obsPuyoList_)
		{
			OBSPUYOLIST.draw();
		}

		for (auto&& OBSPUYO : stg.obsPuyo_)
		{
			OBSPUYO->draw();
		}

		for (auto&& GuidePos : stg.GuidePyPos_)
		{
			DrawGraph(stg.offset_.x + GuidePos.x * stg.blockSize, stg.offset_.y + GuidePos.y * stg.blockSize,
				stg.GrHandle_[8], true);
		}

		DrawBox(stg.nextBoxPos.x + (stg.screenSizeX / 8) * (3 + stg.id_) - stg.blockSize / 2,
			stg.nextBoxPos.y,
			stg.nextBoxPos.x + (stg.screenSizeX / 8) * (3 + stg.id_) + stg.blockSize / 2,
			stg.nextBoxPos.y + stg.blockSize * 2,
			0xffffff, false);

		for (auto&& NEXTPUYO : stg.nextPuyo_)
		{
			NEXTPUYO->draw();
		}
	}
};