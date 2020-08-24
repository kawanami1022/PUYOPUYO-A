#pragma once
#include "../TitleScene.h"
struct PAD_INPUT_DRAW
{
	void operator()(TitleScene& title)
	{
		DrawFormatString(340, 510 - title.texture_[1]->GetSize().y / 2, 0xffffff, "press");
		DrawFormatString(420, 510 - title.texture_[1]->GetSize().y / 2, 0xffffff, "key");
		DrawGraph(400 - title.texture_[1]->GetSize().x / 2,
			500 - title.texture_[1]->GetSize().y / 2,
			title.texture_[1]->GetHandle(), true);
	}
};