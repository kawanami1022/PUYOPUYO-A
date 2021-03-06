#pragma once
#include <string>
#include <memory>
#include <map>
#include "Texture.h"
using SharTexture = std::shared_ptr<Texture>;
using MapTexture = std::map<std::string, SharTexture>;

class TextureFactory
{
public:
	SharTexture GetTexture(std::string FileName);
private:
	MapTexture TextureContainer_;
	SharTexture CreateTexture(std::string FileName);
	
};

