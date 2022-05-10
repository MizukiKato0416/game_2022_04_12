//=============================================================================
//
// ハプニング親クラス処理 [happening.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _HAPPENING_H_
#define _HAPPENING_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModelSingle;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CHappenig : public CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class HAPPENING_TYPE
	{
		NONE = 0,		// 無し
		TRAMPOLINE,		// トランポリン
		FAN,			// 扇風機
		REDBULL,		// レッドブル
		STARRING,		// 六芒星
		AIRPLANE,		// 飛行機
		GIRL,			// ロキ子
		MAX,			// 総数
	};

	CHappenig(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// デフォルトコンストラクタ
	~CHappenig();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }	// セッター
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }	// セッター
	void SetModel(CModelSingle *model) { m_model = model; }	// セッター
	CModelSingle *GetModel(void) { return m_model; }		// ゲッター
	bool HitPlayer(void);									//プレイヤーとの当たり判定
	void SetCameraZoom(void);								//カメラがプレイヤーをズームする
private:
	CModelSingle *m_model;	// モデル
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
};

#endif