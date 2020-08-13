#pragma once
#include <type_traits>
enum class ComInputID
{
	PG_UP,
	PG_DOWN,
	Max
};

static ComInputID begin(ComInputID) {return ComInputID::PG_UP; };
static ComInputID end(ComInputID) {return ComInputID::Max; };
static ComInputID operator++(ComInputID& state) 
{ return state = ComInputID(std::underlying_type<ComInputID>::type(state) + 1);};
static ComInputID operator*(ComInputID state) { return state; };