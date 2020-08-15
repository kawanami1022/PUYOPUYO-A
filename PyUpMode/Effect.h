#pragma once
#include <EffekseerForDXLib.h>
#include "../stage.h"
#include "../Puyo/Puyo.h"

struct EFFECT
{
	int frame;

	EFFECT()
	{
		frame = 0;
	}

	void operator()(Stage *stage)
	{
		if (frame == 0)
		{
			//stage->playEfkHandle_.emplace(stage->EffectHandle_[])
		}
		// エフェクトをセットする

	}
};