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
	mouse();
	~mouse();
	bool Hold(int);
	bool Push(int);
	bool Release(int);
	bool separate(int);
	Vector2 getMousePos();
protected:
	std::array<int, 3> _mouseInputData;
	std::map<InputID, int> _mouseInputTbl;
private:
	Vector2 pos;
};

