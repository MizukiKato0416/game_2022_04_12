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

	CUi(CObject::PRIORITY Priority = CObject::PRIORITY::UI);	//コンストラクタ
	~CUi();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nPriolty, const TYPE &type);
	TYPE GetUIType(void) { return m_type; }		//種類取得処理

private:
	TYPE m_type;						// UIの種類
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	CControl *m_pControl;
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_size;					//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_H_