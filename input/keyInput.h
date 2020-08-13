#pragma once
#include <array>
#include "controller.h"

struct KeyInput:public controller
{
	ContType GetType(void)override;
	bool Setup(int no) override;	// ƒvƒŒ[ƒ„[‚Ìnumber
	void Update(void) override;
	bool push(InputID)override;
	bool Hold(InputID)override;
	bool release(InputID)override;
	bool separate(InputID)override;
	void DebugDrow(int id)override;
private:
	std::array<char, 256> _keyData;
	std::map<InputID, int> _InputTbl;
};