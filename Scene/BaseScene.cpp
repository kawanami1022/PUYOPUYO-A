#include <DxLib.h>
#include "../input/keyInput.h"
#include "BaseScene.h"
std::shared_ptr<ComInput> BaseScene::comInput;
SharCntr BaseScene::controller = nullptr;
int BaseScene::IstcCnt_=0;
BaseScene::BaseScene()
{
	controller = std::make_unique<KeyInput>();
	controller->Setup(0);
	controller->AutoChangeInput(controller, 0);
	comInput = std::make_unique<ComInput>();
	comInput->Setup();
	IstcCnt_++;
}

BaseScene::~BaseScene()
{
}

