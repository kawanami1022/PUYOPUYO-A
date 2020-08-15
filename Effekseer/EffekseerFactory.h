#pragma once
#include <memory>
#include <map>
#include <string>
#include "Effect.h"


class Effect;
using SharInt = std::shared_ptr<int>;
using SharEfk = std::shared_ptr<Effect>;

class EffekseerFactory
{
public:
	SharEfk GetEfkHandle(std::string, float mag);
	void EraseEfkHandle(std::string);
private:
	std::map<std::string, SharEfk> EfkContainer_;
	SharEfk CreateEfkHandle(std::string, float mag);
};

