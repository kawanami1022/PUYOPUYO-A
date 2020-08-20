#pragma once
#include "../Vector2.h"
#include "controller.h"
#include "InputID.h"

class mouse :
	public controller
{
public:
	void Update() override;
	bool Setup(int no) override;
	ContType GetType(void) override;
	bool Hold(InputID)override;
	bool push(InputID)override;
	bool release(InputID)override;
	bool separate(InputID)override;
	void DebugDrow(int id)override;
	Vector2 getMousePos();
	InputID GetInputID();
	int GetMouseWheelFlag(InputID inputID);
protected:
	std::map<InputID, int> _mouseInputTbl;
private:
	Vector2 pos;
	int mouseWheel_;
};

