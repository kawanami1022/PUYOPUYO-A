#pragma once
#define lpEfkMng EfkMng::GetInstance()

class EfkMng
{

public:
	static void Create();
	static EfkMng& GetInstance();
	static void Destroy();
	static EfkMng* hInstance;
private:
	EfkMng();
	~EfkMng();
};

