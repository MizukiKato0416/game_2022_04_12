//=============================================================================
//
// バナナクラス処理 [banana.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _BANANA_H_
#define _BANANA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "happening.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBanana : public CHappenig
{
public:
	CBanana(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// デフォルトコンストラクタ
	~CBanana();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CBanana *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 回転
	int m_nCntSlow;		//スローになる時間カウント用
	bool m_bHitPlayer;	//プレイヤーに当たったかどうか
};

#endif
