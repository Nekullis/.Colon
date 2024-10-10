#include "../../Header/Function/Bone.h"
#include "../../Header/Math/Vector3D.h"
//----------------------------------------------------------------------
// @filename Bone.cpp
// @author: Saito Ko
// @explanation
// �L�����N�^�[�̔��̖т⃊�{���Ȃǂ�bone�𕨗����Z�œ��������߂̃N���X
//----------------------------------------------------------------------
const Vector3D Bone::_orign(0, 0, 0);

//1�e ���0.015 ~ 0.017�b���炢 
//1�񂾂Ɣ��U����
//2�񂾂Ƃ��ɂႮ�ɂ�ɂȂ�
//10�񂾂ƍ����ۂ��Ȃ�
//100��ȏオ���ꂢ�Ɍ�����
//���͑��150�`170��

#ifdef EULER
const float Bone::_processInterval = 0.0001f;
#elif RUNGE_KUTTA
const float bone::_processInterval = 0.0007f;
#endif
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param Model ���f���n���h��
// @param list �����������{�[���̃t���[���ԍ�
// @param size �{�[���̐�
// @param jsonFileName �p�����[�^�f�[�^��������json�t�@�C���̖��O
// @return �Ȃ�
//----------------------------------------------------------------------
Bone::Bone(
	int* Model,
	std::vector<int> list,
	int size,
	std::string jsonFileName
) :
	_model(Model),
	_frameList(list),
	_listSize(size),
	_springList(size + 1),
	_naturalList(size + 1)
{
	//�{�[���̏�����
	_vecDirList = new Vector3D[_listSize];
	_orignPos = new Vector3D[_listSize + 2];
	_transMatrixList = new MATRIX[_listSize];
	// �f�o�b�O����\�����邩�ǂ���
	_isTrans = 1;
	_oldIsTrans = _isTrans;
	// �v�Z����O�̍��̌�����s��E�ʒu���擾
	for (int i = 0; i < _listSize; i++) {
		_transMatrixList[i] = MV1GetFrameLocalMatrix(*_model, _frameList[i + 1]);//�����i�e�j�̏ꏊ
		MATRIX local_mat = MV1GetFrameLocalMatrix(*_model, _frameList[i + 2]);//�q�Ɍ����Ă������
		_vecDirList[i] = VTransform(_orign.toVECTOR(), local_mat);
		// �s���3�s�ڂ�������
		for (int j = 0; j < 3; j++) {
			_transMatrixList[i].m[3][j] = 0.0f;
		}

		_orignPos[i + 2] = MV1GetFramePosition(*_model, _frameList[i + 2]);
	}
	//�t�����̈ʒu���擾
	_orignPos[0] = MV1GetFramePosition(*_model, _frameList[0]);
	_orignPos[1] = MV1GetFramePosition(*_model, _frameList[1]);
	// �d�͂̌���
	_gravityDir = VGet(0.0f, -1.0f, 0.0f);

	//----------------------------------------------------------------------------------
	//�������Z�����邽�߂̕ϐ��̏�����
	_massPointSize = static_cast<int>(_frameList.size()) - 1;
	_massPosList = new Vector3D[_massPointSize];
	_massAccelList = new Vector3D[_massPointSize];

	_massWeight = new float[_massPointSize];
	_viscousResistance = new float[_massPointSize];
	_gravity = new float[_massPointSize];
	_spring = new float[_massPointSize];
	_naturalCorrectionFactor = new float[_massPointSize];

	//�t�@�C�����炻�ꂼ��̃p�����[�^��ǂݍ���-----------
	JsonFile json(jsonFileName);
	int i = 0;
	for (auto& bone : json.GetJson()) {
		bone.at("massWeight").get_to(_massWeight[i]);
		bone.at("viscousResistance").get_to(_viscousResistance[i]);
		bone.at("gravity").get_to(_gravity[i]);
		bone.at("spring").get_to(_spring[i]);
		bone.at("naturalCorrectionFactor").get_to(_naturalCorrectionFactor[i]);
		i++;
	}
	//--------------------------------------------------------------------------

	for (int i = 0; i < _massPointSize; i++) {
		_massPosList[i].Set(MV1GetFramePosition(*_model, _frameList[i + 1]));
	}

	for (int i = 0; i < _massPointSize - 1; i++) {
		//_naturalList�̏�����
		//_natulalCorrectionFactor�͒ʏ�1.0�ŗǂ��Ǝv�����A
		// ���̖т��ُ�ɒ����Ȃ����Ƃ���_natulalCorrectionFactor��ύX��
		// ���̃��f���̔��̒����ɋ߂���Ԃɂ���
		_naturalList[i] = _naturalCorrectionFactor[i] * (_massPosList[i + 1] - _massPosList[i]).Len();

		//_springList�̏�����
		//�΂˂̒l�͌��܂��Ă��邪_naturalCorrectionFactor�ɔ�Ⴕ�ĕύX����
		//����͎��_�����̒��������K�v�Ȃ���
		// ���_�ɍ��킵�Ă΂˒萔���ύX�\
		_springList[i] = _naturalList[i] * _spring[i];
	}
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Bone::~Bone() {
	_frameList.clear();
	_springList.clear();
	_naturalList.clear();
	_model = nullptr;

	delete[] _vecDirList;         _vecDirList = nullptr;
	delete[] _orignPos;           _orignPos = nullptr;
	delete[] _transMatrixList; _transMatrixList = nullptr;

	delete[] _massPosList;    _massPosList = nullptr;
	delete[] _massAccelList;  _massAccelList = nullptr;

	delete[] _massWeight;     _massWeight = nullptr;
	delete[] _viscousResistance; _viscousResistance = nullptr;
	delete[] _gravity;               _gravity = nullptr;
	delete[] _spring;               _spring = nullptr;
	delete[] _naturalCorrectionFactor; _naturalCorrectionFactor = nullptr;

};
//----------------------------------------------------------------------
// @brief ���C������
// @param pos_list �{�[���̈ʒu�̃��X�g
// @return �����������ǂ���
//----------------------------------------------------------------------
void Bone::SetMain(Vector3D* pos_list) {
	for (int i = 0; i < _listSize; i++) {
		SetBoneDir(
			pos_list[i + 1],
			pos_list[i],
			_frameList[i + 1],
			_frameList[i],
			_transMatrixList[i],
			_vecDirList[i]
		);
	};
};
//----------------------------------------------------------------------
// @brief �{�[���̌�����ݒ�
// @param world_dir_vec �{�[���̕���
// @param boon_pos �{�[���̕t�����̈ʒu
// @param target_frame �ύX����{�[���̃t���[���ԍ�
// @param parent_frame �e�{�[���̃t���[���ԍ�
// @param trans_mat  �t�����̈ʒu��ύX���邽�߂̍s��
// @param dir_parent ���̌���
// @return �Ȃ�
//----------------------------------------------------------------------
void Bone::SetBoneDir(
	Vector3D world_dir_vec,
	Vector3D boon_pos,
	int target_frame,
	int parent_frame,
	MATRIX trans_mat,
	Vector3D dir_parent)
{
	MATRIX tmpMat;
	tmpMat = MV1GetFrameLocalWorldMatrix(*_model, parent_frame); // �e�{�[���̃��[�J�������[���h
	tmpMat = MInverse(tmpMat); // �t�s����v�Z
	Vector3D localDirVec = VTransform(world_dir_vec.toVECTOR(), tmpMat);//�{�[��������̃��[�J�����W
	Vector3D localBonePos = VTransform(boon_pos.toVECTOR(), tmpMat);//�����̕t�����̃��[�J�����W

	//�{�[����������������
	Vector3D localDirLook = (localDirVec - localBonePos).Normalize();

	//���̌������玟�̌����ւ̉�]�s��
	MATRIX rotationMat = MGetRotVec2(dir_parent.toVECTOR(), localDirLook.toVECTOR());

	//�����̕t�������ʒu�ɂȂ�悤�A���s�ړ�
	MATRIX shiftPos = trans_mat;
	shiftPos.m[3][0] = localBonePos.x;
	shiftPos.m[3][1] = localBonePos.y;
	shiftPos.m[3][2] = localBonePos.z;

	tmpMat = MMult(rotationMat, shiftPos);
	MV1SetFrameUserLocalMatrix(*_model, target_frame, tmpMat);
}
//----------------------------------------------------------------------
// @brief �f�o�b�O����
// @param transNum �����ɂ���{�[���̃t���[���ԍ�
// @return �Ȃ�
//----------------------------------------------------------------------
void Bone::DebugProcess(int transNum) {
	if (_oldIsTrans != _isTrans) {
		for (int i = 0; i < _frameList.size(); i++) {
			int frameNum = _frameList.at(i);
			MV1SetFrameVisible(*_model, frameNum, _isTrans);
		}
		MV1SetFrameVisible(*_model, transNum, _isTrans);
		_oldIsTrans = _isTrans;
	}
};
//----------------------------------------------------------------------
// @brief �f�o�b�O�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void Bone::DebugRender() {
	if (!_isTrans) {
		float r = 5;
		int divNum = 16;
		int color = GetColor(255, 0, 0);
		for (int i = 0; i < _frameList.size(); i++) {
			int frameNum = _frameList.at(i);
			if (!MV1GetFrameVisible(*_model, frameNum)) {
				VECTOR pos = MV1GetFramePosition(*_model, frameNum);
				DrawSphere3D(pos, r, divNum, color, color, true);
			}
		}
	}
};
//----------------------------------------------------------------------
// @brief ���C������
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Bone::Process() {
	// 1F�̌o�ߎ��Ԃ��擾
	double _elapsedTime = 0;//elapsedTime�͌o�ߎ���
	// �o�ߎ��Ԃ����������ď������s��
	while (1)
	{
		//1�t���[����_processInterval�ō���������
		if (_elapsedTime < _processInterval)break;
		_elapsedTime -= _processInterval;
#ifdef EULER
		UpdatePosAndAccelByEuler(_processInterval);
#elif RUNGE_KUTTA
		UpdatePosAndAccelByRungeKutta(_processInterval);
#endif
	}
	// �{�[���̈ʒu���X�V
	SetMain(_massPosList);
	return true;
};
//----------------------------------------------------------------------
// @brief �d�͂̕�����ݒ�
// @param end �d�͂̕�����ݒ�ʒu���擾���邽�߂̃{�[���̃t���[����
// @param start �d�͂̕�����ݒ�ʒu���擾���邽�߂̃{�[���̃t���[����
// @return �Ȃ�
//----------------------------------------------------------------------
void Bone::SetGravity(std::string end, std::string start) {
	int frame = MV1SearchFrame(*_model, end.c_str());
	VECTOR headPos = MV1GetFramePosition(*_model, frame);
	frame = MV1SearchFrame(*_model, start.c_str());
	VECTOR spinePos = MV1GetFramePosition(*_model, frame);

	VECTOR dirVec = VSub(spinePos, headPos);
	_gravityDir = VNorm(VScale(dirVec, -1));
};
//----------------------------------------------------------------------
// @brief �I�C���[�@�ɂ��bone�̈ʒu�Ɖ����x�̍X�V
// @param _elapsedTime ��������������
// @return �Ȃ�
// ----------------------------------------------------------------------
void Bone::UpdatePosAndAccelByEuler(float _elapsedTime) {
	//���Ԃŏ������ו����������������ɋ߂Â��Ă���
	Vector3D* newPosList = new Vector3D[_massPointSize];
	Vector3D* newAccelList = new Vector3D[_massPointSize];

	//�t�����̈ʒu�͌Œ�
	_massPosList[0] = MV1GetFramePosition(*_model, _frameList[1]);
	newPosList[0] = _massPosList[0];

	// ���x�ƈʒu�̍X�V
	for (int i = 1; i < _massPointSize; i++) {
		// �j���[�g���̉^�����������
		// F = ma ����͑��x���~�����̂� a = F/m
		Vector3D Accel = ForceWorksToMassPoint(i, _massPosList, _massAccelList) / _massWeight[i];
		//���x���o��   y(i+1) = y(i) + hf 
		newAccelList[i] = _massAccelList[i] + _elapsedTime * Accel;
		//�ʒu�̍X�V   y(i+1) = y(i) + hf 
		newPosList[i] = _massPosList[i] + _elapsedTime * _massAccelList[i];
	}

	// ���x�ƈʒu���܂Ƃ߂ĕύX
	std::swap(_massAccelList, newAccelList);
	std::swap(_massPosList, newPosList);

	delete[] newPosList;
	delete[] newAccelList;
};
//----------------------------------------------------------------------
// @brief �����Q�N�b�^�@�ɂ��bone�̈ʒu�Ɖ����x�̍X�V
// @param _elapsedTime ��������������
// @return �Ȃ�
// ----------------------------------------------------------------------
void Bone::UpdatePosAndAccelByRungeKutta(float _elapsedTime) {
	//���Ԃŏ������ו����������������ɋ߂Â��Ă���
	Vector3D* keepPosList = new Vector3D[_massPointSize];
	Vector3D* keepAccelList = new Vector3D[_massPointSize];

	Vector3D** posK = new Vector3D * [4];
	Vector3D** accelK = new Vector3D * [4];
	for (int i = 0; i < 4; i++) {
		posK[i] = new Vector3D[_massPointSize];
		accelK[i] = new Vector3D[_massPointSize];
	}

	// 4���̃����Q�N�b�^�@
	//k1,k2,k3,k4�����߂āA�������g���Ĉʒu�Ƒ��x���X�V����

	//k1�����߂�
	for (int i = 0; i < _massPointSize; i++) {
		accelK[0][i] = ForceWorksToMassPoint(i, _massPosList, _massAccelList) / _massWeight[i];
		posK[0][i] = _massAccelList[i];
		keepAccelList[i] = _massAccelList[i] + accelK[0][i] * _elapsedTime / 2;
		keepPosList[i] = _massPosList[i] + posK[0][i] * _elapsedTime / 2;
	}

	//k2�����߂�
	for (int i = 0; i < _massPointSize; i++) {
		accelK[1][i] = ForceWorksToMassPoint(i, keepPosList, keepAccelList) / _massWeight[i];
		posK[1][i] = keepAccelList[i];
		keepAccelList[i] = _massAccelList[i] + accelK[1][i] * _elapsedTime / 2;
		keepPosList[i] = _massPosList[i] + posK[1][i] * _elapsedTime / 2;
	}

	//k3�����߂�
	for (int i = 0; i < _massPointSize; i++) {
		accelK[2][i] = ForceWorksToMassPoint(i, keepPosList, keepAccelList) / _massWeight[i];
		posK[2][i] = keepAccelList[i];
		keepAccelList[i] = _massAccelList[i] + accelK[2][i] * _elapsedTime;
		keepPosList[i] = _massPosList[i] + posK[2][i] * _elapsedTime;
	}

	//k4�����߂�
	for (int i = 0; i < _massPointSize; i++) {
		accelK[3][i] = ForceWorksToMassPoint(i, keepPosList, keepAccelList) / _massWeight[i];
		posK[3][i] = keepAccelList[i];
	}

	// ���x�ƈʒu�̍X�V
	for (int i = 0; i < _massPointSize; i++) {
		//���x���o��   
		_massAccelList[i] = _massAccelList[i] + (_elapsedTime * (accelK[0][i] + 2 * accelK[1][i] + 2 * accelK[2][i] + accelK[3][i]) / 6);
		//�ʒu�̍X�V   
		_massPosList[i] = _massPosList[i] + (_elapsedTime * (posK[0][i] + 2 * posK[1][i] + 2 * posK[2][i] + posK[3][i]) / 6);
	}

	//�t�����̈ʒu�͌Œ�
	_massPosList[0] = MV1GetFramePosition(*_model, _frameList[1]);

	delete[] keepPosList;
	delete[] keepAccelList;
	for (int i = 0; i < 4; i++) {
		delete[] posK[i];
		delete[] accelK[i];
	}

}
//----------------------------------------------------------------------
// @brief �΂˂̂荇���A�d�́A��R�͂���͂����߂�
// @param i ���_�̔ԍ�
// @param posList ���_�̈ʒu�̃��X�g
// @param accelList ���_�̉����x�̃��X�g
// @return �j���[�g���̉^���̖@���Ɋ�Â�����
// ----------------------------------------------------------------------
Vector3D Bone::ForceWorksToMassPoint(int i, Vector3D* posList, Vector3D* accelList) {
	Vector3D force;

	//�s������
	//�΂˂̂荇�� ������̒e���͂Ɖ������̏d�͂��荇�����v�Z
	//��R������
	//�d�͂�������

	//���_i�`���_i+1�Ԃ̂΂˂���󂯂��
	if (i < _massPointSize - 1) {
		////�΂˂̐L�ы�𒲂ׂ�
		float growth = (posList[i + 1] - posList[i]).Len() - _naturalList[i];
		//�΂˂̐L�т�͂ɕϊ�
		force += _springList[i] * growth * (posList[i + 1] - posList[i]).Normalize();
	}

	// ���_i-1�`���_i�Ԃ̃o�l����󂯂�� 
	//�΂˂̐L�ы�𒲂ׂ�
	float growth = (posList[i] - posList[i - 1]).Len() - _naturalList[i - 1];
	//�΂˂̐L�т�͂ɕϊ�
	force += _springList[i - 1] * growth * (posList[i - 1] - posList[i]).Normalize();

	//����͔S����R 
	//��R�͂Ȃ̂Ł|�𑫂�
	force -= _viscousResistance[i] * accelList[i];

	//�d�� 
	force += _massWeight[i] * _gravity[i] * _gravityDir;

	return force;
};
//----------------------------------------------------------------------
// @brief bone�̈ʒu�Ɖ����x�̏�����
// @return �Ȃ�
//----------------------------------------------------------------------
void Bone::PositionReset() {
	//�����Ӂ@�ʒu�⑬�x�����������܂����A
	// �����ȃ��f���łȂ��Ə�����������d�͂̉e���œ����܂�
	for (int i = 0; i < _listSize; i++) {
		//���W�Ԋҍs��̏�����
		MV1ResetFrameUserLocalMatrix(*_model, _frameList[i + 1]);
	}

	for (int i = 0; i < _massPointSize; i++) {
		//�ʒu�̏�����
		_massPosList[i] = MV1GetFramePosition(*_model, _frameList[i + 1]);
		//���x���O�ɂ���
		_massAccelList[i].Set(0.0f, 0.0f, 0.0f);
	}
};