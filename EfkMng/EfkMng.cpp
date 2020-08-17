#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <mutex>
#include "EfkMng.h"

EfkMng* EfkMng::hInstance=nullptr;

EfkMng& EfkMng::GetInstance()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
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
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	
	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(800, 600);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);
}

EfkMng::~EfkMng()
{


	// Effekseer���I������B
	Effkseer_End();
}
