//===========================================
//フェード処理
//Author:加藤瑞葵
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CFade : public CObject2D
{
public:
	//フェードの種類
	typedef enum
	{
		FADE_NONE = 0,		//何もしていない
		FADE_IN,			//フェードイン
		FADE_OUT,			//フェードアウト
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);		//コンストラクタ
	~CFade();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	FADE GetFade(void);
	void SetFade(CManager::MODE modeNext);
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE modeNext);

private:
	FADE m_fade;							//フェードの状態
	CManager::MODE m_modeNext;				//次の画面(モード)
	D3DXCOLOR m_color;						//フェードの色
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_FADE_H_