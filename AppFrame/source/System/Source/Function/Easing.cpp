//----------------------------------------------------------------------
// @filename Easing.cpp
// @author: Saito Ko
// @explanation
// �C�[�W���O�֐����܂Ƃ߂��N���X
//----------------------------------------------------------------------
#include "../../Header/Function/Easing.h"
#include "../../Header/Math/mymath.h"

//----------------------------------------------------------------------
// @brief �C�[�W���O�E���j�A
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::Linear(float cnt, float start, float end, float frames) {
    return (end - start) * cnt / frames + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���N���b�h
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�N���b�h
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * cnt * (cnt - 2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�N���b�h
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return (end - start) / 2.0f * cnt * cnt + start;
    }
    cnt--;
    return -(end - start) / 2.0f * (cnt * (cnt - 2) - 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���N���[�r�b�N
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�N���[�r�b�N
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt + 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�N���[�r�b�N
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return (end - start) / 2.0f * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0f * (cnt * cnt * cnt + 2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���N�H�[�g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�N�H�[�g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�N�H�[�g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return (end - start) / 2.0f * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return -(end - start) / 2.0f * (cnt * cnt * cnt * cnt - 2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���N�B���g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�N�B���g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�N�B���g
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return (end - start) / 2.0f * cnt * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0f * (cnt * cnt * cnt * cnt * cnt + 2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���T�C��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InSine(float cnt, float start, float end, float frames) {
    return -(end - start) * cosf(cnt / frames * (PIOver2)) + end + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�T�C��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutSine(float cnt, float start, float end, float frames) {
    return (end - start) * sinf(cnt / frames * PIOver2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�T�C��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutSine(float cnt, float start, float end, float frames) {
    return -(end - start) / 2.0f * (cosf(PI * cnt / frames) - 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���G�N�X�|
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InExpo(float cnt, float start, float end, float frames) {
    return (end - start) * powf(2.0f, 10 * (cnt / frames - 1)) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�G�N�X�|
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutExpo(float cnt, float start, float end, float frames) {
    return (end - start) * (-powf(2.0f, -10 * cnt / frames) + 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�G�N�X�|
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutExpo(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return (end - start) / 2.0f * powf(2.0f, 10 * (cnt - 1)) + start;
    }
    cnt--;
    return (end - start) / 2.0f * (-powf(2.0f, -10 * cnt) + 2) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���T�[�N��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * (sqrtf(1 - cnt * cnt) - 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�T�[�N��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * sqrtf(1 - cnt * cnt) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�C���A�E�g�T�[�N��
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::InOutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0f;
    if(cnt < 1) {
        return -(end - start) / 2.0f * (sqrtf(1 - cnt * cnt) - 1) + start;
    }
    cnt -= 2;
    return (end - start) / 2.0f * (sqrtf(1 - cnt * cnt) + 1) + start;
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�E�A�E�g�G���X�e�B�b�N
// @param cnt ���݂̃t���[��
// @param start �J�n�l
// @param end �I���l
// @param frames �t���[����
// @return �w�肵�����Ԃ̒l
//----------------------------------------------------------------------
float Easing::OutElastic(float cnt, float start, float end, float frames)
{
    if (cnt == 0) {
        return start;
    }
    else if (cnt == frames) {
        return end;
    }
    else {
        float time = cnt / frames;
        float rad = (2.0f * PI) / 3.0f;
        float rate = powf(2, -10 * time) * sinf((time * 10 - 0.75f) * rad) + 1;

        return  start + (end - start) * rate;
    }
}

//----------------------------------------------------------------------
// @brief �C�[�W���O�֐����Ăяo��
// @param value �l
// @param nowTime ���݂̎���
// @param start �J�n�l
// @param end �I���l
// @param maxTime �ő厞��
// @param easing �C�[�W���O�֐�
// @return ����
//----------------------------------------------------------------------
void Easing::CallingFunction(float* value, float nowTime, float start, float end, float maxTime,float (*easing)(float, float, float, float) ){
    if (nowTime > 0) {
        if (nowTime > maxTime) {
            nowTime = maxTime;
        }
        (*value) = easing(nowTime, start, end, maxTime);
    }
};