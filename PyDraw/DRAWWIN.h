#pragma once
#include "../Puyo/Puyo.h"
#include "../stage.h"
struct DRAWWIN
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
		stg.StageUI_[STG_TYPE::WIN].DrawUIReductionWidth(
			{ stg.offset_.x + 4 * stg.blockSize,
			stg.offset_.y + 6 * stg.blockSize }, RotaSpeed);
	}

};