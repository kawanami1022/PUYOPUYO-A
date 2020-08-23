#include <DxLib.h>
#include "Score.h"

Score::Score(SharTexture txHdl,Positoin2 pos,int id)
{
	txHdl_ = txHdl;
	pos_ = pos;
	id_ = id;
}

void Score::Draw()
{
	if (id_ == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			DrawGraph(pos_.x, pos_.y, txHdl_->GetHandle(), true);
		}
	}
}
