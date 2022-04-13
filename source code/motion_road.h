//===========================================
//モーション読み込み処理
//Author:加藤瑞葵
//===========================================
#ifndef _MOTION_ROAD_H_
#define _MOTION_ROAD_H_
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MOTION_MAX_KEY_INFO	(128)	//キーの情報の最大値

//================================================
//構造体の定義
//================================================
//キーの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
} KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;						//再生フレーム
	std::vector<KEY> aKey;			//各モデルのキー要素(パーツの最大数)
} KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;										//ループするかどうか
	int nNumKey;									//キーの総数
	KEY_INFO aKeyInfo[MOTION_MAX_KEY_INFO];			//キーの情報
} MOTION_INFO;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CMotionRoad
{
public:
	//モーションを持っているオブジェクトの種類
	typedef enum
	{
		MOTION_HAVE_TYPE_PLAYER = 0,				//プレイヤー
		MOTION_HAVE_TYPE_ENEMY_BEE,					//蜂型の敵
		MOTION_HAVE_TYPE_ENEMY_FAT,					//太型の敵
		MOTION_HAVE_TYPE_ENEMY_BOSS,				//ボスの敵
		MOTION_HAVE_TYPE_MAX
	} MOTION_HAVE_TYPE;

	//プレイヤーのモーションの種類
	typedef enum
	{
		MOTION_PLAYER_TYPE_NEUTRAL = 0,		//ニュートラル
		MOTION_PLAYER_TYPE_MOVE,			//移動
		MOTION_PLAYER_TYPE_SLASH_01,		//斬撃1
		MOTION_PLAYER_TYPE_SLASH_02,		//斬撃2
		MOTION_PLAYER_TYPE_SLASH_03,		//斬撃3
		MOTION_PLAYER_TYPE_SLASH_04,		//斬撃4
		MOTION_PLAYER_TYPE_DAMAGE,			//被ダメージ
		MOTION_PLAYER_TYPE_SPECIAL,			//必殺技1
		MOTION_PLAYER_TYPE_MAGIC_01,		//魔法攻撃1
		MOTION_PLAYER_TYPE_GUARD,			//ガード
		MOTION_PLAYER_TYPE_MAX
	} MOTION_PLAYER_TYPE;

	CMotionRoad();			//コンストラクタ
	~CMotionRoad();			//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	static CMotionRoad *Create(void);								//生成処理
	//モーション情報取得処理
	MOTION_INFO GetMotionInfo(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType);
	//モーション情報->キー情報->再生フレーム取得処理
	int GetMotionKeyInfoFrame(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey);
	//モーション情報->キー情報->位置取得処理
	D3DXVECTOR3 GetMotionKeyInfoPos(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel);
	//モーション情報->キー情報->回転取得処理
	D3DXVECTOR3 GetMotionKeyInfoRot(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel);
	//モーション情報->キー情報->位置と回転設定処理
	void SetMotionKeyInfoPosRot(const MOTION_HAVE_TYPE &motionHaveType, const int &nMotionType, const int &nCntKey, const int &nCntModel, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

private:
	std::vector<MOTION_INFO> m_aInfo[MOTION_HAVE_TYPE_MAX];			//モーション情報
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MOTION_ROAD_H_