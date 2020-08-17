#pragma once
#include <array>
#include <map>
#include "InputID.h"
#include "CommonInputID.h"
#define STCI static_cast<int>

enum class Trg
{
	Now,
	Old,
	Max
};



//入力装置の種類
enum class ContType
{
	Key,
	Mouse,
	Pad,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;


struct controller
{
	void operator()()
	{
		Update();
	}

	const CntData& GetCntData(void)
	{
		return _data;
	}

	virtual ContType GetType(void) = 0;
	virtual bool Setup(int no) = 0;	// プレーヤーのnumber
	virtual bool push(InputID) = 0;
	virtual bool release(InputID) = 0;
	virtual bool Hold(InputID) = 0;
	virtual bool separate(InputID)=0;
	virtual void DebugDrow(int id) = 0;
protected:
	CntData _data;

private:
	virtual void Update(void) = 0;


};




