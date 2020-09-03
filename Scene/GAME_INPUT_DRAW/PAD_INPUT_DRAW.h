#pragma once
#include "../GameScene.h"
struct PAD_INPUT_DRAW
{
	void operator()(GameScene& title)
	{
		DrawFormatString(340, 510 - title.texture_[1]->GetSize().y / 2, 0xffffff, "press");
		DrawFormatString(420, 510 - title.texture_[1]->GetSize().y / 2, 0xffffff, "key");
		DrawGraph(400 - title.texture_[1]->GetSize().x / 2,
			500 - title.texture_[1]->GetSize().y / 2,
			title.texture_[1]->GetHandle(), true);
	}
};