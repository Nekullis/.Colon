//----------------------------------------------------------------------
// @filename Easing.cpp
// @author: Saito Ko
// @explanation
// イージング関数をまとめたクラス
//----------------------------------------------------------------------
#include "../../Header/Function/Easing.h"
#include "../../Header/Math/mymath.h"

//----------------------------------------------------------------------
// @brief イージング・リニア
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::Linear(float cnt, float start, float end, float frames) {
    return (end - start) * cnt / frames + start;
}

//----------------------------------------------------------------------
// @brief イージング・インクワッド
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトクワッド
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * cnt * (cnt - 2) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトクワッド
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・インクュービック
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトクュービック
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt + 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトクュービック
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・インクォート
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトクォート
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトクォート
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・インクィント
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトクィント
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトクィント
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・インサイン
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InSine(float cnt, float start, float end, float frames) {
    return -(end - start) * cosf(cnt / frames * (PIOver2)) + end + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトサイン
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutSine(float cnt, float start, float end, float frames) {
    return (end - start) * sinf(cnt / frames * PIOver2) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトサイン
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InOutSine(float cnt, float start, float end, float frames) {
    return -(end - start) / 2.0f * (cosf(PI * cnt / frames) - 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インエクスポ
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InExpo(float cnt, float start, float end, float frames) {
    return (end - start) * powf(2.0f, 10 * (cnt / frames - 1)) + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトエクスポ
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutExpo(float cnt, float start, float end, float frames) {
    return (end - start) * (-powf(2.0f, -10 * cnt / frames) + 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトエクスポ
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・インサークル
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::InCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * (sqrtf(1 - cnt * cnt) - 1) + start;
}

//----------------------------------------------------------------------
// @brief イージング・アウトサークル
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
//----------------------------------------------------------------------
float Easing::OutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * sqrtf(1 - cnt * cnt) + start;
}

//----------------------------------------------------------------------
// @brief イージング・インアウトサークル
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング・アウトエラスティック
// @param cnt 現在のフレーム
// @param start 開始値
// @param end 終了値
// @param frames フレーム数
// @return 指定した時間の値
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
// @brief イージング関数を呼び出す
// @param value 値
// @param nowTime 現在の時間
// @param start 開始値
// @param end 終了値
// @param maxTime 最大時間
// @param easing イージング関数
// @return 無し
//----------------------------------------------------------------------
void Easing::CallingFunction(float* value, float nowTime, float start, float end, float maxTime,float (*easing)(float, float, float, float) ){
    if (nowTime > 0) {
        if (nowTime > maxTime) {
            nowTime = maxTime;
        }
        (*value) = easing(nowTime, start, end, maxTime);
    }
};