#pragma once

#pragma comment(lib,"AppFrame.lib")

#include "DxLib.h"

#include "../MemoryLeak.h"

//Application
#include "Application/ApplicationBase.h"
#include "Application/UtilMacro.h"
#include "Application/Global.h"
#include "System/Header/Component/Component.h"
#include "System/Header/Component/Object/ObjectBase.h"

//CFile
#include "File/CFile/CFile.h"
#include "File/JsonFile/JsonFile.h"

//System
// Animation
#include "System/Header/Component/Animation/FrameData.h"
#include "System/Header/Component/Animation/MotionList.h"
#include "System/Header/Component/Animation/AnimationComponent.h"
//Collision
#include "System/Header/Collision/2DCollision.h"
#include "System/Header/Collision/3DCollision.h"
#include "System/Header/Collision/MyStructure.h"
//Convert
#include "System/Header/Convert/Convert.h"
//Draw
#include "System/Header/Draw/mydraw.h"
#include "System/Header/Draw/3DDraw.h"
#include "System/Header/Draw/DrawGauge.h"
//Effect
#include "System/Header/Effect/Afterglow.h"
#include "System/Header/Effect/AfterImage.h"
#include "System/Header/Effect/ScreenVibration.h"
//EventSystem
#include "System/Header/EventSystem/EventSystem.h"
// Input
#include "System/Header/Input/XInput.h"
#include "System/Header/Input/Mouse.h"
//Math
#include "System/Header/Math/mymath.h"
#include "System/Header/Math/Vector2D.h"
#include "System/Header/Math/Vector3D.h"
#include "System/Header/Math/Matrix3D.h"
#include "System/Header/Math/Spline.h"
#include "System/Header/Math/Quaternion.h"
//Sound
#include "System/Header/Sound/SoundItem.h"
#include "System/Header/Sound/SoundServer.h"
//Function
#include "System/Header/Function/Bone.h"
#include "System/Header/Function/Easing.h"
#include "System/Header/Function/Fps.h"
#include "System/Header/Function/IK.h"
#include "System/Header/Function/Vibration.h"
#include "System/Header/Function/Timer.h"
#include "System/Header/Function/TimeLimit.h"

//Component
#include "System/Header/Component/ComponentLib.h"
//Types
#include "System/Header/Types/DataTypes.h"

//Global
#include "Application/Global.h"
#include "System/Header/Resource/ResourceServer.h"