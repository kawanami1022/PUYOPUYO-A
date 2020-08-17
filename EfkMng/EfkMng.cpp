#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <mutex>
#include "EfkMng.h"

EfkMng* EfkMng::hInstance=nullptr;

EfkMng& EfkMng::GetInstance()
{
	// TODO: return ステートメントをここに挿入します
	static std::once_flag flag;
	std::call_once(flag, Create);
	return (*hInstance);
}

void EfkMng::Create()
{
	if (hInstance == nullptr)
	{
		hInstance = new EfkMng();
	}
}

void EfkMng::Destroy()
{
	delete hInstance;
	hInstance=nullptr;
}

EfkMng::EfkMng()
{
	Effekseer_Init(12000);
	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	
	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(800, 600);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);
}

EfkMng::~EfkMng()
{


	// Effekseerを終了する。
	Effkseer_End();
}
