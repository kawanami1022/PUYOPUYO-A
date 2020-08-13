#pragma once
#include <memory>
#include "../Texture/TextureFactory.h"
#include "../Texture/Texture.h"

class BaseScene;

using UniqueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual UniqueBase input(UniqueBase) = 0;
	virtual UniqueBase upDate(UniqueBase) = 0;

	virtual void Draw() = 0;

private:
	
};



