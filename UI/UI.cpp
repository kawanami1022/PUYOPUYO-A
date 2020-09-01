#include <cmath>
#include <DxLib.h>
#include "UI.h"



UI::UI()
{
	frame_ = 0;
	txHdl_ = Texture(0);
}
UI::UI(int frame, int GrHdl):frame_(frame), txHdl_(GrHdl)
{
}

void UI::DrawUI(Positoin2 Center)
{
	DrawExtendGraph(Center.x - txHdl_.GetSize().x / 2, Center.y - txHdl_.GetSize().y / 2,
		Center.x + txHdl_.GetSize().x / 2, Center.y + txHdl_.GetSize().y / 2, txHdl_.GetHandle(), true);

}

void UI::DrawUIReductionWidth(Positoin2 Center, int speed)
{
	frame_++;
	int tmpWdh = abs((((frame_* speed) + txHdl_.GetSize().x / 2) % (txHdl_.GetSize().x * 2)) - txHdl_.GetSize().x);

	if (frame_*speed > txHdl_.GetSize().x*2)tmpWdh = 0;
	DrawExtendGraph(
		tmpWdh + Center.x - txHdl_.GetSize().x / 2, Center.y - txHdl_.GetSize().y / 2,
		Center.x + txHdl_.GetSize().x / 2 - tmpWdh, Center.y + txHdl_.GetSize().y / 2,
		txHdl_.GetHandle(),
		true);
}


