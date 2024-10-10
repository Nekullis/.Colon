//----------------------------------------------------------------------
// @filename ResourceServer.h
// @author: Saito Ko
// @explanation
// �摜�⃂�f���Ȃǂ̃��\�[�X���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include "EffekseerForDXLib.h"

class ResourceServer
{
public:

	enum class TYPE: int {
		Handle = 0,
		Mult,
		Efk,
		Model,
		Sound,
	};

	//�����̉摜��ۑ����邽�߂̍\����
	struct Mult {
		int  AllNum = -1;//�摜�̑S�̖̂���
		int* handle = nullptr;//�摜��ۑ�����p�̕ϐ�   ���������I�ɕω����邽�߃|�C���^
	};

	// �摜�G�t�F�N�V�Amv1�n���h���𔻕ʂ��ǂݍ��ފ֐��ł� 
	// �����ɕ�������ǂݍ��݂ɂ͑Ή����Ă��܂���
	static int Load(std::string key, std::string handleName);

	// �l��Ԃ��ǂݍ��݊֐�
	static int LoadGraph(std::string key_name, std::string handle_name);//�摜�n���h���̓ǂݍ���
	static int LoadDivGraph(std::string key_name, std::string handle_name, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleBuf); //�摜�n���h���̕��������̓ǂݍ���
	//�摜�̕����ǂݍ��݁@���O�� �g���q�ƕ����Ă������� ���O�̓t�@�C���̂Ƃ���ł܂Ƃ߂ĕύX����΂��̂܂܎g����͂��ł��B
	static int LoadMultGraph(std::string key_name, std::string handle_name, std::string extension, int AllNum, int* HandleBuf);
	static int LoadEffekseerEffect(std::string key_name, std::string handle_name);//�G�t�F�N�V�A�̃G�t�F�N�g�̓ǂݍ���
	static int MV1LoadModel(std::string key_name, std::string  model_name,bool duplicate = true);//dxlib��.mv1�`���ɑΉ������R�c���f���̓ǂݍ���
	static int LoadSound(std::string key_name, std::string sound_name);//�T�E���h�̓ǂݍ���
	
	// �l��Ԃ��Ȃ��ǂݍ��݊֐�
	static int LoadDivGraph(std::string key_name, std::string handle_name, int AllNum, int XNum, int YNum, int XSize, int YSize); //�摜�n���h���̕��������̓ǂݍ���
	static int LoadMultGraph(std::string key_name, std::string handle_name, std::string extension, int AllNum);

	static int LoadVertexShader(std::string key_name, std::string handle_name);//���_�V�F�[�_�[�̓ǂݍ���
	static int LoadPixelShader(std::string key_name, std::string handle_name);//�s�N�Z���V�F�[�_�[�̓ǂݍ���

	static int SearchSingle(std::string search_key, TYPE resouceType);
	static bool SearchMult(std::string search_key,int* handle, int size);
	static ResourceServer::Mult SearchMult(std::string search_key);
	static std::pair<bool, int> DeleteSearchSingle(std::string search_key, std::unordered_map<std::string,int>* resourceMap);
	static std::pair<bool, ResourceServer::Mult> DeleteSearchMult(std::string search_key, std::unordered_map<std::string, Mult>* resourceMap);

	
	static bool Delete(std::string key, TYPE resouceType);
	static bool MV1DeleteModel(std::string key, int model); // �w�肵��key��model�̒l����T���o���폜�@�����d���ł�
	static bool MV1DeleteModelAll(std::string key);// �w�肵��key�̃��f�����������ꍇkey�̂��ׂĂ��폜����
	static bool MV1DeleteModelOrigin(std::string key);//�w�肵��key�̃��f�����ǂݍ���ł������ꍇ Duplicate���邽�߂̃I���W�i���n���h�����폜����

	static void DeleteResourceAll();//�S�Ẵ��\�[�X���폜

	static std::unordered_map<std::string, int> _handleMap;//�摜��ۑ�����ϐ�
	static std::unordered_map<std::string, int> _soundMap;//se�Ebgm��ۑ�����ϐ�
	static std::unordered_map<std::string, Mult> _multMap;//�����̉摜��ۑ�����ϐ�
	static std::unordered_map<std::string, int >_effekseerMap;//�G�t�F�N�V�A�̃G�t�F�N�g��ۑ�����ϐ�
	static std::unordered_map<std::string, int >_modelOriginMap;//dxlib�̃��f���n���h����ۑ�����ϐ�
	static std::unordered_map<std::string, std::vector<int> >_modelMap;//dxlib�̃��f���n���h����ۑ�����ϐ�
	static std::unordered_map<std::string, int > _pixelShaderMap;//�s�N�Z���V�F�[�_�[��ۑ�����ϐ�
	static std::unordered_map<std::string, int > _vertexShaderMap;//���_�V�F�[�_�[��ۑ�����ϐ�
};