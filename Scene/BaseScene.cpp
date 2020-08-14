#include "BaseScene.h"

BaseScene::BaseScene()
{
	comInput = std::make_unique<ComInput>();
	comInput->Setup();
}

BaseScene::~BaseScene()
{
}

