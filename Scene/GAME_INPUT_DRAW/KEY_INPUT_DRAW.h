#pragma once
#include "../GameScene.h"
struct KEY_INPUT_DRAW
{
	void operator()(GameScene& title)
	{
		//DrawFormatString(0, 0, 0xffffff, "TitleScene");
		//title.controller->DebugDrow(0);
		if (title.frame_ % 60 > 30)
		{
			DrawGraph(400 - title.texture_[STCI(TxNameID::PUSH_SPC)]->GetSize().x / 2,
				500 - title.texture_[STCI(TxNameID::PUSH_SPC)]->GetSize().y / 2,
				title.texture_[STCI(TxNameID::PUSH_SPC)]->GetHandle(), true);
		}
	}
};