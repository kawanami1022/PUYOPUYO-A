#pragma once
#include "../Vector2.h"
#include "../Texture/Texture.h"

class UI
{
public:
	UI();
	UI(int, int);
	int frame_;
	void DrawUI(Positoin2 Center);
	void DrawUIReductionWidth(Positoin2 Center);		// �k���`��
private:
	Texture txHdl_;
};

