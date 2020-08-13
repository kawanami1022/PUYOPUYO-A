#pragma once
#include <memory>
#include <map>
#include <array>
#include "CommonInputID.h"
#include "controller.h"

// 共通キー入力

struct ComInput 
{
	void operator()()
	{
		Update();
	}

	bool Setup();	// プレーヤーのnumber

	bool push(ComInputID);
	bool Hold(ComInputID);
	bool release(ComInputID);
	bool separate(ComInputID);
private:
	ComData comData_;
	std::array<char, 256> _ComkeyData;
	std::map<ComInputID, int> _ComInputTbl;
	void Update(void);
};

