#pragma once
#include <string>
#include "../Vector2.h"
class Texture
{

private:
	int GrHandle;
	Vector2 size_;
public:
	Texture(std::string);
	// getter
	Vector2 GetSize()const;
	int GetHandle()const;
};

