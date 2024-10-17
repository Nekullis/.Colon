//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// ���̕`��p�R���|�[�l���g�N���X
//----------------------------------------------------------------------
#include "../../AppFrame/source/System/Header/Component/DrawSphereComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawSphereComponent::DrawSphereComponent(ObjectBase* owner, int updateowder):DrawComponent(owner,updateowder){
	m_Sphere = new Sphere();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawSphereComponent::~DrawSphereComponent(){
	delete m_Sphere;
	m_Sphere = nullptr;
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawSphereComponent::Update(){
	DrawComponent::Update();
	m_Sphere->pos = m_Pos;
	m_Sphere->Render(GetColor(255, 255, 255));
}
