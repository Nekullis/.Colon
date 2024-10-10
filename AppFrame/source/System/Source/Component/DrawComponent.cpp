//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �`��p�R���|�[�l���g�̊��N���X
//----------------------------------------------------------------------
#include"../../AppFrame/source/System/Header/Component/DrawComponent.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawComponent::DrawComponent(ObjectBase* owner, int updateowder):Component(owner, updateowder) {
	m_Owner = owner;
	m_Handle = 0;
	m_Pass = "";
	m_Pos = Vector3D(0.0f, 0.0f, 0.0f);
	m_Scale = Vector3D(1.0f, 1.0f, 1.0f);

}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawComponent::~DrawComponent(){
}

//----------------------------------------------------------------------
// @brief �ǂݍ���
// @param pass ���f���̃p�X
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawComponent::LoadPass(const char* pass) {
	m_Pass = pass;
}

//----------------------------------------------------------------------
// @brief ���f���̐ݒ�E�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawComponent::Update(){
	Component::Update();
}
