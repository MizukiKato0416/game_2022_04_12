//===========================================
//飛行機雲の処理
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_CLOUD_H_
#define _AIRPLANE_CLOUD_H_

#include "object.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================
#define AIRPLANE_CLOUD_SIZE_RAND	(float (rand() % 40 + 20))		//エフェクトを出すサイズのランダム値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CAirplaneCloud : public CObject
{
public:
	CAirplaneCloud(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//コンストラクタ
	~CAirplaneCloud();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAirplaneCloud *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 move, const int nNumEffect);

	void SetMove(const D3DXVECTOR3 move) { m_move = move; }	//移動量設定処理

private:
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_pos;						//位置
	std::vector<CEffect3D*> m_pEffect3D;	//エフェクトのポインタ
	int m_nNumEffect;						//エフェクトの数
};

#endif // !_AIRPLANE_CLOUD_H_