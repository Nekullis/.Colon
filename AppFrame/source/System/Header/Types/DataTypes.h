/**
 * @file    DataTypes.h
 * @brief   �����̃f�[�^�^���i�[���邽�߂̃N���X
 * @date    2024�N9��11��
 */

#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <initializer_list>

 /**
  * @class   DataTypes
  * @brief   �����̃f�[�^�^���i�[���A�_��Ɉ������߂̃N���X
  */
class DataTypes
{
private:
    /**
     * @brief   �f�[�^�^�̒�`
     * @details int, float, bool, std::string, std::vector<DataTypes> �̌^���i�[�ł���
     */
    using Value = std::variant<int, float, bool, std::string, std::vector<DataTypes>>;

    /**
     * @typedef DataMap
     * @brief   ��������L�[�ADataTypes��l�Ƃ���f�[�^�}�b�v�̌^��`
     * @details std::unordered_map<std::string, DataTypes> �̃G�C���A�X�ł��B
     *          �L�[�ƒl�̃y�A�������I�ɊǗ����邽�߂Ɏg�p����܂��B
     */
    using DataMap = std::unordered_map<std::string, DataTypes>;

public:
    /**
     * @brief   �f�t�H���g�R���X�g���N�^
     */
    DataTypes() = default;

    /**
    * @brief   ���������X�g����I�u�W�F�N�g���쐬����R���X�g���N�^
    * @param[in] init_list  �L�[��DataTypes�̃y�A�̃��X�g
    * @param    string, DataTypes -> �L�[�A �i�[�������f�[�^
    */
    DataTypes(std::initializer_list<std::pair<std::string, DataTypes>> init_list)
    {
        for (const auto& pair : init_list)
        {
            _data[pair.first] = pair.second;
        }
    }

    /**
     * @brief   int�^�̒l�����R���X�g���N�^
     * @param[in] value  int�^�̒l
     */
    DataTypes(int value)                            : _value(value) {}

    /**
     * @brief   float�^�̒l�����R���X�g���N�^
     * @param[in] value  float�^�̒l
     */
    DataTypes(float value)                          : _value(value) {}

    /**
     * @brief   bool�^�̒l�����R���X�g���N�^
     * @param[in] value  bool�^�̒l
     */
    DataTypes(bool value)                           : _value(value) {}

    /**
    * @brief   std::string�^�̒l�����R���X�g���N�^
    * @param[in] value  std::string�^�̒l
    */
    DataTypes(const std::string& value)             : _value(value) {}

    /**
     * @brief   std::vector<DataTypes>�^�̒l�����R���X�g���N�^
     * @param[in] value  std::vector<DataTypes>�^�̒l
     */
    DataTypes(const std::vector<DataTypes>& value)  : _value(value) {}

    /**
     * @brief   int�^�̒l��ݒ肷��
     * @param[in] value  int�^�̒l
     */
    void Set(int value)                            { _value = value; }

    /**
     * @brief   float�^�̒l��ݒ肷��
     * @param[in] value  float�^�̒l
     */
    void Set(float value)                          { _value = value; }

    /**
     * @brief   bool�^�̒l��ݒ肷��
     * @param[in] value  bool�^�̒l
     */
    void Set(bool value)                           { _value = value; }

    /**
     * @brief   std::string�^�̒l��ݒ肷��
     * @param[in] value  std::string�^�̒l
     */
    void Set(const std::string& value)             { _value = value; }

    /**
     * @brief   std::vector<DataTypes>�^�̒l��ݒ肷��
     * @param[in] value  std::vector<DataTypes>�^�̒l
     */
    void Set(const std::vector<DataTypes>& value)  { _value = value; }

    /**
    * @brief   �i�[����Ă���l���擾����
    * @tparam T   �擾�������^
    * @return     �w�肵���^�̒l
    * @warning    �擾����^���i�[����Ă���^�ƈ�v���Ȃ��ꍇ�A����͖���`�ƂȂ�\��������܂��B
    */
    template<typename T>
    T Get() const 
    { 
        if (std::holds_alternative<T>(_value)) {
            return std::get<T>(_value);
        }
    }

    /**
     * @brief   �L�[�ƒl�̃y�A��ǉ�����
     * @param[in] key    �L�[�ƂȂ镶����
     * @param[in] value  �ǉ�����DataTypes�^�̒l
     */
    void AddData(const std::string& key, const DataTypes& value) 
    {
        _data[key] = value;
    }

    /**
	* @brief            �L�[�ƒl�̃y�A���폜����
	* @param[in] key    �L�[�ƂȂ镶����
    */
	void RemoveData(const std::string& key)
	{
		_data.erase(key);
	}

    /**
	* @brief   object�̉������
    */
	void Clear()
	{
		_data.clear();
	}

    /**
     * @brief   �L�[�ɑΉ�����DataTypes�^�̒l��Ԃ�
     * @param[in] key  �L�[�ƂȂ镶����
     * @return         �L�[�ɑΉ�����DataTypes�^�̒l
     * @note �L�[�����݂��Ȃ��ꍇ�́A�V����DataTypes�I�u�W�F�N�g���쐬�����B
     */
    DataTypes& operator[](const std::string& key) 
    {
        return _data[key];
    }

    /**
     * @brief   �L�[�ɑΉ�����DataTypes�^�̒l��Ԃ��iconst�Łj
     * @param[in] key  �L�[�ƂȂ镶����
     * @return         �L�[�ɑΉ�����const DataTypes�^�̒l
     * @warning �L�[�����݂��Ȃ��ꍇ�A����`����ɂȂ�\��������܂��B
     */
    const DataTypes& operator[](const std::string& key) const
    {
        auto it = _data.find(key);
        if (it != _data.end())
        {
            return it->second;
        }
    }

private:
    Value   _value;     //!< �i�[�����l
    DataMap _data;      //!< �L�[�ƒl�̃y�A��ێ�
};
