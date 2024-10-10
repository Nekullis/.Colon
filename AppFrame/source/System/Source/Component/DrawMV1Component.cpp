//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// MV1���f���`��p�R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/DrawMV1Component.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawMV1Component::DrawMV1Component(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder){
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawMV1Component::~DrawMV1Component(){
	MV1DeleteModel(m_Handle);
}

//----------------------------------------------------------------------
// @brief ���f���̓ǂݍ���
// @param pass ���f���̃p�X
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawMV1Component::LoadPass(const char* pass){
	m_Pass = pass;
	m_Handle = MV1LoadModel((const TCHAR*)(m_Pass));
}

//----------------------------------------------------------------------
// @brief ���f���̐ݒ�E�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawMV1Component::Update(){
	//�R���|�[�l���g�X�V����
	DrawComponent::Update();
	//���f���̈ʒu�ݒ�
	MV1SetPosition(m_Handle, m_Owner->GetPos().toVECTOR());
	//���f���̃T�C�Y�ݒ�
	MV1SetScale(m_Handle, m_Owner->GetScale().toVECTOR());
	//�����ݒ�
	MV1SetRotationXYZ(m_Handle, m_Owner->GetRotation().toVECTOR());
	//�`�揈��
	MV1DrawModel(m_Handle);
}


