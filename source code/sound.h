//===========================================
//サウンド処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSound
{
public:
	CSound();				//コンストラクタ
	~CSound();				//デストラクタ

	//サウンドファイル
	enum class SOUND_LABEL
	{
		CANCEL_SE = 0,			//キャンセルSE
		DECIDE_SE,				//決定SE
		CURSOR_SE,				//カーソルのSE
		PAUSE_SE,				//ポーズSE
		GAMECLEAR_SE,			//ゲームクリアSE
		GAMEOVER_SE,			//ゲームオーバーSE
		SLASH_SE,				//斬撃SE
		GUARD_SE,				//ガードSE
		MAGIC_SE,				//魔法SE
		SPECIAL_SE,				//必殺技SE
		TITLE_BGM,				//タイトルBGM
		MENU_BGM,				//メニューBGM
		GAME_BGM,				//ゲーム内BGM
		RESULT_BGM,				//リザルトBGM
		MAX,
	};

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	HRESULT Play(const SOUND_LABEL &label);
	void Stop(const SOUND_LABEL &label);
	void Stop(void);
	void ControllVoice(const SOUND_LABEL &label, const float &fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	//音量調整

private:
	//パラメーター構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[(int)SOUND_LABEL::MAX] = {};			// ソースボイス
	BYTE *m_apDataAudio[(int)SOUND_LABEL::MAX] = {};							// オーディオデータ
	DWORD m_asizeAudio[(int)SOUND_LABEL::MAX] = {};							// オーディオデータサイズ

	static PARAM m_aParam[(int)SOUND_LABEL::MAX];								// 各音素材のパラメータ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SOUND_H_