 #pragma once
#include <array>
#include <list>
#include <memory>
#include <vector>
#include <functional>
#include "Vector2.h"
#include "Effekseer/EffekseerFactory.h"
#include "Effekseer/Effect.h"
#include "input/ComInput.h"
#include "input/CommonInputID.h"
#include "input/controller.h"
#include "Puyo/ObsPuyo.h"
#include "Texture/TextureFactory.h"
#include "Texture/Texture.h"
#define STGPUYO(id) stage->puyo_[id]
#define PUYO_DELETE_NUM	4

enum class STG_MODE
{
	GENERATES,
	PUYON,
	MUNYON,
	DROP,
	FALL,
	ERASE,
	EFFECT,
	MAX,
};


enum class STG_TYPE
{
	PLAY,
	WIN,
	LOSE,
	MAX
};


class Puyo;

using sharPuyo = std::shared_ptr<Puyo>;


class Stage
{
private:
	const int screenSizeX;
	const int screenSizeY;
	const int blockSize;
	const int gridCountX;
	const int gridCountY;

	STG_MODE stgMode;
	std::vector<sharPuyo> puyo_;
	std::vector<sharPuyo> nextPuyo_;
	std::shared_ptr<controller> controller_;
	
	std::vector<PUYO_TYPE> stgDataBase_;	// 
	std::vector<PUYO_TYPE*> stgData_;		// _dataBaseの一次元配列の先頭アドレスを確保
	std::vector<PUYO_TYPE> eraseDataBase_;	// 消去用データ
	std::vector<PUYO_TYPE*> eraseData_;		// 消去用データ
	std::vector<Vector2>	ErPyDelPos_;
	std::vector<sharPuyo> ErPyDel_;		// 消去用

	std::map<STG_MODE, std::function<void(Stage* stage)>> StgModeFunc;
	std::map<InputID, std::function<void(Stage* stage)>> StgInputFunc;
	std::map<STG_TYPE, std::function<void(Stage& stage)>> StgDrawFunc;
	std::function<void(Vector2&&,Vector2&&)> chPuyo_;
	std::list<ObsPuyo> obsPuyoList_;
	std::vector<sharObsPuyo> obsPuyo_;
	STG_TYPE stgType_;			// ステージ状態
	int frame;
	InputID inputId_;
	static int stageCount_;
	int id_;
	int color_;
	Vector2 offset_;
	Vector2 size_;
	Vector2 nextBoxPos;
	std::array<Vector2,2> GuidePyPos_;	//ガイド用Puyo座標

	// 初期化処理
	bool Init(Vector2&);
	bool efkInit();			// エフェクト

	int _checkGridCount;
	int SetChainCount_;
	int GetChainCount_;

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
	friend struct EFFECT;
	
	friend struct DRAWPLAYING;
	friend struct DRAWWIN;
	friend struct DRAWLOSE;
protected:

public:
	Vector2 _pos;

	void input();
	int update(STG_TYPE);
	void draw();
	void makePuyo();
	void setNextPuyo();
	void SetStageData();
	void SetPuyoData();
	bool setPermition(Puyo& puyo);
	bool chErasePuyo(Vector2&& GridPos, Vector2&& chGridPos);
	bool ErasePuyo(Vector2&& GridPos);			// 消せるぷよが存在	true 存在しない false
	bool EraseObsPuyo();						// お邪魔ぷよ消去処理
	void SetChainCount(int SetChainCount);
	void SetPuyoGuide();


	void makeObsPuyoList();

	// 入力処理系の関数
	void ChangeInputMode(ComInputID);
	Vector2 getChipPos();
	STG_TYPE GetStgType();

	bool DeletePuyo();
	std::vector<PUYO_TYPE*> GetErasePos();
	Stage(Vector2&& offset, Vector2&& size);
	~Stage();
	friend class PlayUnit;
	TextureFactory textureFactory;
	std::vector<int> GrHandle_;
	std::vector<int> GmOvHdl_;

	// エフェクト
	std::vector<SharEfk> EffectHandle_;
	std::list<int> playEfkHandle_;
	EffekseerFactory efkFac_;

};

