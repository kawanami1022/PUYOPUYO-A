#pragma once
#include <memory>
#include <map>
#include <array>
#include "CommonInputID.h"
#include "controller.h"

// ���ʃL�[����

struct ComInput 
{
	void operator()()
	{
		Update();
	}

	bool Setup();	// �v���[���[��number

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

