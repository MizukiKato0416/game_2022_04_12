//=============================================================================
//
// 背景処理 [bg.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object3D.h"
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBg : public CObject3D
{
public:
	CBg(CObject::PRIORITY Priority = CObject::PRIORITY::POLYGON_3D);	// デフォルトコンストラクタ
	~CBg();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CBg *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, D3DXVECTOR2 uv_move_speed);
	void SetUvMove(const D3DXVECTOR2 speed) { m_uv_move_speed = speed; }
private:
	D3DXVECTOR2 m_uv_move_speed;
	D3DXVECTOR2 m_uv_pos;
};

#endif
