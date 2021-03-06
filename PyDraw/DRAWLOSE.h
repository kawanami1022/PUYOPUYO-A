#pragma once
#include "../Puyo/Puyo.h"
#include "../stage.h"
struct DRAWLOSE
{
	void operator()(Stage& stg)
	{
		for (int y = 0; y < stg.gridCountY; y++)
		{
			for (int x = 0; x < stg.gridCountX; x++)
			{
				if (stg.stgData_[x][y] == PUYO_TYPE::WALL)
					DrawGraph(stg.offset_.x + x * stg.blockSize, stg.offset_.y + y * stg.blockSize, stg.GrHandle_[STCI(PUYO_TYPE::WALL)], true);
			}
		}
		DrawGraph(stg.offset_.x + 1 * stg.blockSize, stg.offset_.y + 1 * stg.blockSize, stg.GmOvHdl_[STCI(STG_TYPE::LOSE)], true);
	}
};