#pragma once
#include <mutex>
#include <list>
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include "controller.h"
#include "../Vector2.h"
#include "../Puyo/PUYO_ID.h"

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
	void IdntSmColor();			// 同色のpuyoを識別する
	void SetInputPattern();		// 入力パターンを作成
	void ResetFrame();			// フレームをリセットする
private:

	std::list<InputID> InputPatten_;
	std::pair<Positoin2, Positoin2> PyLdPoint_;		// ぷよの着地点
};

