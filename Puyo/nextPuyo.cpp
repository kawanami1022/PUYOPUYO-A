#include "../stage.h"
#include "nextPuyo.h"

nextPuyo::nextPuyo(Vector2 pos, PUYO_TYPE puyoType, int GrHandle):Puyo(std::move(pos))
{
	puyoType_ = puyoType;
	GrHandle_ = GrHandle;
}
