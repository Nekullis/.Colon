
#pragma once	
#include <math.h>
#define	 PI (3.1415926f)
#define TwoPI   (PI * 2.0f)
#define PIOver2 (PI / 2.0f)
// �l�X�ȃC�[�W���O
// https://game-ui.net/?p=835 ���Q�l��
class Easing 
{
public:
static float Linear(float cnt, float start, float end, float frames);
static float InQuad(float cnt, float start, float end, float frames);
static float OutQuad(float cnt, float start, float end, float frames);
static float InOutQuad(float cnt, float start, float end, float frames);
static float InCubic(float cnt, float start, float end, float frames);
static float OutCubic(float cnt, float start, float end, float frames);
static float InOutCubic(float cnt, float start, float end, float frames);
static float InQuart(float cnt, float start, float end, float frames);
static float OutQuart(float cnt, float start, float end, float frames);
static float InOutQuart(float cnt, float start, float end, float frames);
static float InQuint(float cnt, float start, float end, float frames);
static float OutQuint(float cnt, float start, float end, float frames);
static float InOutQuint(float cnt, float start, float end, float frames);
static float InSine(float cnt, float start, float end, float frames);
static float OutSine(float cnt, float start, float end, float frames);
static float InOutSine(float cnt, float start, float end, float frames);
static float InExpo(float cnt, float start, float end, float frames);
static float OutExpo(float cnt, float start, float end, float frames);
static float InOutExpo(float cnt, float start, float end, float frames);
static float InCirc(float cnt, float start, float end, float frames);
static float OutCirc(float cnt, float start, float end, float frames);
static float InOutCirc(float cnt, float start, float end, float frames);

static float  OutElastic(float cnt, float start, float end, float frames);

static void CallingFunction(float* value, float nowTime, float start, float end, float maxTime,float (*easing)(float, float, float, float) );
};
