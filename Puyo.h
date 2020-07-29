#pragma once
#include <memory>
#include <functional>
#include <map>
#include "input/InputID.h"
#include "Vector2.h"
#include "Stage.h"
enum class PUYO_TYPE
{
	NON,			// 
	R,			// ê‘
	G,			// óŒ
	B,			// ê¬
	Y,			// â©êF
	P,			// éá
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

const int color[static_cast<int>(PUYO_TYPE::MAX)]={0,0xff0000,0x00ff33,0x0000ff,0xffff00,0x00ffff};


class Puyo
{
public:
	Puyo(Vector2& fieldPos, Vector2 GridPos);
	~Puyo();
	void update();
	void draw();
	void Move(InputID id);
	void Down(InputID id);
	Vector2 GetGridPos();
	PUYO_TYPE GetPuyoType();
	bool GetAlive();
	void SetAlive(bool aliveFlag);
	void setMovePer(DirPermit);
	void setBlockSize(int size);
	void drop();
	bool DeletePuyo();
	void SetMatchGrid(Vector2&& Pos);
	friend class Stage;

private:
	Vector2 pos_;
	Vector2 chipPos;
	Vector2 GridPos;
	PUYO_TYPE puyoType;
	PUYO_STATE puyoState;
	Vector2 offsetPos_;
	DirPermit dirPer_;
	bool alive_;
	int radious;
	int blockSize;
	std::map< PUYO_STATE, std::function<void(PUYO_STATE)>> move;
	std::map< PUYO_STATE, std::function<void()>> drawID;
	bool Init(Vector2& fieldPos, Vector2& GridPos);
	int speed;

};

