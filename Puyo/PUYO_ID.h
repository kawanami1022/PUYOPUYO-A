#pragma once
enum class PUYO_TYPE
{
	NON,			// 
	R,			// Ô
	G,			// —Î
	B,			// Â
	Y,			// ‰©F
	P,			// ‡
	OBS,			// ‚¨×–‚
	WALL,
	MAX,
};


enum class PUYO_STATE
{
	MOVE,
	STOP,
	DEAD,
	MAX,
};
