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
	MAX,
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
	std::vector<PUYO_TYPE*> stgData_;		// _dataBase�̈ꎟ���z��̐擪�A�h���X���m��
	std::vector<PUYO_TYPE> eraseDataBase_;	// �����p�f�[�^
	std::vector<PUYO_TYPE*> eraseData_;		// �����p�f�[�^
	std::vector<Vector2>	ErPyDelPos_;

	std::map<STG_MODE, std::function<void(Stage* stage)>> StgModeFunc;
	std::map<InputID, std::function<void(Stage* stage)>> StgInputFunc;
	std::function<void(Vector2&&,Vector2&&)> chPuyo_;
	std::list<ObsPuyo> obsPuyo_;

	int frame;
	InputID inputId_;
	static int stageCount_;
	int id_;
	int color_;
	Vector2 offset_;
	Vector2 size_;
	Vector2 nextBoxPos;
	std::array<Vector2,2> GuidePyPos_;	//�K�C�h�pPuyo���W

	// ����������
	bool Init(Vector2&);
	bool efkInit();			// �G�t�F�N�g

	int _checkGridCount;
	int SetChainCount_;
	int GetChainCount_;
	int ObsDropCnt_;

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
	friend struct Effect;
protected:

public:
	Vector2 _pos;

	void input();
	int update();
	void draw();
	void makePuyo();
	void setNextPuyo();
	void SetStageData();
	void SetPuyoData();
	bool setPermition(Vector2 tmp, int ID);
	bool chErasePuyo(Vector2&& GridPos, Vector2&& chGridPos);
	bool ErasePuyo(Vector2&& GridPos);			// ������Ղ悪����	true ���݂��Ȃ� false
	void SetChainCount(int SetChainCount);

	void SetPuyoGuide();

	// ���͏����n�̊֐�
	void ChangeInputMode(ComInputID);
	Vector2 getChipPos();
	bool DeletePuyo();
	std::vector<PUYO_TYPE*> GetErasePos();
	Stage(Vector2&& offset, Vector2&& size);
	~Stage();
	friend class PlayUnit;
	TextureFactory textureFactory;
	std::vector<int> GrHandle_;

	// �G�t�F�N�g
	std::vector<SharEfk> EffectHandle_;
	std::list<SharInt> playEfkHandle_;
	EffekseerFactory efkFac_;

};

