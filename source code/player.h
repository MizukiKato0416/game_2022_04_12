//===========================================
//プレイヤー処理
//Author:加藤瑞葵
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"

//前方宣言
class CModel;
class CMotionPlayer;

//================================================
//マクロ定義
//================================================
#define MAX_PLAYER_MODEL					(5)		//モデルの数

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayer : public CObject
{
public:

	//メンバ関数
	CPlayer(CObject::PRIORITY Priority = CObject::PRIORITY::PLAYER);				//コンストラクタ
	~CPlayer();												//デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

	void SetModelPos(const int &nCntModel, const D3DXVECTOR3 &pos);							//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(const int &nCntModel);											//モデルの位置取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }												//プレイヤーの向き取得処理
	void SetModelRot(const int &nCntModel, const D3DXVECTOR3 &rot);							//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(const int &nCntModel);											//モデルの向き取得処理
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }								//移動量設定処理
	static void CPlayer::Collision(CObject *&pSubjectObject, const float &fObjRadius);		//当たり判定処理
	bool CPlayer::CollisionOnly(CObject *&pSubjectObject, const float &fObjRadius);			//衝突判定のみの処理
	bool GetShot(void) { return m_bShot; }													//発射取得処理

private:
	//メンバ関数
	void Move(void);								//移動処理
	void Rotate(void);								//回転処理
	void Jump(void);								//ジャンプ処理

	//メンバ変数
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_posOld;							//1フレーム前の位置
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	D3DXVECTOR3	m_size;								//サイズ
	D3DXVECTOR3 m_rot;								//向き
	CModel *m_apModel[MAX_PLAYER_MODEL];			//モデルのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	CModel *m_pParent;								//親モデルへのポインタ
	CMotionPlayer *m_pMotionPlayer;					//モーションプレイヤーのポインタ
	float m_fObjectiveRot;							//目的の向き
	float m_fNumRot;								//向きを変える量
	bool m_bRotate;									//回転しているかどうか
	bool m_bShot;									//発射したかどうか
	float m_fJump;									//ジャンプ力
};

#endif // !_PLAYER_H_