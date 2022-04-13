//=============================================================================
//xファイルロード処理
//Author:加藤瑞葵
//=============================================================================
#ifndef _X_LOAD_H_
#define _X_LOAD_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CXload
{
public:
	//タイプ
	typedef enum
	{
		X_TYPE_PLAYER_BODY = 0,					//プレイヤーの体
		X_TYPE_PLAYER_HEAD,						//プレイヤーの頭
		X_TYPE_PLAYER_ARM_R,					//プレイヤーの右上腕
		X_TYPE_PLAYER_FRONTARM_R,				//プレイヤーの右腕
		X_TYPE_PLAYER_HAND_R,					//プレイヤーの右手
		X_TYPE_PLAYER_ARM_L,					//プレイヤーの左上腕
		X_TYPE_PLAYER_FRONTARM_L,				//プレイヤーの左腕
		X_TYPE_PLAYER_HAND_L,					//プレイヤーの左手
		X_TYPE_PLAYER_WAIST,					//プレイヤーの腰
		X_TYPE_PLAYER_THIGH_R,					//プレイヤーの右腿
		X_TYPE_PLAYER_LEG_R,					//プレイヤーの右脚
		X_TYPE_PLAYER_FOOT_R,					//プレイヤーの右足
		X_TYPE_PLAYER_THIGH_L,					//プレイヤーの左腿
		X_TYPE_PLAYER_LEG_L,					//プレイヤーの左脚
		X_TYPE_PLAYER_FOOT_L,					//プレイヤーの左足
		X_TYPE_PLAYER_SWORD,					//プレイヤーの剣
		X_TYPE_WALL_01,							//壁01
		X_TYPE_PILLER_01,						//柱01
		X_TYPE_BEE,								//蜂
		X_TYPE_ENEMY_FAT_BODY,					//太型敵の体
		X_TYPE_ENEMY_FAT_HEAD,					//太型敵の頭
		X_TYPE_ENEMY_FAT_ARM_R,					//太型敵の右腕
		X_TYPE_ENEMY_FAT_ARM_L,					//太型敵の左腕
		X_TYPE_ENEMY_FAT_LEG,					//太型敵の足
		X_TYPE_ENEMY_BOSS_BODY,					//ボスの体
		X_TYPE_ENEMY_BOSS_HEAD,					//ボスの頭
		X_TYPE_ENEMY_BOSS_ARM_R,				//ボスの右腕
		X_TYPE_ENEMY_BOSS_ARM_L,				//ボスの左腕
		X_TYPE_ENEMY_BOSS_LEG,					//ボスの足
		X_TYPE_MAX								//最大数
	} X_TYPE;

	CXload();									//コンストラクタ
	~CXload();									//デストラクタ

	void Init(void);									// テクスチャの生成
	LPD3DXMESH GetMesh(const X_TYPE &type);					// メッシュの割り当て
	LPD3DXBUFFER GetBuffMat(const X_TYPE &type);				// マテリアルの割り当て
	DWORD GetNumMat(const X_TYPE &type);						// マテリアル数の割り当て
	X_TYPE GetType(const int &nType) { return (X_TYPE)nType; }	// タイプ取得処理
	void Uninit(void);									// 終了
private:
	LPD3DXMESH m_apMesh[X_TYPE_MAX];			//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_apBuffMat[X_TYPE_MAX];		//マテリアル(材質情報)へのポインタ
	DWORD m_aNumMat[X_TYPE_MAX];				//マテリアル数
};

#endif