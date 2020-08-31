#pragma once
#include "../stage.h"

struct DROP_OBS
{
	void operator()(Stage* stg)
	{
		stg->stgMode = STG_MODE::GENERATES;
		stg->makeObsPuyoList();
		for (auto&& ObsPuyo : stg->obsPuyo_)
		{
			stg->setPermition((*ObsPuyo));
			if (ObsPuyo->drop())
			{
				stg->stgMode = STG_MODE::DROP_OBS;
			}
		}
	}
};