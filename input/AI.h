#pragma once
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include "controller.h"


struct AI :public controller
{
	void Update() override;
	ContType GetType(void)override;
	bool Setup(int no)override;	// ÉvÉåÅ[ÉÑÅ[ÇÃnumber
	bool push(InputID)override;
	bool release(InputID)override;
	bool Hold(InputID)override;
	bool separate(InputID)override;
	void DebugDrow(int id)override;
	void changeInputTbl(int, InputID)override;
	void PadForceFeedback(int, int)override;

private:


};

