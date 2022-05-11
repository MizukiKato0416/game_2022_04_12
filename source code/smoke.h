//===========================================
//煙エフェクトの処理
//Author:KatoMizuki
//===========================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "object.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSmoke : public CObject
{
public:
	CSmoke(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//コンストラクタ
	~CSmoke();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSmoke *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &move, const D3DXVECTOR3 &addRot,
		                  const D3DXVECTOR3 &addSize, const float &fSubtractAlpha);
	//移動量設定処理
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }
	//移動量取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_addRot;					//回転加算値
	D3DXVECTOR3 m_addSize;					//サイズ加算値
	CEffect3D *m_pEffect3D;					//エフェクトのポインタ
	float m_fSubtractAlpha;					//α値減算値
};

#endif // !_SMOKE_H_