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
#include "UI/UI.h"

#define STGPUYO(id) stage->puyo_[id]
#define PUYO_DELETE_NUM	4

const int RotaSpeed = 6;

enum class STG_MODE
{
	GENERATES,
	PUYON,
	MUNYON,
	DROP,
	FALL,
	ERASE,
	EFFECT,
	DROP_OBS,
	GENERATE_OBS,
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
	std::vector<PUYO_TYPE*> stgData_;		// _dataBase�̈ꎟ���z��̐擪�A�h���X���m��
	std::vector<PUYO_TYPE> eraseDataBase_;	// �����p�f�[�^
	std::vector<PUYO_TYPE*> eraseData_;		// �����p�f�[�^
	std::vector<Vector2>	ErPyDelPos_;
	std::vector<sharPuyo> ErPyDel_;		// �����p

	std::map<STG_MODE, std::function<void(Stage* stage)>> StgModeFunc;
	std::map<InputID, std::function<void(Stage* stage)>> StgInputFunc;
	std::map<STG_TYPE, std::function<void(Stage& stage)>> StgDrawFunc;
	std::function<void(Vector2&&,Vector2&&)> chPuyo_;
	std::list<ObsPuyo> obsPuyoList_;
	std::vector<sharObsPuyo> obsPuyo_;



	std::map<STG_TYPE, UI> StageUI_;		// �X�e�[�W��UI

	STG_TYPE stgType_;			// �X�e�[�W���
	int frame_;
	InputID inputId_;
	static int stageCount_;
	int id_;
	int color_;
	Vector2 offset_;
	Vector2 size_;
	Vector2 nextBoxPos;
	Positoin2 shackPos_;				// �h�炷���W
	std::array<Vector2,2> GuidePyPos_;	//�K�C�h�pPuyo���W
	// ����������
	bool Init(Vector2&);
	bool efkInit();			// �G�t�F�N�g
	bool ButtonInit();
	void controllerTypeDraw();

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
	friend struct GENERATES_OBS;
	friend struct DROP_OBS;

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
	bool ErasePuyo(Vector2&& GridPos);			// ������Ղ悪����	true ���݂��Ȃ� false
	bool EraseObsPuyo();						// ���ז��Ղ��������
	void SetChainCount(int SetChainCount);
	void SetPuyoGuide();

	void makeObsPuyoList();
	// ���͏����n�̊֐�
	void ChangeInputMode(ComInputID);

	//Getter
	Vector2 getChipPos();
	STG_TYPE GetStgType();
	Positoin2 GetGridPos(Positoin2);
	PUYO_TYPE GetStageData(Positoin2);


	bool DeletePuyo();
	std::vector<PUYO_TYPE*> GetErasePos();
	Stage(Vector2&& offset, Vector2&& size);
	~Stage();
	friend class PlayUnit;

	// �O���t�B�b�N�n���h��
	TextureFactory textureFactory;
	std::vector<int> GrHandle_;
	std::vector<int> GmOvHdl_;
	std::map<ContType, SharTexture> ContTypeTxHdl_;		// ���͗p�O���t�B�b�N�n���h��

	std::list<std::string> contNameList_;
	std::array<int, STCI(ContType::Max)> contHdl_;

	//std::list<std::string> InputKeyNmList_;				// ���͗p
	std::vector<int> InputHdl_;							// ���̓O���t�B�b�N�n���h��


	// �G�t�F�N�g
	std::vector<SharEfk> EffectHandle_;
	std::list<int> playEfkHandle_;
	EffekseerFactory efkFac_;

};

