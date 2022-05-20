//=============================================================================
//
// トロフィールーム処理 [trophy.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
#include "input_keyboard.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CLetter;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle : public CObject
{
public:
	CTitle(PRIORITY priorty = PRIORITY::NONE);	// デフォルトコンストラクタ
	~CTitle();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

private:
	void SeletMode(void);
	void Tutorial(void);
	void ColUpdate(void);
	void ResultTimer(void);
	void PasWord(void);
	CObject2D *m_click;	// CLICKロゴ
	CObject2D *m_pas_word;// パスワード入力欄
	vector<CObject2D*> m_button;// ボタン
	vector<CObject2D*> m_tutorial;// チュートリアル
	vector<CLetter*> m_pas_font;// パスワード
	vector<wstring> m_key_name;	// パスワード1文字ずつ
	vector<string> m_letter_single;	// パスワード
	string m_pasword;	// パスワード
	int m_count_letter;	// テキストカウント
	int m_result_timer;	// リザルトへのタイマー
	int m_letter_limitl;	// 文字制限
	bool m_fade_flag;	// フェードフラグ
	bool m_tutorial_flag;	// チュートリアルか
	bool m_pas_drop;	// パスワード打ち込み
};

#endif // !_TITLE_H_