#pragma once
#include "../Vector2.h"
#include "../Texture/TextureFactory.h"
#include "../Texture/Texture.h"
enum class BLOCK_COLOR {
    BLOWN,
    BLUE,
    GREEN,
    PAPLE,
    RED,
    MAX
};
struct BLOCK
{
    BLOCK(Positoin2, Vector2, int);
	Positoin2 pos_;
	Vector2 Size_;
	int GrHdl_;
};