#pragma once
#include <map>
#include <array>
#include <memory>
#include <DxLib.h>
#include "controller.h"
class Pad :public controller
{
public:
	ContType GetType(void)override;
	void Update()override;
	bool push(InputID)override;
	bool release(InputID)override;
	bool Hold(InputID)override;
	bool separate(InputID)override;
	bool Setup(int)override;
	void DebugDrow(int id)override;
protected:
	std::array<XINPUT_STATE, 1> _xInputData;
	std::map<InputID, int> _xInputTbl;
	
private:
};

