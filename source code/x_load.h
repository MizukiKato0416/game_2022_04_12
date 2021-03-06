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
		X_TYPE_PLAYER_ARM_R,					//プレイヤーの右腕
		X_TYPE_PLAYER_ARM_L,					//プレイヤーの左腕
		X_TYPE_PLAYER_LEG_R,					//プレイヤーの右足
		X_TYPE_PLAYER_LEG_L,					//プレイヤーの左足
		X_TYPE_PLAYER_GIRL_BODY,				//プレイヤーガールの体
		X_TYPE_PLAYER_GIRL_ARM_R,				//プレイヤーガールの右腕
		X_TYPE_PLAYER_GIRL_ARM_L,				//プレイヤーガールの左腕
		X_TYPE_PLAYER_GIRL_LEG_R,				//プレイヤーガールの右足
		X_TYPE_PLAYER_GIRL_LEG_L,				//プレイヤーガールの左足
		X_TYPE_THORN,							//棘
		X_TYPE_CLOUD,							//雲
		X_TYPE_CLOUD_GRAY,						//雷雲
		X_TYPE_GROUND,							//地面
		X_TYPE_TRAMPLINE,						//トランポリン
		X_TYPE_FAN,								//扇風機
		X_TYPE_AIRPLANE,						//飛行機
		X_TYPE_STARRING,						//六芒星
		X_TYPE_REDBULL,							//レッドブル
		X_TYPE_START,							//スタート地点
		X_TYPE_ROCKET,							//ロケット
		X_TYPE_BANANA,							//バナナ
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