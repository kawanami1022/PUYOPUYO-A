#include <DxLib.h>
#include "UI.h"


UI::UI(int frame, int GrHdl):frame_(frame), txHdl_(GrHdl)
{
}

void UI::DrawUI(Positoin2 Center)
{
	DrawExtendGraph(Center.x - txHdl_.GetSize().x / 2, Center.y - txHdl_.GetSize().y / 2,
		Center.x + txHdl_.GetSize().x / 2, Center.y + txHdl_.GetSize().y / 2, txHdl_.GetHandle(), true);

}

void UI::DrawUIReductionWidth(Positoin2 Center)
{
	DrawExtendGraph(frame_+Center.x - txHdl_.GetSize().x / 2, Center.y - txHdl_.GetSize().y / 2,
		Center.x + txHdl_.GetSize().x / 2- frame_, Center.y + txHdl_.GetSize().y / 2, txHdl_.GetHandle(), true);
}


