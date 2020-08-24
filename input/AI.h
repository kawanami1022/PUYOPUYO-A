#pragma once
#include "controller.h"
struct AI :public controller
{
	ContType GetType(void)override;
	bool Setup(int no)override;	// ƒvƒŒ[ƒ„[‚Ìnumber
	bool push(InputID)override;
	bool release(InputID)override;
	bool Hold(InputID)override;
	bool separate(InputID)override;
	void DebugDrow(int id)override;
	void changeInputTbl(int, InputID)override;
	void PadForceFeedback(int, int)override;
};

