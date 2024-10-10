/*
** WinMain
*/

//
// include ��
//

#include "../appframe.h"
#include "Global.h"

//
// WinMain(). �v���O�����N���֐�
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		// �v���O�����I�������������[�N�����o����

	SetBackgroundColor(0,0,0);

	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		appBase->Input();

		appBase->Process();

		ClearDrawScreen();		// ��ʂ�����������
		appBase->Render();
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f������

		if (global.GetExit()) {
			break;
		}

	}

	appBase->Terminate();

	return 0;
}
