#include <DxLib.h>
#include "Texture.h"

Texture::Texture(std::string FileName)
{
	GrHandle = LoadGraph(FileName.data());
	GetGraphSize(GrHandle, &size_.x, &size_.y);
}

Vector2 Texture::GetSize() const
{
	return size_;
}

int Texture::GetHandle() const
{
	return GrHandle;
}
