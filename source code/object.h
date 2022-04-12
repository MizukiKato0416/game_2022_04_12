//===========================================
//シーン処理
//Author:加藤瑞葵
//===========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CObject
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,			//なし
		PRIORITY_PLAYER,			//プレイヤー
		PRIORITY_MODEL,				//モデル
		PRIORITY_ENEMY,				//敵
		PRIORITY_LOCK_ON,			//ロックオン
		PRIORITY_ENEMY_BULLET,		//敵の弾
		PRIORITY_POLYGON_3D,		//3Dポリゴン
		PRIORITY_SHADOW,			//影
		PRIORITY_MESH_FIELD,		//メッシュフィールド
		PRIORITY_CHECK_CIRCLE,		//チェックポイント
		PRIORITY_WARP_CIRCLE,		//ワープポイント
		PRIORITY_MAGIC,				//魔法
		PRIORITY_TRAJECTORY,		//メッシュ軌跡
		PRIORITY_EXPLOSION,			//爆発
		PRIORITY_SPARK,				//火の粉
		PRIORITY_EFFECT3D,			//パーティクル
		PRIORITY_FIRE_BALL,			//炎の弾
		PRIORITY_EXCLAMATION_MARK,	//ビックリマーク
		PRIORITY_UI,				//UI
		PRIORITY_RANKING,			//ランキング
		PRIORITY_MAP,				//マップ
		PRIORITY_MASK,				//マスク
		PRIORITY_PAUSE,				//ポーズ
		PRIORITY_FADE,				//フェード
		PRIORITY_MAX
	} PRIORITY;

	enum class OBJTYPE
	{
		NONE = 0,			//なし
		EFFECT_3D,			//3Dエフェクト
		TRAJECTORY,			//メッシュ軌跡
		FLOOR,				//床
		MAGIC_CIRCLE,		//魔法陣
		MAGIC_THUNDER,		//雷魔法
		MAGIC_FIRE,			//炎魔法
		WARP_CIRCLE,		//ワープ魔法陣
		CHECK_CIRCLE,		//チェックポイント魔法陣
		PLAYER,				//プレイヤー
		MODEL,				//モデル
		ENEMY,				//敵
		ENEMY_BEE,			//敵(蜂)
		ENEMY_FAT,			//敵(太)
		ENEMY_BOSS,			//敵(ボス)
		BULLET_ENEMY,		//敵の弾
		FIRE_BALL,			//炎の弾
		EXPLOSION,			//爆発
		SPARK,				//火の粉
		GUARD,				//ガードエフェクト
		GAUGE,				//ゲージ
		UI,					//UI
		MAP,				//マップ
		POLYGON_3D,			//3Dポリゴン
		EXCLAMATION_MARK,	//ビックリマーク
		SHADOW,				//影
		MAX
	};

	CObject(int nPriority = PRIORITY_NONE);			//コンストラクタ
	virtual ~CObject();								//デストラクタ

	//メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);			//オブジェクトタイプ設定処理
	OBJTYPE GetObjType(void);					//オブジェクトタイプ取得処理
	CObject *GetObjNext(CObject *pObject);		//引数のオブジェクトの次のオブジェクト情報取得処理
	static CObject *GetTopObj(int nPriority);	//引数のプライオリティの先頭オブジェクト取得処理
	D3DXVECTOR3 GetPos(void);					//位置取得処理
	void SetPos(D3DXVECTOR3 pos);				//位置設定処理
	void SetPosOld(D3DXVECTOR3 posOld);			//1フレーム前の位置設定処理
	D3DXVECTOR3 GetPosOld(void);				//1フレーム前の位置取得処理
	D3DXVECTOR3 GetSize(void);					//サイズ取得処理
	void SetSize(D3DXVECTOR3 size);				//サイズ設定処理
	void SetPriority(int nPriority);			//プライオリティ設定処理

protected:
	void Release(void);

private:
	static CObject *m_pTop[PRIORITY_MAX];	//先頭オブジェクトのポインタ
	static CObject *m_pCur[PRIORITY_MAX];	//現在(一番後ろ)オブジェクトのポインタ
	CObject *m_pPrev;						//前のオブジェクトへのポインタ
	CObject *m_pNext;						//次のオブジェクトへのポインタ
	int m_nPriority;						//優先順位の番号
	OBJTYPE m_objType;						//オブジェクトの種類
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3 m_posOld;					//1フレーム前のポリゴンの位置
	D3DXVECTOR3 m_size;						//ポリゴンのサイズ
	bool m_bDeath;							//死亡フラグ
};

#endif // !_OBJECT_H_