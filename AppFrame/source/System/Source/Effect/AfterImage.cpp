//----------------------------------------------------------------------
// @filename AfterImage.cpp
// @author: Morozumi Hiroya
// @explanation
// �L�����N�^�[�̎c���\�����s���N���X
// �������ɂ������f���𕡐��̕\�����邱�ƂŎc����\������
//----------------------------------------------------------------------
#include "../../Header/Effect/AfterImage.h"
#include "../../Header/Resource/ResourceServer.h"

AfterImage::AfterImage()
{
	_parentModelHandle = -1;

	_modelInfo.clear();
	_afterImageNum = 0;
	_remainTimeMax = 0;
}

AfterImage::~AfterImage()
{
	for(auto itr = _modelInfo.begin(); itr != _modelInfo.end(); ++itr)
	{
		delete (*itr);
		(*itr) = nullptr;
	}
	_modelInfo.clear();
}

// ����������
// @param parentModelHandle: �e���f���̃n���h��
// @param keyName: �L�[���iResourceServer�ł̃��f���f�[�^�̊Ǘ��Ɏg�p����j
// @param modelName: ���f���̃p�X
// @param afterImageNum: �����ɕ\������c���̍ő吔
// @param remainTime: �c���̎�������
void AfterImage::Init(int parentModelHandle, std::string keyName, std::string modelName, int afterImageNum, int remainTime)
{
	_parentModelHandle = parentModelHandle;

	this->_afterImageNum = afterImageNum;
	_modelInfo.resize(afterImageNum);

	this->_remainTimeMax = remainTime;

	// �c�����f�����̏�����
	for(int i = 0; i < _afterImageNum; i++) {
		_modelInfo[i] = new ModelInfo();

		_modelInfo[i]->use = false;
		_modelInfo[i]->remainTime = 0;

		_modelInfo[i]->modelHandle = ResourceServer::MV1LoadModel(keyName, modelName);
		_modelInfo[i]->difColorScale = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

// �c����ǉ�����
// @param animIndex: �A�j���[�V�����̃C���f�b�N�X�imv1�t�@�C�����ł̃C���f�b�N�X�ԍ��j�i-1�̏ꍇ�̓A�j���[�V������K�����Ȃ��j
// @param playTime: �A�j���[�V�����̍Đ�����
void AfterImage::AddAfterImage(int animIndex, float playTime)
{
	for(int i = 0; i < _afterImageNum; i++) {
		// �g�p���Ă��Ȃ��v�f��T��
		if(_modelInfo[i]->use == false) {
			// �c���̐ݒ�
			_modelInfo[i]->use = true;
			_modelInfo[i]->remainTime = _remainTimeMax;

			// �e���f���̃f�B�t���[�Y�J���[�̃X�P�[���l���擾���A�c�����f���ɓK������
			_modelInfo[i]->difColorScale = MV1GetDifColorScale(_parentModelHandle);
			MV1SetDifColorScale(_modelInfo[i]->modelHandle, _modelInfo[i]->difColorScale);

			// �e���f���̍s����c�����f���ɓK������
			MV1SetMatrix(_modelInfo[i]->modelHandle, MV1GetMatrix(_parentModelHandle));

			// �A�j���[�V�����̐ݒ�
			if(animIndex != -1) {
				_modelInfo[i]->attachIndex = MV1AttachAnim(_modelInfo[i]->modelHandle, animIndex);
				MV1SetAttachAnimTime(_modelInfo[i]->modelHandle, _modelInfo[i]->attachIndex, playTime);
			}

			break;
		}
	}
}

// �X�V����
void AfterImage::Process()
{
	for (int i = 0; i < _afterImageNum; i++) {
		if (_modelInfo[i]->use == true) {
			// �c��J�E���g�����炷
			_modelInfo[i]->remainTime--;

			// �c��J�E���g��0�ȉ��ɂȂ�����g�p�t���O��false�ɂ���
			if (_modelInfo[i]->remainTime <= 0) {
				_modelInfo[i]->use = false;

				// �A�j���[�V�����̃f�^�b�`
				MV1DetachAnim(_modelInfo[i]->modelHandle, _modelInfo[i]->attachIndex);
			}
			else {
				// �c��J�E���g�ɉ����ē����x��ύX����
				float alphaRate = (float)_modelInfo[i]->remainTime / (float)_remainTimeMax;
				COLOR_F nextColor = _modelInfo[i]->difColorScale;
				nextColor.a = _modelInfo[i]->difColorScale.a * alphaRate;
				MV1SetDifColorScale(_modelInfo[i]->modelHandle, nextColor);
			}
		}
	}
}

// �`�揈��
void AfterImage::Render()
{
	for(int i = 0; i < _afterImageNum; i++) {
		if(_modelInfo[i]->use == true) {
			MV1DrawModel(_modelInfo[i]->modelHandle);
		}
	}
}

