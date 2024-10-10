//----------------------------------------------------------------------
// @filename SoundServer.cpp
// @author: Saito Ko
// @explanation
// 登録したSEやBGMなどを管理するクラス
//----------------------------------------------------------------------
#include "../../Header/Sound/SoundItem.h"
#include "../../Header/Sound/SoundServer.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
SoundServer::SoundServer() {
	_isUpdate = false;
	_cntOneShot = 0;
	_SeVolume = _VoiceVolume = 255;
	_BgmVolume = 150;
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
SoundServer::~SoundServer() {
	Clear();
}

//----------------------------------------------------------------------
// @brief サーバー内のサウンドを全て削除
// @return なし
//----------------------------------------------------------------------
void SoundServer::Clear() {
	for (auto&& e : _v) {
		delete e.second;
	}
	for (auto&& e : _vAdd) {
		delete e.second;
	}
	for (auto&& e : _vDel) {
		delete e.second;
	}
	_v.clear();
	_vAdd.clear();
	_vDel.clear();
}

//----------------------------------------------------------------------
// @brief サウンドを追加
// @param snd: 追加するサウンド
// @return なし
//----------------------------------------------------------------------
void SoundServer::Add(SoundItemOneShot* snd) {
	std::string name = "__ONESHOT_SOUND_" + std::to_string(_cntOneShot);
	_cntOneShot++;
	Add(name, snd);
	snd->Play();		// OneShotは登録した瞬間再生する
}

//----------------------------------------------------------------------
// @brief サウンドを追加
// @param name: サウンドの名前
// @param snd: 追加するサウンド
// @return なし
//----------------------------------------------------------------------
void SoundServer::Add(std::string name, SoundItemOneShot* snd) {
	Add(name, static_cast<SoundItemBase*>(snd));
	snd->Play();		// OneShotは登録した瞬間再生する
}

//----------------------------------------------------------------------
// @brief サウンドを追加
// @param name: サウンドの名前
// @param snd: 追加するサウンド
// @return なし
//----------------------------------------------------------------------
void SoundServer::Add(std::string name, SoundItemBase* snd) {
	if (_isUpdate) {
		_vAdd[name] = snd;
	}
	else {
		_v[name] = snd;
	}
	snd->SetSoundServer(this);
}

//----------------------------------------------------------------------
// @brief サウンドを削除
// @param snd: 削除するサウンド
// @return true: 成功
//----------------------------------------------------------------------
bool SoundServer::Del(SoundItemBase* snd) {
	for (auto&& e : _v) {
		if (e.second == snd) {
			if (_isUpdate) {
				_vDel[e.first] = e.second;
			}
			else {
				std::string name = e.first;
				delete _v[name];
				_v.erase(name);
			}
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
// @brief サウンドを削除
// @param name: 削除するサウンドの名前
// @return true: 成功
//----------------------------------------------------------------------
bool SoundServer::Del(std::string name) {
	if (_v.count(name) > 0) {
		return Del(_v[name]);
	}
	return false;
}

//----------------------------------------------------------------------
// @brief サウンドを取得
// @param name: サウンドの名前
// @return サウンド
//----------------------------------------------------------------------
SoundItemBase* SoundServer::Get(std::string name) {
	if (_v.count(name) > 0) { return _v[name]; }
	return NULL;
}

//----------------------------------------------------------------------
// @brief サウンドを検索
// @param name: サウンドの名前
// @return サウンド
//----------------------------------------------------------------------
SoundItemBase* SoundServer::Search(std::string name) {
	if (GetASyncLoadNum() == 0) {
		auto itr = _v.find(name);
		if (itr != _v.end()) {
			return itr->second;
		}
#ifdef _DEBUG
		else {
			//エラー
			//ファイルが無い 又は 読み込まれていません
			std::string errar = "ファイルが無い 又は 読み込まれていません";
			MessageBox(NULL, errar.c_str(), "エラー", MB_OK);
		}
#endif
	}
#ifdef _DEBUG
	else {
		//エラー
		//非同期読み込み中です。
		std::string errar = "非同期読み込み中です。";
		MessageBox(NULL, errar.c_str(), "エラー", MB_OK);
	}
#endif
	return nullptr;
};

//----------------------------------------------------------------------
// @brief サウンドを再生
// @param name: サウンドの名前
// @return true: 成功
//----------------------------------------------------------------------
bool SoundServer::DirectPlay(std::string name) {
	auto playSound = Search(name);
	if (playSound) {
		playSound->Play();
		return true;
	}
	return false;
};

//----------------------------------------------------------------------
// @brief サウンドをランダム再生
// @param name: サウンドの名前
// @return true: 成功
//----------------------------------------------------------------------
bool SoundServer::RandomPlay(std::vector<std::string> name) {
	int random = rand() % name.size();
	if (DirectPlay(name.at(random))) {
		return true;
	}
	return false;
};

//----------------------------------------------------------------------
// @brief 再生中のサウンドを検索
// @return 再生中のサウンド
//----------------------------------------------------------------------
std::vector<SoundItemBase*> SoundServer::NowPlayingSearch() {
	std::vector<SoundItemBase*> nowPlaying;
	for (auto&& e : _v) {
		if (e.second->IsPlay()) {
			nowPlaying.push_back(e.second);
		}
	}
	return nowPlaying;
};

//----------------------------------------------------------------------
// @brief 再生中のサウンドを検索
// @param type: サウンドの種類
// @return 再生中のサウンド
//----------------------------------------------------------------------
std::vector<SoundItemBase*> SoundServer::NowPlayingSearchType(SoundItemBase::TYPE type) {
	std::vector<SoundItemBase*> nowPlaying;
	for (auto&& e : _v) {
		if (e.second->GetType() == type && e.second->IsPlay()) {
			nowPlaying.push_back(e.second);
		}
	}
	return nowPlaying;
};

//----------------------------------------------------------------------
// @brief 全てのサウンドを停止
// @return なし
//----------------------------------------------------------------------
void SoundServer::StopAll() {
	auto stopSound = NowPlayingSearch();
	for (auto&& e : stopSound) {
		e->Stop();
	}
};

//----------------------------------------------------------------------
// @brief タイプのサウンドを停止
// @param type: サウンドの種類
// @return なし
//----------------------------------------------------------------------
void SoundServer::StopType(SoundItemBase::TYPE type) {
	auto stopSound = NowPlayingSearchType(type);
	for (auto&& e : stopSound) {
		if (e->GetFade() != SoundItemBase::FADE_OUT) {
			e->Stop();
		}
	}
}

//----------------------------------------------------------------------
// @brief BGMをフェードアウト
// @param time: フェードアウト時間
// @return なし
//----------------------------------------------------------------------
void SoundServer::BgmFadeOut(int time) {
	auto fadeSound = NowPlayingSearchType(SoundItemBase::TYPE::BGM);
	for (auto&& e : fadeSound) {
		e->SetFade(SoundItemBase::FADE_OUT,time);
	}
};

//----------------------------------------------------------------------
// @brief BGMをフェードイン
// @param name: サウンドの名前
// @param time: フェードイン時間
// @return なし
//----------------------------------------------------------------------
void SoundServer::BgmFadeIn(std::string name,int time){
	auto sound = Search(name);
	//もしかしたらここでサウンドの音量を0にしないといけないかも 1Fずれるかも
	sound->SetFade(SoundItemBase::FADE_IN,time); 
	sound->Play();
};

//----------------------------------------------------------------------
// @brief 更新
// @return なし
//----------------------------------------------------------------------
void SoundServer::Update() {
	// 追加リストのものを追加
	for (auto&& e : _vAdd) { Add(e.first, e.second); }
	_vAdd.clear();

	// Updateを回す
	_isUpdate = true;
	for (auto&& e : _v) {
		e.second->Update();
	}
	_isUpdate = false;

	// 削除リストのものを削除
	for (auto&& e : _vDel) { Del(e.second); }
	_vDel.clear();
}

//----------------------------------------------------------------------
// @brief SEの音量を設定
// @param volume: 音量
// @return なし
//----------------------------------------------------------------------
void SoundServer::SetBgmVolume(int volume) { 
	_BgmVolume = volume; 
	auto bgmList = NowPlayingSearchType(SoundItemBase::TYPE::BGM);
	for(auto&& bgm : bgmList){
	   bgm->SetVolume();
	}
}