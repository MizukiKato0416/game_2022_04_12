//===========================================
//UI処理
//Authore:加藤瑞葵
//===========================================
#ifndef _UI_H_
#define _UI_H_
#include "object2D.h"

//前方宣言
class CControl;

//================================================
//マクロ定義
//================================================
#define UI_CROSS_SIZE		(40.0f)		//バツUIのサイズ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CUi : public CObject2D
{
public:
	//UIの種類
	enum class TYPE
	{
		NONE = 0,
		PRESS_START,	//PRESSSTART
		MAX
	};

	CUi(int nPriority = PRIORITY_UI);	//コンストラクタ
	~CUi();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty, TYPE type);
	TYPE GetUIType(void) { return m_type; }		//種類取得処理

private:
	TYPE m_type;						// UIの種類
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	CControl *m_pControl;
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_H_