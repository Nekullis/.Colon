//----------------------------------------------------------------------
// @filename DrawComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// OBB�`��N���X
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawOBBComponent.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawOBBComponent::DrawOBBComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder){
	m_Obb = new OBB();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawOBBComponent::~DrawOBBComponent(){
	delete m_Obb;
	m_Obb = nullptr;
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawOBBComponent::Update(){
	DrawComponent::Update();
	m_Obb->pos = m_Pos;
	m_Obb->Render(GetColor(255,255,255));
}

