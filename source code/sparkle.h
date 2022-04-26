//===========================================
//キラキラエフェクトの処理
//Author:KatoMizuki
//===========================================
#ifndef _SPARKLE_H_
#define _SPARKLE_H_

#include "object.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================
#define SPARKLE_SIZE_RAND	(float (rand() % 40 + 20))		//エフェクトを出すサイズのランダム値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSparkle : public CObject
{
public:
	CSparkle(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//コンストラクタ
	~CSparkle();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSparkle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nNumEffect);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//移動量設定処理

private:
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_pos;						//位置
	std::vector<CEffect3D*> m_pEffect3D;	//エフェクトのポインタ
	int m_nNumEffect;						//エフェクトの数
};

#endif // !_SPARKLE_H_