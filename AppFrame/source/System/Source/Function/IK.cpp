//----------------------------------------------------------------------
// @filename IK.cpp
// @author: Kawai Daisuke
// @explanation
// 逆運動学を用いたIKの計算を行うクラス
//----------------------------------------------------------------------
#include "../../Header/Function/IK.h"
#include "../../Header/Math/Vector3D.h"
#include "../../Header/Collision/3DCollision.h"

//----------------------------------------------------------------------
// @brief 1ボーンIK
// @param targetPos 目標位置
// @param bonePos ボーンの位置
// @param boneDir ボーンの向き
// ----------------------------------------------------------------------
void IK::OneBoneIK(Vector3D targetPos, Vector3D& bonePos, Vector3D& boneDir) {

    // ①IKの目標位置をローカルに変換
    Vector3D localTargetPos = targetPos - bonePos;
    // 正規化して方向ベクトルにする
    Vector3D localTargetDir = localTargetPos.Normalize();

    // sq = squaredの略で、2乗を表す
    float sqX = localTargetPos.x * localTargetPos.x;
    float sqY = localTargetPos.y * localTargetPos.y;
    float sqZ = localTargetPos.z * localTargetPos.z;

    // 三平方の定理でベクトルの長さを求める
    float length = sqrtf(sqX + sqY + sqZ);


    // ②ローカル座標から三角比を用いてsinΘz, cosΘz, sinΘy, cosΘyを計算
    // 2.1 ヨー角を計算する
    // DxLibはY-upなのでsinΘy, cosΘyを計算する(Z-upだとsinΘz, cosΘzになる)
    float cosTY = localTargetPos.x / sqrtf(sqX + sqZ);
    float sinTY = localTargetPos.z / sqrtf(sqX + sqZ);

    // 2.2 ピッチ角を計算する
    // sinΘx, cosΘxを計算する
    float cosTZ = sqrtf(sqX + sqZ) / length;
    float sinTZ = localTargetPos.y / length;


    // ③ボーンの向きを求める
    // 3.1 ヨー軸の回転行列を作る
    // グローバルのY軸（上方向）
    Vector3D yawAxis = VGet(0.0f, 1.0f, 0.0f);
    if (localTargetDir.x == 0.0f && localTargetDir.z == 0.0f) {
        yawAxis = VGet(1.0f, 0.0f, 0.0f); // 特殊ケース: 目標がY軸に沿っている場合、X軸を回転軸にする
    }
    MATRIX rotationYaw = MGetRotAxis(yawAxis.toVECTOR(), atan2f(sinTY, cosTY));

    // 3.2 ピッチ軸の回転行列を作る
    // グローバルのX軸（右方向）
    Vector3D pitchAxis = VGet(1.0f, 0.0f, 0.0f);
    MATRIX rotationPitch = MGetRotAxis(pitchAxis.toVECTOR(), atan2f(sinTZ, cosTZ));

    // ボーンの方向を更新
    // ここ必ずヨー→ピッチの順番で掛ける
    boneDir = VTransform(boneDir.toVECTOR(), rotationYaw);
    boneDir = VTransform(boneDir.toVECTOR(), rotationPitch);
}

//----------------------------------------------------------------------
// @brief 2ボーンIK
// @param targetPos 目標位置
// @param joint1Pos 第一関節の位置
// @param joint1Dir 第一関節の向き
// @param joint2Pos 第二関節の位置
// @param joint2Dir 第二関節の向き
// @param bone1Length 第一ボーンの長さ
// @param bone2Length 第二ボーンの長さ
// ----------------------------------------------------------------------
void IK::TwoBoneIK(Vector3D targetPos, Vector3D& joint1Pos, Vector3D& joint1Dir,
    Vector3D& joint2Pos, Vector3D& joint2Dir, float bone1Length, float bone2Length) {

    Vector3D Line = targetPos - joint1Pos;
    float LineLength = Line.Len();

    // ①1ボーンIKを使って第一関節を目標位置に向ける
    OneBoneIK(targetPos, joint1Pos, joint1Dir);

    // ②第一関節の進行方向を基準として第二関節の回転軸を法線とする平面を作る
    Vector3D planeNormal = joint1Dir.Cross(targetPos - joint1Pos);
    planeNormal = planeNormal.Normalize(); // 法線の正規化

    // ここからは第一関節も第二関節も上の法線を軸とした１軸回転をするため、２次元の問題として扱う
    // ③第二関節の先端が目標位置に向くように二本の関節を回転させて、三角形を作る  
    // 3.1三角形の各辺は、それぞれbone1Length, bone2Length, Lineの長さを持つので
    // 辺aをbone1Length、辺bをbone2Length、辺cをLineとして余弦定理を使ってcosB,Cを求める
    float sqA = bone1Length * bone1Length;
    float sqB = bone2Length * bone2Length;
    float sqC = LineLength * LineLength;

    float cosB = (sqA + sqC - sqB) / (2 * bone1Length * LineLength);
    Collision3D::clamp1m1(cosB); // -1～1の範囲にクランプ
    float sinB = sqrtf(1 - cosB * cosB);

    float cosC = (sqA + sqB - sqC) / (2 * bone1Length * bone2Length);
    Collision3D::clamp1m1(cosC); // -1～1の範囲にクランプ
    float sinC = sqrtf(1 - cosC * cosC);

    // 3.3回転方向について考える前に、第2関節の回転角が余弦定理で求めた三角形abcの内角Cではなく、
    // 実際には外角のπ-Cとなっている点について考慮しなければなりません。
    // といっても、ここは以下の公式にしたがってcosCの符号を反転するだけで構いません。sinCの値はそのままです。
    cosC = -cosC; // 外角補正

    // ④回転方向からsinにつく符号を決める
    // 回転方向が反時計回りの場合は正方向の回転で、時計回りの場合は負方向の回転となる。
    // 回転方向の正負はsinθの正負だけで表現できるので、cosの符号は変化しない。
    // ここで、sinθの正負は外積を使って求めることができる。
    // ここで、外積の結果が正の場合はsinθが正、負の場合はsinθが負となる。
    if (joint1Dir.Cross(targetPos - joint1Pos).Len() < 0) {
        sinB = -sinB;
    }

    // ⑤得られたcos, sinの組み合わせで、各関節を回転させる
    // joint1の新しい方向ベクトルを計算
    MATRIX rotationB = MGetRotAxis(planeNormal.toVECTOR(), atan2f(sinB, cosB));
    joint1Dir = VTransform(joint1Dir.toVECTOR(), rotationB);
    joint1Dir = joint1Dir.Normalize(); // 正規化

    // joint2の位置を計算
    joint2Pos = joint1Pos + joint1Dir * bone1Length;
    // joint2の新しい方向ベクトルを計算
    MATRIX rotationC = MGetRotAxis(planeNormal.toVECTOR(), atan2f(sinC, cosC));
    joint2Dir = VTransform(joint1Dir.toVECTOR(), rotationC);
    joint2Dir = joint2Dir.Normalize(); // 正規化
}