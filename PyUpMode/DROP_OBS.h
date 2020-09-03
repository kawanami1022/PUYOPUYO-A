#pragma once
#include <random>
#include "../stage.h"

struct DROP_OBS
{
	void operator()(Stage* stg)
	{
		std::random_device seed_gen;
		std::mt19937 random_(seed_gen());
		std::uniform_int_distribution<int> dist(-3, 3);
		stg->shackPos_.x = static_cast<int>(dist(random_));
		stg->shackPos_.y = static_cast<int>(dist(random_));


		stg->stgMode = STG_MODE::GENERATES;

		for (auto&& ObsPuyo : stg->obsPuyo_)
		{
			stg->setPermition((*ObsPuyo));
			// ���Ƃ���obspuyo����������DropObs���
			if (ObsPuyo->drop(6))
			{
				stg->stgMode = STG_MODE::DROP_OBS;
			}
		}

		if (stg->stgMode == STG_MODE::GENERATES)
		{
			for (auto&& ObsPuyo : stg->obsPuyo_)
			{
				// �Ղ�̈ʒu���O���b�h�ɍ��킹��
				ObsPuyo->SetMatchGrid();
			}
			stg->SetStageData();
		}
	}
};