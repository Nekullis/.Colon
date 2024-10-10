//----------------------------------------------------------------------
// @filename Afterglow.cpp
// @date: 2024/04/01
// @author: saito ko
// @explanation
// �S�����U�����A�S���̖ڂɎc���𔭐�������N���X
//----------------------------------------------------------------------
#include "../../Header/Effect/Afterglow.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param model: ���f���n���h��
// @param frameNum: ���f���n���h���ɂ���ʒu���擾�������W���C���g�ԍ�
// @param length: �|���S����\������Ƃ���y���̒���
// @param handle: �摜�n���h��
// @param animCountMax: �A�j���[�V�����̗�����������
// @return �Ȃ�
//----------------------------------------------------------------------
Afterglow::Afterglow(int model,int frameNum,float length,int handle,int animCountMax){
	// ������
	IsUpdate = false;
	_model = model;
	_frameNum = frameNum;
	_length = length;
	_handle = handle;
	_animCount = 0;
	_animCountMax = animCountMax;
	IsStop = false;
	_oldPos = VGet(0,0,0);

	_subColor = static_cast<int>(255 / animCountMax);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Afterglow::~Afterglow(){
	_vertex.clear();
	_vertexIndex.clear();
};
//----------------------------------------------------------------------
// @brief ���_��ǉ����ʒu��uv�l��ݒ肷��
// @return �Ȃ�
//----------------------------------------------------------------------
void Afterglow::SetVertex(){
	// �R���e�i�̍ŏ��ɒl��ǉ�����֐�
	auto vertex_push_front = [&](VERTEX3D index){
		_vertex.insert(_vertex.begin(), index);
	};
	auto index_push_front = [&](unsigned short index){
		_vertexIndex.insert(_vertexIndex.begin(),index);
	};

	// �t���[���̈ʒu���擾
	VECTOR pos = MV1GetFramePosition(_model,_frameNum);
	// �O�̈ʒu�Ƃ̍������擾
	VECTOR dirVec = VSub(pos, _oldPos);
	if(VSquareSize(dirVec) > 0.01f){
		// �ʒu���ς���Ă���Ƃ����K��
		dirVec = VNorm(dirVec);
	    // �@���x�N�g�����擾
	    VECTOR normalVecX = VNorm(VCross(dirVec,VGet(0,1,0)));
	    // �@���x�N�g�������ɏ㉺�̃x�N�g�����擾
	    VECTOR normalVecY = VNorm(VCross(dirVec, normalVecX));
	    VECTOR upVec = VScale(normalVecY,_length);
	    VECTOR downVec = VScale(normalVecY, _length * -1);
	    
	    // ���_���X�g
	    VECTOR posList[2] = {VAdd(pos,downVec),VAdd(pos,upVec)};
	    float vList[2] = {0,1};
	    // ���_��ݒ�
	    for(int i = 0 ; i < 2; i++){
			VERTEX3D vertex{};
	    	vertex.pos = posList[i];
	    	vertex.norm = normalVecX;
	    	vertex.dif = GetColorU8(255,0,0,255);
	    	vertex.spc = GetColorU8(0,0,0,0);
	    	vertex.u = 0;
	    	vertex.v = vList[i];
	    	vertex.su = 0;
	    	vertex.sv = 0;
	    	// ���_��ǉ�
	    	vertex_push_front(vertex);
	    }
	    
	    // ���_�C���f�b�N�X�����炷
	    for(auto&& index : _vertexIndex){
	        index +=2;
	    }
	    // ���_�C���f�b�N�X���X�g
	    unsigned short indexList[6] = {3,2,1,1,2,0};
	    // ���_�C���f�b�N�X��ǉ�
	    for(int i = 0; i < 6; i++){
	    	index_push_front(indexList[i]);
	    }

		if(IsStop){
			_animCount = static_cast<int>(_vertex.size()) / 2;
			IsStop = false;
		}

	}
	else{
		IsStop = true;
	}
	// �ʒu��ۑ�
	_oldPos = pos;
};
//----------------------------------------------------------------------
// @brief ���_���X�V���A�j���[�V�������s��
// @return �Ȃ�
//----------------------------------------------------------------------
void Afterglow::Process(){
	// u�l���X�V
	for(auto&& vertex : _vertex){
	    vertex.u += 1.0f / _animCountMax;
		vertex.dif.r -= _subColor;
		vertex.dif.a -= _subColor;
	}

	// ���_������Ƃ�
	if(_vertex.size() > 0 ){
		// �A�j���[�V�����J�E���g���ő�l�ɒB���Ă��Ȃ��Ƃ����₷
		if(_animCount < _animCountMax+1){
			_animCount++;
		}
		else{
			// �A�j���[�V�����J�E���g���ő�l�ɒB���Ă���̂ō폜�J�n����
			// ����Ȃ����_���폜
			for(int i = 0; i < 2; i++){
			   _vertex.pop_back();
			}
			// ����Ȃ����_�C���f�b�N�X���폜
			for(int i = 0; i < 6; i++){
			   _vertexIndex.pop_back();
			}
		}
		// ���_���Ȃ��Ȃ�����A�j���[�V�����J�E���g��0�ɏ�����
		if(_vertex.size() == 0){
			_animCount = 0;
		}
	}

	// ���_��ݒ肷��t���O�������Ă���Ƃ�
	if (IsUpdate) {
		SetVertex();
	}

};
//----------------------------------------------------------------------
// @brief �|���S����`�悷��
// @return �Ȃ�
//----------------------------------------------------------------------
void Afterglow::Render(){
	if(_vertex.size() >= 4){
		// ���C�e�B���O�ƃo�b�N�J�����O�𖳌��ɂ��ĕ`��
		SetUseLighting(false);
		SetUseBackCulling(false);
		DrawPolygonIndexed3D(_vertex.data(), static_cast<int>(_vertex.size()), _vertexIndex.data(), (static_cast<int>(_vertexIndex.size()) / 3) - 2, _handle, true);
		// ���ɖ߂�
		SetUseLighting(true);
		SetUseBackCulling(true);
	}
};
