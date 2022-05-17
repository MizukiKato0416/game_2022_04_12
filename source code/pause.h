//===========================================
//ポーズ処理
//Authore:加藤瑞葵
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "object.h"
#include "main.h"

//前方宣言
class CObject2D;
class CManager;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPause : public CObject
{
public:
	CPause(CObject::PRIORITY Priority = CObject::PRIORITY::PAUSE);			//コンストラクタ
	~CPause();										//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetPause(void);
	static bool SetPause(const bool &bPause);
	static CPause *Create(void);

private:
	//画面遷移の選択肢ボタン
	typedef enum
	{
		SELECT_START = 0,		//再開ボタン
		SELECT_EXIT,			//メニューに戻るボタン
		SELECT_MAX
	}SELECT;

	CObject2D *m_apObject2D[SELECT_MAX];	//UI
	CObject2D *m_pObject2D[2];				//ポーズのフレーム
	CObject2D *m_pPauseButton;				// ポーズボタン
	static bool m_bPause;					//ポーズ画面かどうか
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PAUSE_H_