#include "../stage.h"
#include "nextPuyo.h"

nextPuyo::nextPuyo(Vector2 pos, PUYO_TYPE puyoType):Puyo(std::move(pos))
{
	puyoType_ = puyoType;
}
