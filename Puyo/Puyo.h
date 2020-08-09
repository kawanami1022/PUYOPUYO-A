#pragma once
#include <memory>
#include <functional>
#include <map>
#include "../input/InputID.h"
#include "../Vector2.h"
#include "../Stage.h"

struct BitField
{
	unsigned int u : 1;
	unsigned int r : 1;
	unsigned int d : 1;
	unsigned int l : 1;
};

union DirPermit
{
	BitField perBit;
	unsigned int flag;
};

enum class PUYO_TYPE
{
	NON,			// 
	R,			// ê‘
	G,			// óŒ
	B,			// ê¬
	Y,			// â©êF
	P,			// éá
	OBS,			// Ç®é◊ñÇ
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



class Puyo
{
public:
	Puyo(Vector2&& Pos);
	Puyo(Vector2& stagePos, Vector2 GridPos);
	Puyo(Vector2& stagePos, Vector2 GridPos, PUYO_TYPE puyoType,int GrHandle);
	~Puyo();
	void update();
	void draw();
	void Down(InputID id);
	Vector2 GetGridPos();
	PUYO_TYPE GetPuyoType();
	bool GetAlive();
	void SetAlive(bool aliveFlag);
	void setBlockSize(int size);
	bool drop();
	bool DeletePuyo();
	void SetMatchGrid(Vector2&& Pos);
protected:
	PUYO_TYPE puyoType_;
	PUYO_STATE puyoState;
private:
	Vector2 pos_;
	Vector2 ROffPos_;

	Vector2 offsetPos_;
	DirPermit dirPer_;		// 0:à⁄ìÆãñâ¬ 1:à⁄ìÆã÷é~
	DirPermit munyonBox_;		// 0:ï`âÊÇµÇ»Ç¢ 1:ãÈå`ï`âÊ
	bool alive_;
	Vector2 radious;
	int blockSize;
	std::map< PUYO_STATE, std::function<void(PUYO_STATE)>> move;
	std::map< PUYO_STATE, std::function<void()>> drawID;
	bool Init(Vector2& fieldPos, Vector2& GridPos);
	int speed;
	int GrHandle_;
	friend class Stage;

	friend struct IpLeft;
	friend struct IpUp;
	friend struct IpDown;
	friend struct IpRight;
	friend struct IpTurnL;
	friend struct IpTurnR;

	friend struct GENERATES;
	friend struct FALL;
	friend struct PUYON;
	friend struct MUNYOUN;
	friend struct ERASE;
	friend struct DROP;
};

