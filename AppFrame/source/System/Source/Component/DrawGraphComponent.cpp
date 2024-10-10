//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �摜�`��p�R���|�[�l���g
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawGraphComponent.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawGraphComponent::DrawGraphComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder) {
	
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawGraphComponent::~DrawGraphComponent(){
	DeleteGraph(m_Handle);
}

//----------------------------------------------------------------------
// @brief ���f���̓ǂݍ���
// @param pass ���f���̃p�X
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawGraphComponent::LoadPass(const char* pass) {
	DrawComponent::LoadPass(pass);
	m_Handle = LoadGraph(m_Pass);
}

//----------------------------------------------------------------------
// @brief ���f���̐ݒ�E�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawGraphComponent::Update(){
	DrawComponent::Update();
	//�`��
	DrawGraph(static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y), m_Handle, true);
}


