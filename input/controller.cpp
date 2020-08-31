#include <DxLib.h>
#include "controller.h"
#include "mouse.h"
#include "keyInput.h"
#include "Pad.h"
#include "../stage.h"
#include "../Puyo/Puyo.h"
#include "../Puyo/nextPuyo.h"
#include "../Puyo/ObsPuyo.h"

int controller::joyPadNum_ = 0;


void controller::ResetJoyPadNum()
{
	joyPadNum_ = DxLib::ReSetupJoypad();
}

void controller::AutoChangeInput(SharCntr& sharCnt, int stageID)
{
	joyPadNum_ = GetJoypadNum();

	if (joyPadNum_ > stageID)
	{
		if (sharCnt->GetType() != ContType::Pad)
		{
			sharCnt = std::make_unique<Pad>();
			sharCnt->Setup(stageID);
		}
	}
	if (sharCnt->GetType() == ContType::Pad)
	{
		if (joyPadNum_ ==0)
		{
			if (sharCnt->GetType() != ContType::Key)
			{
				sharCnt = std::make_unique<KeyInput>();
				sharCnt->Setup(stageID);
			}
		}
	}
}


void controller::SetStgData(std::vector<PUYO_TYPE> stgDataBase, 
						std::vector<std::shared_ptr<Puyo>> nextPuyo,
						std::pair<PUYO_TYPE, PUYO_TYPE> CntlPuyoType)
{
	CntlPuyoType_ = CntlPuyoType;
	stgDataBase_ = stgDataBase;
	nextPuyo_ = nextPuyo;
	
	for (int i = 0; i < gridCountX_; i++)
	{
		stgData_.emplace_back(&stgDataBase_[STCI(i * gridCountY_)]);
	}
	SetStgDataFlag_ = true;
}

void controller::SetStgType(STG_MODE stgMode)
{
}

void controller::InitTexture()
{
	TxHdl_ = { inputTextuerName_.GetTexture("Image/AI���[�h.png"),
			inputTextuerName_.GetTexture("Image/�L�[�{�[�h�ɂイ��傭.png"),
			inputTextuerName_.GetTexture("Image/�}�E�X�ɂイ��傭.png"),
			inputTextuerName_.GetTexture("Image/�ς��ǂɂイ��傭.png") };
}
