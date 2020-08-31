#pragma once
#include <memory>
#include "Puyo.h"
class ObsPuyo;
using sharObsPuyo = std::shared_ptr<ObsPuyo>;

class ObsPuyo :
	public Puyo
{
public:
	ObsPuyo(Vector2& fieldPos, Vector2 GridPos, int GrHandle);
private:
	int DropCount;
	friend struct GENERATES;
	friend struct GENERATES_OBS;
	friend struct DROP_OBS;
};

