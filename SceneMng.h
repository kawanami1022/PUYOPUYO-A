#pragma once
#include <mutex>
#include <memory>
#include <vector>
#include "Vector2.h"
#define SCREEN_SIZE_X	800
#define SCREEN_SIZE_Y	600

#define lpSceneMng SceneMng::GetInstance()

class Stage;

class SceneMng
{
private:
	SceneMng();
	~SceneMng();
	void upDate();
	void draw();
	static SceneMng *hInstance;
	int SetChainCount_;
	Vector2 offset;
	Vector2 size;
	int handle;		// グラフィックハンドル
public:
	static SceneMng& GetInstance()
	{
		static std::once_flag once;
		std::call_once(once, Create);		// 1度だけ呼ぶ	
		return (*hInstance);
	}
	static void Create()
	{
		if (hInstance == nullptr)
		{
			hInstance = new SceneMng();
		}
	}
	static void Destroy()
	{
		delete hInstance;
		hInstance = nullptr;
	}
	int Run();
	std::vector<std::unique_ptr<Stage>> stage;

};

