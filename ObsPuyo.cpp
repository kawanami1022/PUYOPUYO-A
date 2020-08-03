#include "stage.h"
#include "ObsPuyo.h"

ObsPuyo::ObsPuyo(Vector2& fieldPos, Vector2 GridPos):Puyo(fieldPos, GridPos)
{
	puyoType =PUYO_TYPE::OBS;
}
