#pragma once
#include "../Vector2.h"
#include "../Texture/TextureFactory.h"
#include "../Texture/Texture.h"
class Score
{
public:
	Score(SharTexture txHdl_, Positoin2 pos,int id);
	void Draw();
private:
	Positoin2 pos_;
	int score_;
	SharTexture txHdl_;
	int id_;
};

