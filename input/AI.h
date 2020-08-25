#pragma once
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include "controller.h"

enum class PUYO_TYPE;
class Puyo;
class nextPuyo;
class ObsPuyo;
struct AI :public controller
{
	void Update() override;
	ContType GetType(void)override;
	bool Setup(int no)override;	// プレーヤーのnumber
	bool push(InputID)override;
	bool release(InputID)override;
	bool Hold(InputID)override;
	bool separate(InputID)override;
	void DebugDrow(int id)override;
	void changeInputTbl(int, InputID)override;
	void PadForceFeedback(int, int)override;
	void SetStgData(std::vector<PUYO_TYPE>, std::shared_ptr<Puyo>);	// stageData:ステージデータ
private:
	int gridCountX_;
	int gridCountY_;
	std::map<InputID,std::pair<int, int>> InputStateContainer_;
	std::vector<PUYO_TYPE> stgDataBase_;	// 
	std::vector<PUYO_TYPE*> stgData_;		// _dataBaseの一次元配列の先頭アドレスを確保
	std::shared_ptr<Puyo> nextPuyo_;
};

