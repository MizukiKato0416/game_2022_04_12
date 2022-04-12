//===========================================
//パーティクル処理
//Author:加藤瑞葵
//===========================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_
#include "billboard.h"

//前方宣言
class CControl;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEffect3D : public CBillboard
{
public:
	//エフェクトの種類
	enum class EFFECT3D_TYPE
	{
		NONE = 0,
		CHECK,			//チェックポイント
		HIT,			//ヒットエフェクト
		THUNDER,		//雷
		FLASH,			//閃光
		FIRE,			//炎
		EXPLOSION,		//爆発
		MAX
	};

	CEffect3D(int nPriority = PRIORITY_EFFECT3D);		//コンストラクタ
	~CEffect3D();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, EFFECT3D_TYPE type);

private:
	EFFECT3D_TYPE m_type;		//エフェクトの種類
	CControl *m_pControl;		//コントロールクラスのポインタ
};

#endif // !_EFFECT3D_H_