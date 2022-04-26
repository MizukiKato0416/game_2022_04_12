//=============================================================================
//
// スターリングクラス処理 [starring.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _STARRING_H_
#define _STARRING_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object.h"
#include "happening.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStarring : public CHappenig
{
public:
	CStarring(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// デフォルトコンストラクタ
	~CStarring();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CStarring *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 回転
};

#endif