#pragma once

#include <string>
#include <nlohmann/json.hpp>

class JsonFile
{
public:
	JsonFile();
	JsonFile(const std::string& filepath);
	virtual ~JsonFile();

	void Init() { json = nullptr; }
	//読み込み・書き込み
	//このクラスのjsonデータに外部のjsonファイルを読み込み
	nlohmann::json Import(const std::string& filepath);
	//jsonデータの中の一要素を指定したメンバ変数に代入
	template <typename T>
	void Read(const std::string& jmem, T& mem);
	//他クラスで変更されたデータをこのクラスで保持しているjsonデータに上書きもしくは追加する
	//std::string jdata = R"({ ~通常のjsonファイルの記述~ })"; 　　をつくって記述する
	void StrWrite(const std::string& jdata);
	template <typename T>
	// このクラスで保有しているjsonファイルに一要素を上書きもしくは追加
	void JsonWrite(const std::string& name, const T& variable);
	void Save(const std::string& filename);
	nlohmann::json GetJson() { return json; }
protected:
	nlohmann::json json;
};

template<typename T>
inline void JsonFile::Read(const std::string& jmem, T& mem)
{
	json.at(jmem).get_to(mem);
}

template<typename T>
inline void JsonFile::JsonWrite(const std::string& name, const T& variable)
{
	json[name] = variable;
}

