#pragma once
#include <string>
#include "../Vector2.h"
class Texture
{

private:
	int GrHandle_;
	Vector2 size_;
public:
	Texture(int);
	// getter
	Vector2 GetSize();
	int GetHandle();
};

