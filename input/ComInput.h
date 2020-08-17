#pragma once
#include <memory>
#include <map>
#include <array>
#include "CommonInputID.h"
#include "controller.h"

// ���ʃL�[����
using ComData = std::map<ComInputID, TrgBool>;

struct ComInput 
{
	void operator()()
	{
		Update();
	}

	bool Setup();	// �v���[���[��number
	bool reset();	// �v���[���[��number

	bool push(ComInputID);
	bool Hold(ComInputID);
	bool release(ComInputID);
	bool separate(ComInputID);
	ComData GetComData();
	static ComData comData_;
private:
	std::array<char, 256> _ComkeyData;
	std::map<ComInputID, int> _ComInputTbl;
	void Update(void);
	int frame_;
};

