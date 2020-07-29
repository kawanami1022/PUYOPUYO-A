#pragma once
#include "../stage.h"
#include "../Puyo.h"

struct GENERATES
{
	void operator()(Stage* stage) {
		stage->stgMode = STG_MODE::DROP;
		stage->makePuyo();
	}
};