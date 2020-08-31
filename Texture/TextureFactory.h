#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "Texture.h"
using SharTexture = std::shared_ptr<Texture>;
using MapTexture = std::map<std::string, SharTexture>;
using MapDivTexture = std::map<std::string, std::vector<SharTexture>>;

class TextureFactory
{
public:
	SharTexture GetTexture(std::string FileName);
private:
	MapTexture TextureContainer_;		// 単体読み込み用変数
	SharTexture CreateTexture(std::string FileName);						// 画像作成

};

