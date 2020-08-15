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
		// �G�t�F�N�g���Z�b�g����
		if (frame == 0)
		{
			int idx = 0;
			for (auto&& ErPyDel : stage->ErPyDel_)
			{
				stage->playEfkHandle_.emplace_back(
					PlayEffekseer2DEffect(stage->EffectHandle_[STCI(ErPyDel->GetPuyoType())]->GetHandle()));
				SetPosPlayingEffekseer2DEffect(stage->playEfkHandle_.back(),
					ErPyDel->pos_.x, ErPyDel->pos_.y, 0);

			}

		}
		for (auto&& PlEfkHdl : stage->playEfkHandle_)
		{
			if (frame == 60 * 3)
			{
				
				StopEffekseer2DEffect(PlEfkHdl);}
			stage->stgMode = STG_MODE::FALL;
			//�Đ�����ĂȂ�������Fall��ԂɕύX
			if (IsEffekseer2DEffectPlaying(PlEfkHdl) == 0)
			{
				stage->stgMode = STG_MODE::EFFECT;
				break;
			}
		}

		if (stage->stgMode == STG_MODE::FALL)
		{
			frame = 0;
			stage->playEfkHandle_.clear();
			stage->ErPyDel_.clear();
		}
		frame++;
	}
};