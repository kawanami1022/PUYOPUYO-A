#include <DxLib.h>
#include "Texture.h"

Texture::Texture(int GrHandle)
{
	GrHandle_ = GrHandle;
	GetGraphSize(GrHandle_, &size_.x, &size_.y);
}

Vector2 Texture::GetSize()
{
	return size_;
}

int Texture::GetHandle()
{
	return GrHandle_;
}
