#pragma once
#include <string>
#include <map>
#include <memory>
#include "../Input/CommonInputID.h"
#include "../input/ComInput.h"
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
protected:
	// 入力系
	static std::shared_ptr<ComInput> comInput;
	static SharCntr controller;
	// 画像
	SharTexture textureFactory;
	std::map<std::string, SharTexture> textureContainer;
private:
	void SceneInit();
	static int IstcCnt_;	// インスタンス回数
};



