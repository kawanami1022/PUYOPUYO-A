#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include "Vector2.h"
#include "input/controller.h"
#include "input/keyInput.h"
#include "input/Pad.h"
#define STGPUYO(id) stage->puyo_[id]
#define PUYO_DELETE_NUM	4

enum class STG_MODE
{
	GENERATES,
	PUYON,
	DROP,
	FALL,
	ERASE,
	MAX,
};

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

#include "Puyo.h"



class Stage
{
private:
	const int blockSize;
	const int gridCountX;
	const int gridCountY;
	STG_MODE stgMode;
	std::vector<std::shared_ptr<Puyo>> puyo_;
	std::shared_ptr<controller> controller_;
	std::vector<PUYO_TYPE> stgDataBase_;	// 
	std::vector<PUYO_TYPE*> stgData_;		// _dataBase�̈ꎟ���z��̐擪�A�h���X���m��
	std::vector<PUYO_TYPE> eraseDataBase_;	// �����p�f�[�^
	std::vector<PUYO_TYPE*> eraseData_;		// �����p�f�[�^
	std::vector<Vector2>	ErPyDelPos_;
	std::map<STG_MODE, std::function<void(Stage* stage)>> StgModeFunc;
	std::map<InputID, std::function<void(Stage* stage)>> StgInputFunc;
	std::function<void(Vector2&&,Vector2&&)> chPuyo_;
	int frame;
	InputID inputId_;
	static int stageCount_;
	int id_;
	int color_;
	Vector2 offset_;
	Vector2 size_;
	bool Init(Vector2&);
	int _checkGridCount;

	friend struct IpLeft;
	friend struct IpUp;
	friend struct IpDown;
	friend struct IpRight;
	friend struct IpTurnL;
	friend struct IpTurnR;

	friend struct GENERATES;
	friend struct FALL;
	friend struct PUYON;
	friend struct ERASE;
	friend struct DROP;
protected:

public:
	Vector2 _pos;

	void input();
	void update();
	void draw();
	void makePuyo();
	void updtPuyoData();
	void SetStageData();
	void SetPuyoData();
	bool setPermition(Vector2 tmp, int ID);
	bool chErasePuyo(Vector2&& GridPos, Vector2&& chGridPos);
	bool ErasePuyo(Vector2&& GridPos);
	Vector2 getChipPos();
	bool DeletePuyo();
	std::vector<PUYO_TYPE*> GetErasePos();
	Stage(Vector2&& offset, Vector2&& size);
	~Stage();
	friend class PlayUnit;



};

