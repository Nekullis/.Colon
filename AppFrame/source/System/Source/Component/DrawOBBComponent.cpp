//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// OBB�`��N���X
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawOBBComponent.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawOBBComponent::DrawOBBComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder)
{
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawOBBComponent::~DrawOBBComponent(){
}

//----------------------------------------------------------------------
// @brief �ǂݍ���
// @param pass ���f���̃p�X
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawOBBComponent::Update(){
	DrawComponent::Update();
}

//----------------------------------------------------------------------
// @brief ���f���̐ݒ�E�`��
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawOBBComponent::LoadPass(const char* pass){
	DrawComponent::LoadPass(pass);
}
