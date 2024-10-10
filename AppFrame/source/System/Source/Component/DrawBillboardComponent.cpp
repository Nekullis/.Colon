//----------------------------------------------------------------------
// @filename DrawBillboardComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �r���{�[�h��`�悷�邽�߂̃R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/DrawBillboardComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawBillboardComponent::DrawBillboardComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder)
{
	m_Owner = owner;
	mHandle = -1;
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawBillboardComponent::~DrawBillboardComponent()
{

}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawBillboardComponent::Update()
{
	Component::Update();
	DrawBillboard3D(m_Owner->GetPos().toVECTOR(), 0.5f, 0.5f, 1.0f, 0.0f, mHandle, true);
}
