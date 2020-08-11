#include <DxLib.h>
#include "DxLib_Draw.h"

void DxLib_Draw::DrawBoxEOff(int x, int y, int offset_x, int offset_y,int color, bool FillFlag)
{
	DrawBox(x, y, x + offset_x, y + offset_y,color, FillFlag);
}

void DxLib_Draw::DrawBoxLineEOff(int x, int y, int offset_x, int offset_y, int color)
{
	DrawLineBox(x, y, x + offset_x, y + offset_y, color);
}

void DxLib_Draw::DrawExtendGraphCe(int posX, int posY, int size_x, int size_y, int GrHandle)
{
	DrawExtendGraph(posX - size_x / 2, posY - size_y / 2, posX + size_x / 2, posY + size_y / 2, GrHandle, true);
}

