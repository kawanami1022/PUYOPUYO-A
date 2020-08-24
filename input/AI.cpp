#include "AI.h"

ContType AI::GetType(void)
{
	return ContType();
}

bool AI::Setup(int no)
{
	InputStateContainer_ =
	{ {InputID::Up,std::make_pair(0,0)},
	{InputID::Down,std::make_pair(1,1)},
	{InputID::Left,std::make_pair(1,0)},
	{InputID::Right,std::make_pair(1,0)},
	{InputID::TURN_L,std::make_pair(1,0)},
	{InputID::TURN_R,std::make_pair(1,0)} };
	return false;
}

bool AI::push(InputID inputID)
{
	return false;
}

bool AI::release(InputID inputID)
{
	return false;
}

bool AI::Hold(InputID inputID)
{
	return false;
}

bool AI::separate(InputID inputID)
{
	return false;
}

void AI::DebugDrow(int id)
{
}

void AI::changeInputTbl(int, InputID)
{
}

void AI::PadForceFeedback(int, int)
{
}
