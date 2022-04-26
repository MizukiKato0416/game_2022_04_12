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
		TRAJECTORY_PLAYER,		//プレイヤーの軌跡
		MAX
	};

	CEffect3D(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//コンストラクタ
	~CEffect3D();										//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, const EFFECT3D_TYPE &type);

	//減算合成設定処理
	void SetAlphaBlendSubtraction(bool bAlphaBlendSubtraction) { m_bAlphaBlendSubtraction = bAlphaBlendSubtraction; }

private:
	EFFECT3D_TYPE m_type;			//エフェクトの種類
	CControl *m_pControl;			//コントロールクラスのポインタ
	bool m_bAlphaBlendSubtraction;	//減算合成するかどうか
};

#endif // !_EFFECT3D_H_