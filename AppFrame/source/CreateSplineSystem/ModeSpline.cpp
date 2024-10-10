//----------------------------------------------------------------------
// @filename ModeSpline.h
// @author: Saito Ko
// @explanation
// �X�v���C���ł̋O���𐶐����t�@�C�����쐬���邽�߂̃N���X
//----------------------------------------------------------------------
#include "dxlib.h"
#include "../Header/ModeSpline.h"
#include "../AppFrame/source/System/Header/Function/Spline.h"
#include "../Header/Manager/SuperManager.h"

namespace {
	constexpr auto SELECTITEM_NUM = 8;
	constexpr auto TIME_TICK_X = 1480;
	constexpr auto TIME_TICK_WIDTH = 300;
	constexpr auto CAMERA_MOVE_SPEED = 50;
}

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param input XInput�N���X
// @param pos �J�����̏����ʒu
//----------------------------------------------------------------------
ModeSpline::ModeSpline(XInput* input,Vector3D pos){
	this->input = input;
	_cameraOriginPos = pos;

	_pointList = {
		new SplineBox(pos + Vector3D(-400,-400,0)),
		new SplineBox(pos + Vector3D(-200,400,0)),
		new SplineBox(pos + Vector3D(200,-400,0)),
		new SplineBox(pos + Vector3D(400,400,0))
	};

	_cameraDistance = -1000;
	_cameraAngle = Vector3D(90 * 3.141592f / 180, 0, 0);

	_cameraPos.x = _cameraDistance * cos(_cameraAngle.x) * cos(_cameraAngle.y);
	_cameraPos.y = _cameraDistance * sin(_cameraAngle.y);
	_cameraPos.z = _cameraDistance * sin(_cameraAngle.x) * cos(_cameraAngle.y);

	_mouse = new Mouse();
	_splineBox = nullptr;

	_moveType = MoveType::None;
	_modeType = ModeType::Modyfy;
	_splineType = SplineType::BSpline;

	_timePickPosX = TIME_TICK_X;
	_speedPickPosX = TIME_TICK_X;
	_isPlay = false;

	SetCameraNearFar(100.0f, 1000000.0f);

};

//----------------------------------------------------------------------
// @brief ������
// @return �������ɐ����������ǂ���
//----------------------------------------------------------------------
bool ModeSpline::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

//----------------------------------------------------------------------
// @brief �I������
// @return �I�������ɐ����������ǂ���
//----------------------------------------------------------------------
bool ModeSpline::Terminate() {
	base::Terminate();
	SetCameraNearFar(1.0f, 1000000.0f);
	return true;
}

//----------------------------------------------------------------------
// @brief �J�����̈ړ�
// @return �Ȃ�
//----------------------------------------------------------------------
void ModeSpline::SetCameraMove(){
	int oldX = _mouse->GetOldX();
	int oldY = _mouse->GetOldY();
	int x = _mouse->GetX();
	int y = _mouse->GetY();
	_cameraAngle.x += (float)(oldX - x) /1000;
	_cameraAngle.y += (float)(oldY - y) /1000;
};

//----------------------------------------------------------------------
// @brief �X�v���C���{�b�N�X�̈ړ�
// @return �Ȃ�
//----------------------------------------------------------------------
void ModeSpline::MoveSplineBox(){
	if (_splineBox != nullptr) {
		_splineBox->SetPos(ConvScreenPosToWorldPos(VGet(_mouse->GetX(), _mouse->GetY(), distance)));
	}
};

//----------------------------------------------------------------------
// @brief �ۑ�
// @return �Ȃ�
//----------------------------------------------------------------------
void ModeSpline::Save(){
	FILE* fp;
	fopen_s(&fp, "spline.txt", "w");
	if (fp == nullptr) {
		printfDx("�t�@�C�����J���܂���ł���");
		return;
	}
	std::string str;
	str += std::to_string(_timeSpeed) + "\n";
	for (int i = 0; i < _pointList.size(); i++) {
		Vector3D pos = _pointList[i]->GetPos();
		str+= std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + std::to_string(pos.z) + "\n";
	}

	str = str.substr(0,str.size()-2);//�I�[�����ƃJ���}�폜
	fprintf(fp, str.c_str());
	fclose(fp);
};

//----------------------------------------------------------------------
// @brief �}�E�X�ł̏Փ˔���
// @return �Ȃ�
//----------------------------------------------------------------------
void ModeSpline::CollisionCheck() {

	if (_mouse->GetTrg(MOUTH_LEFT)) {
		int x = _mouse->GetX();
		int y = _mouse->GetY();
		bool processSkip = false;
		// �ŏ��Ƀ��[�h�ύX
		int boxX = 0, boxY = 0, boxW = 80, boxH = 20;
		for (int i = 0; i < SELECTITEM_NUM; i++) {
			if (x > boxX && x < boxX + boxW && y > boxY && y < boxY + boxH) {
				switch (i) {
				case 0:
					_modeType = ModeType::Modyfy;
					break;
				case 1:
					_modeType = ModeType::AddPoint;
					processSkip = true;
					break;
				case 2:
					_modeType = ModeType::Remove;
					processSkip = true;
					break;
				case 3:
					_modeType = ModeType::Save;
					break;
				case 4:
					_isPlay = true;
					break;
				case 5:
					_isPlay = false;
					break;
				case 6:
					_splineType = SplineType::BSpline;
					break;
				case 7:
					_splineType = SplineType::CatmullRom;
					break;
				}
				break;
			}
			boxX += boxW + 10;
		}

		boxX = _timePickPosX - 10, boxY = 40, boxW = _timePickPosX + 10, boxH = 60;
		if (x > boxX && x < boxX + boxW && y > boxY && y < boxY + boxH) {
			_modeType = ModeType::Time;
		}

		boxX = _speedPickPosX - 10, boxY = 80, boxW = _speedPickPosX + 10, boxH = 60;
		if (x > boxX && x < boxX + boxW && y > boxY && y < boxY + boxH) {
			_modeType = ModeType::Speed;
		}

		// ���[�h�ɂ���ď�����ύX

		if(processSkip)return ;

		switch (_modeType) {
		case ModeType::Modyfy:

			for (float i = 0.0f; i < 1.0f; i += 1.0f / 100.0f) {
				if (_splineBox != nullptr)break;
				Vector3D startPos = ConvScreenPosToWorldPos(VGet(x, y, 0.0f));
				Vector3D endPos = ConvScreenPosToWorldPos(VGet(x, y, i));
				for (int j = 0; j < _pointList.size(); j++) {
					if (Collision3D::SegmentOBB(startPos, endPos, (*_pointList[j]->GetOBB()))) {
						_splineBox = _pointList[j];
						distance = i;
						_moveType = MoveType::Spline;
						break;
					}
				}
			}

			if (_splineBox == nullptr) {
				_moveType = MoveType::Camera;
			}
			break;
		case ModeType::AddPoint:
			_pointList.push_back(new SplineBox(ConvScreenPosToWorldPos(VGet(x,y,0.9f))));
			break;
		case ModeType::Remove:
			if (_pointList.size() > 4) {
				for (float i = 0.0f; i < 1.0f; i += 1.0f / 100.0f) {
					if (_splineBox != nullptr)break;
					Vector3D startPos = ConvScreenPosToWorldPos(VGet(x, y, 0.0f));
					Vector3D endPos = ConvScreenPosToWorldPos(VGet(x, y, i));
					for (int j = 0; j < _pointList.size(); j++) {
						if (Collision3D::SegmentOBB(startPos, endPos, (*_pointList[j]->GetOBB()))) {
							_deleteList.push_back(_pointList[j]);
							break;
						}
					}
				}
			}
			break;
		case ModeType::Save:
			Save();
			break;
		}
	}
};

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
bool ModeSpline::Process() {
	base::Process();
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	SuperManager::GetInstance()->Skip();
	_mouse->Update();
	if(input->GetTrg(XINPUT_BUTTON_START)){
		ModeServer::GetInstance()->Del(this);
	}

	if (_isPlay) {
		_time += _timeSpeed;
		if (_time > 1.0f) {
			_time = 0.0f;
		}
	}

	if (_mouse->GetRel(MOUTH_LEFT)) {
		_splineBox = nullptr;
		_moveType = MoveType::None;
		if (_modeType == ModeType::Save || _modeType == ModeType::Time || _modeType == ModeType::Speed) {
			_modeType = ModeType::Modyfy;
		}
	}

	if (_modeType == ModeType::Time) {
		int x = _mouse->GetX();
		_timePickPosX = x;
		_timePickPosX = Math::Clamp(TIME_TICK_X, TIME_TICK_X + TIME_TICK_WIDTH, _timePickPosX);
		_time = static_cast<float>(_timePickPosX - TIME_TICK_X) / TIME_TICK_WIDTH;
	}

	if (_modeType == ModeType::Speed) {
		int x = _mouse->GetX();
		_speedPickPosX = x;
		_speedPickPosX = Math::Clamp(TIME_TICK_X, TIME_TICK_X + TIME_TICK_WIDTH, _speedPickPosX);
		_timeSpeed = static_cast<float>(_speedPickPosX - TIME_TICK_X) / TIME_TICK_WIDTH / 100;
	}


	_timePickPosX = TIME_TICK_X + _time * TIME_TICK_WIDTH;

	for(auto itr = _deleteList.begin(); itr != _deleteList.end();++itr){
		for (auto itr2 = _pointList.begin(); itr2 != _pointList.end();) {
			if ((*itr) == (*itr2)) {
				delete (*itr2);
				itr2 = _pointList.erase(itr2);
				break;
			}
			itr2++;
		}
	}

	CollisionCheck();

	switch(_moveType){
		case MoveType::Spline:
			MoveSplineBox();
			break;
		case MoveType::Camera:
			SetCameraMove();
			break;
	}

	_cameraDistance -= GetMouseWheelRotVol() * 5;

	_cameraPos.x = _cameraDistance * cos(_cameraAngle.x) * cos(_cameraAngle.y);
	_cameraPos.y = _cameraDistance * sin(_cameraAngle.y);
	_cameraPos.z = _cameraDistance * sin(_cameraAngle.x) * cos(_cameraAngle.y);

	if(CheckHitKey(KEY_INPUT_A)){
		_cameraOriginPos.x += cos(_cameraAngle.x + 3.141592f / 2) * CAMERA_MOVE_SPEED;
		_cameraOriginPos.z += sin(_cameraAngle.x + 3.141592f / 2) * CAMERA_MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		_cameraOriginPos.x -= cos(_cameraAngle.x + 3.141592f / 2) * CAMERA_MOVE_SPEED;
		_cameraOriginPos.z -= sin(_cameraAngle.x + 3.141592f / 2) * CAMERA_MOVE_SPEED;
	}	
	if (CheckHitKey(KEY_INPUT_W)) {
		_cameraOriginPos.x += CAMERA_MOVE_SPEED * cos(_cameraAngle.x) * cos(_cameraAngle.y);
		_cameraOriginPos.y += CAMERA_MOVE_SPEED * sin(_cameraAngle.y);
		_cameraOriginPos.z += CAMERA_MOVE_SPEED * sin(_cameraAngle.x) * cos(_cameraAngle.y);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		_cameraOriginPos.x -= CAMERA_MOVE_SPEED * cos(_cameraAngle.x) * cos(_cameraAngle.y);
		_cameraOriginPos.y -= CAMERA_MOVE_SPEED * sin(_cameraAngle.y);
		_cameraOriginPos.z -= CAMERA_MOVE_SPEED * sin(_cameraAngle.x) * cos(_cameraAngle.y);
	}

	//Mode�ύX
	int x = _mouse->GetX();
	int y = _mouse->GetY();


	SetCameraPositionAndTarget_UpVecY((_cameraOriginPos + _cameraPos).toVECTOR(), _cameraOriginPos.toVECTOR());
	return true;
}

//----------------------------------------------------------------------
// @brief �`�揈��
// @return �Ȃ�
//----------------------------------------------------------------------
bool ModeSpline::Render() {
	base::Render();
	std::vector<Vector3D> carvePos;
	std::vector<Vector3D> _pos;

	for (int i = 0; i < _pointList.size(); i++) {
		_pointList[i]->Update();
		_pos.push_back(_pointList[i]->GetPos());
		_pointList[i]->GetOBB()->Render(GetColor(255, 255, 255));
	}

	int DivNum = 20;
	for(int i = 0; i < DivNum; i++){
		if(_splineType == SplineType::BSpline){
			carvePos.push_back(Spline::BSpline(_pos, _pos.size() , static_cast<double>(i) / DivNum));
		}
		else if(_splineType == SplineType::CatmullRom){
			carvePos.push_back(Spline::CatmullRomSpline(_pos, static_cast<double>(i) / DivNum));
		}
	}
	for(int i = 0; i < carvePos.size() - 1; i++){
		DrawLine3D(carvePos[i].toVECTOR(), carvePos[i + 1].toVECTOR(), GetColor(255, 0,0));
	}
	for(int i = 0; i < _pointList.size()-1; i++){
		DrawLine3D(_pos[i].toVECTOR(), _pos[i + 1].toVECTOR(), GetColor(0, 255, 0));
	}

	Vector3D sphere;
	if (_splineType == SplineType::BSpline) {
		sphere = Spline::BSpline(_pos, _pos.size(), _time);
	}
	else if (_splineType == SplineType::CatmullRom) {
		sphere = Spline::CatmullRomSpline(_pos, _time);
	}
	DrawSphere3D(sphere.toVECTOR(), 30, 10, GetColor(0, 0, 255), GetColor(0, 0, 255), true);

	std::string modeStr[] = { "Modify","AddPoint","Remove","Save","Play","Stop","BSpline","CatmullRom"};
	int x = 0, y = 0, w = 80, h = 20;
	for (int i = 0; i < SELECTITEM_NUM; i++) {
		// �F�̎w��
		int color = (i == static_cast<int>(_modeType) || i == static_cast<int>(_splineType)) ? GetColor(128, 128, 128) : GetColor(255, 255, 255);
		if(i == 4 && _isPlay)color = GetColor(128, 128, 128);
		else if(i == 5 && !_isPlay)color = GetColor(128, 128, 128);

		DrawBoxAA(x, y, x + w, y + h, color, true);
		DrawFormatString(x+5,0,GetColor(0,0,0),"%s",modeStr[i].c_str());
		x += w + 10;
	}

	DrawBox(TIME_TICK_X - 30, 25, TIME_TICK_X + TIME_TICK_WIDTH + 130, 75, GetColor(128, 128, 128), true);//�w�i
	DrawBox(TIME_TICK_X, 40, _timePickPosX, 60, GetColor(255, 255, 255), true);//�X���C�_�[
	DrawBox(_timePickPosX - 10, 30, _timePickPosX + 10, 70, GetColor(255, 255, 255), true);//�X���C�_�[�̂܂�
	DrawFormatString(TIME_TICK_X + TIME_TICK_WIDTH + 20, 40, GetColor(255, 255, 255), "Time:%f", _time);

	//-------------------------------------------------------
	DrawBox(TIME_TICK_X - 30, 25 + 60, TIME_TICK_X + TIME_TICK_WIDTH + 130, 75 + 60, GetColor(128, 128, 128), true);//�w�i
	DrawBox(TIME_TICK_X, 40 + 60, _speedPickPosX, 60 + 60, GetColor(255, 255, 255), true);//�X���C�_�[
	DrawBox(_speedPickPosX - 10, 30 + 60, _speedPickPosX + 10, 70 + 60, GetColor(255, 255, 255), true);//�X���C�_�[�̂܂�
	DrawFormatString(TIME_TICK_X + TIME_TICK_WIDTH + 20, 40 + 60, GetColor(255, 255, 255), "Speed:%f", _timeSpeed);

	float lineWidth = 50.0f;
	DrawLine3D((_cameraOriginPos - Vector3D(1, 0, 0) * lineWidth).toVECTOR(), (_cameraOriginPos + Vector3D(1, 0, 0) * lineWidth).toVECTOR(), 0x0000ff);
	DrawLine3D((_cameraOriginPos - Vector3D(0, 1, 0) * lineWidth).toVECTOR(), (_cameraOriginPos + Vector3D(0, 1, 0) * lineWidth).toVECTOR(), 0x00ff00);
	DrawLine3D((_cameraOriginPos - Vector3D(0, 0, 1) * lineWidth).toVECTOR(), (_cameraOriginPos + Vector3D(0, 0, 1) * lineWidth).toVECTOR(), 0xff0000);
	return true;
}
