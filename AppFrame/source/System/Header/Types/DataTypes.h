/**
 * @file    DataTypes.h
 * @brief   複数のデータ型を格納するためのクラス
 * @date    2024年9月11日
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
  * @brief   複数のデータ型を格納し、柔軟に扱うためのクラス
  */
class DataTypes
{
private:
    /**
     * @brief   データ型の定義
     * @details int, float, bool, std::string, std::vector<DataTypes> の型を格納できる
     */
    using Value = std::variant<int, float, bool, std::string, std::vector<DataTypes>>;

    /**
     * @typedef DataMap
     * @brief   文字列をキー、DataTypesを値とするデータマップの型定義
     * @details std::unordered_map<std::string, DataTypes> のエイリアスです。
     *          キーと値のペアを効率的に管理するために使用されます。
     */
    using DataMap = std::unordered_map<std::string, DataTypes>;

public:
    /**
     * @brief   デフォルトコンストラクタ
     */
    DataTypes() = default;

    /**
    * @brief   初期化リストからオブジェクトを作成するコンストラクタ
    * @param[in] init_list  キーとDataTypesのペアのリスト
    * @param    string, DataTypes -> キー、 格納したいデータ
    */
    DataTypes(std::initializer_list<std::pair<std::string, DataTypes>> init_list)
    {
        for (const auto& pair : init_list)
        {
            _data[pair.first] = pair.second;
        }
    }

    /**
     * @brief   int型の値を持つコンストラクタ
     * @param[in] value  int型の値
     */
    DataTypes(int value)                            : _value(value) {}

    /**
     * @brief   float型の値を持つコンストラクタ
     * @param[in] value  float型の値
     */
    DataTypes(float value)                          : _value(value) {}

    /**
     * @brief   bool型の値を持つコンストラクタ
     * @param[in] value  bool型の値
     */
    DataTypes(bool value)                           : _value(value) {}

    /**
    * @brief   std::string型の値を持つコンストラクタ
    * @param[in] value  std::string型の値
    */
    DataTypes(const std::string& value)             : _value(value) {}

    /**
     * @brief   std::vector<DataTypes>型の値を持つコンストラクタ
     * @param[in] value  std::vector<DataTypes>型の値
     */
    DataTypes(const std::vector<DataTypes>& value)  : _value(value) {}

    /**
     * @brief   int型の値を設定する
     * @param[in] value  int型の値
     */
    void Set(int value)                            { _value = value; }

    /**
     * @brief   float型の値を設定する
     * @param[in] value  float型の値
     */
    void Set(float value)                          { _value = value; }

    /**
     * @brief   bool型の値を設定する
     * @param[in] value  bool型の値
     */
    void Set(bool value)                           { _value = value; }

    /**
     * @brief   std::string型の値を設定する
     * @param[in] value  std::string型の値
     */
    void Set(const std::string& value)             { _value = value; }

    /**
     * @brief   std::vector<DataTypes>型の値を設定する
     * @param[in] value  std::vector<DataTypes>型の値
     */
    void Set(const std::vector<DataTypes>& value)  { _value = value; }

    /**
    * @brief   格納されている値を取得する
    * @tparam T   取得したい型
    * @return     指定した型の値
    * @warning    取得する型が格納されている型と一致しない場合、動作は未定義となる可能性があります。
    */
    template<typename T>
    T Get() const 
    { 
        if (std::holds_alternative<T>(_value)) {
            return std::get<T>(_value);
        }
    }

    /**
     * @brief   キーと値のペアを追加する
     * @param[in] key    キーとなる文字列
     * @param[in] value  追加するDataTypes型の値
     */
    void AddData(const std::string& key, const DataTypes& value) 
    {
        _data[key] = value;
    }

    /**
	* @brief            キーと値のペアを削除する
	* @param[in] key    キーとなる文字列
    */
	void RemoveData(const std::string& key)
	{
		_data.erase(key);
	}

    /**
	* @brief   objectの解放処理
    */
	void Clear()
	{
		_data.clear();
	}

    /**
     * @brief   キーに対応するDataTypes型の値を返す
     * @param[in] key  キーとなる文字列
     * @return         キーに対応するDataTypes型の値
     * @note キーが存在しない場合は、新しいDataTypesオブジェクトが作成される。
     */
    DataTypes& operator[](const std::string& key) 
    {
        return _data[key];
    }

    /**
     * @brief   キーに対応するDataTypes型の値を返す（const版）
     * @param[in] key  キーとなる文字列
     * @return         キーに対応するconst DataTypes型の値
     * @warning キーが存在しない場合、未定義動作になる可能性があります。
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
    Value   _value;     //!< 格納される値
    DataMap _data;      //!< キーと値のペアを保持
};
