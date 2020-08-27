#pragma once
#include <memory>
#include <array>
#include <map>
#include <vector>
#include "InputID.h"
#include "CommonInputID.h"
#define STCI static_cast<int>

enum class Trg
{
	Now,
	Old,
	Max
};



//入力装置の種類
enum class ContType
{
	AI,
	Key,
	Mouse,
	Pad,
	Max
};

struct controller;
enum class STG_MODE;
enum class PUYO_TYPE;
class Stage;
class Puyo;
class nextPuyo;
class ObsPuyo;
using SharCntr = std::shared_ptr<controller>;
using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;


struct controller
{
	void operator()()
	{
		Update();
	}

	const CntData& GetCntData(void)
	{
		return _data;
	}

	virtual ContType GetType(void) = 0;
	virtual bool Setup(int no) = 0;	// プレーヤーのnumber
	virtual bool push(InputID) = 0;
	virtual bool release(InputID) = 0;
	virtual bool Hold(InputID) = 0;
	virtual bool separate(InputID)=0;
	virtual void DebugDrow(int id) = 0;
	virtual void changeInputTbl(int, InputID)=0;
	virtual void PadForceFeedback(int, int)=0;
	void ResetJoyPadNum();
	void AutoChangeInput(SharCntr&,int);
	void SetStgData(std::vector<PUYO_TYPE>, std::vector<std::shared_ptr<Puyo>>, std::pair<PUYO_TYPE, PUYO_TYPE>);
	void SetStgType(STG_MODE);
protected:
	CntData _data;
	static int joyPadNum_;

	int frame_;
	int id_;
	int gridCountX_;
	int gridCountY_;

	std::pair<PUYO_TYPE, PUYO_TYPE> CntlPuyoType_;		// 操作中のぷよ
	std::vector<PUYO_TYPE> stgDataBase_;	// 
	std::vector<PUYO_TYPE*> stgData_;		// _dataBaseの一次元配列の先頭アドレスを確保
	bool SetStgDataFlag_;					// ステージデータをset確認用変数
	std::vector < std::shared_ptr<Puyo>> nextPuyo_;
	std::map<InputID, std::pair<int, int>> InputStateContainer_;
private:
	virtual void Update(void) = 0;

};




