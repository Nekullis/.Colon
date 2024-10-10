//----------------------------------------------------------------------
// @filename Fps.h
// @author: Saito Ko
// @explanation
// Fps���v�Z�E���䂷��N���X
//----------------------------------------------------------------------
#include "DxLib.h"
#include "../../Header/Function/Fps.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
Fps::Fps()
{
    fps_count = 0;
    count0t = 0;
    for (int i = 0; i < FLAME; i++)
    {
        f[i] = 0;
    }
    ave = 0;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Fps::~Fps()
{

}

//----------------------------------------------------------------------
// @brief fps���v�Z�E����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Fps::WaitFps() {
    int term, i, gnt;
    static int t = 0;
    if (fps_count == 0) {//60�t���[����1��ڂȂ�
        if (t == 0)//���S�ɍŏ��Ȃ�܂��Ȃ�
            term = 0;
        else//�O��L�^�������Ԃ����Ɍv�Z
            term = count0t + 1000 - GetNowCount();
    }
    else    //�҂ׂ�����=���݂���ׂ�����-���݂̎���
        term = (int)(count0t + fps_count * (1000.0 / FLAME)) - GetNowCount();

    if (term > 0)//�҂ׂ����Ԃ����҂�
        Sleep(term);

    gnt = GetNowCount();

    if (fps_count == 0)//60�t���[����1�x������
        count0t = gnt;
    f[fps_count] = gnt - t;//�P���������Ԃ��L�^
    t = gnt;
    //���όv�Z
    if (fps_count == FLAME - 1) {
        ave = 0;
        for (i = 0; i < FLAME; i++)
            ave += f[i];
        ave /= FLAME;
    }
    fps_count = (++fps_count) % FLAME;

    return true;
}

//----------------------------------------------------------------------
// @brief fps��`�悷��
// @param x x���W
// @param y y���W
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Fps::DrawFps(int x, int y) {
    if (ave != 0) {
        DrawBox(0, 0, 120, 20, GetColor(128, 128, 128), true);
        DrawFormatString(x, y, GetColor(255, 255, 255), "fps:%lf\n", 1000 / ave); //double�^��%lf
    }
    return true;
}