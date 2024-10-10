#include <fstream>
#include <iostream>
#include "JsonFile.h"

JsonFile::JsonFile(const std::string& fileName)
{
	//�t�@�C�����J��
	std::ifstream file(fileName);
	if (!file) {
		//�t�@�C�����ǂݍ��߂Ȃ�����
		return;
	}
	//�t�@�C�����ǂݍ��߂��̂�json�N���X�Ɉړ�
	file >> json;
}

JsonFile::JsonFile()
{
	json = nullptr;
}

JsonFile::~JsonFile()
{
}

nlohmann::json JsonFile::Import(const std::string& filepath)
{
	std::ifstream file(filepath);
	file >> json;
	return json;
}

void JsonFile::StrWrite(const std::string& jdata)
{
	json = nlohmann::json::parse(jdata);
}

void JsonFile::Save(const std::string& filename)
{
	std::ofstream file(filename);
	file << std::setw(3) << json << std::endl;
}
