#pragma once
class Effect
{
private:
	int Handle_;		// ƒnƒ“ƒhƒ‹
	float Mag_;		// ”{—¦

public:
	Effect(int handle,float Mag)
	{
		Handle_ = handle;
		Mag_ = Mag;
	}
	int GetHandle()const
	{
		return Handle_;
	}
	float GetMag_()const
	{
		return Mag_;
	}
};

