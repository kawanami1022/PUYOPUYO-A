#include "stage.h"
#include "ObsPuyo.h"
#include "PyUpMode/GENERATES.h"

ObsPuyo::ObsPuyo(Vector2& fieldPos, Vector2 GridPos):Puyo(fieldPos, GridPos)
{
	DropCount = 3;
	puyoType_ =PUYO_TYPE::OBS;
}
