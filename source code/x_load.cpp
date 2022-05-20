//=============================================================================
//Xファイル読み込み処理
//Author:加藤瑞葵
//=============================================================================
#include "x_load.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CXload::CXload()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CXload::~CXload()
{

}

//=============================================================================
//テクスチャの生成
//=============================================================================
void CXload::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得する

	//Xファイル読み込み

	//プレイヤーの体
	D3DXLoadMeshFromX("data/MODEL/player_01/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_BODY], &m_apMesh[X_TYPE_PLAYER_BODY]);

	//プレイヤーの右腕
	D3DXLoadMeshFromX("data/MODEL/player_01/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_R], &m_apMesh[X_TYPE_PLAYER_ARM_R]);

	//プレイヤーの左腕
	D3DXLoadMeshFromX("data/MODEL/player_01/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_ARM_L], &m_apMesh[X_TYPE_PLAYER_ARM_L]);

	//プレイヤーの右足
	D3DXLoadMeshFromX("data/MODEL/player_01/legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_R], &m_apMesh[X_TYPE_PLAYER_LEG_R]);

	//プレイヤーの左足
	D3DXLoadMeshFromX("data/MODEL/player_01/legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_LEG_L], &m_apMesh[X_TYPE_PLAYER_LEG_L]);

	//プレイヤーガールの体
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_BODY], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_BODY], &m_apMesh[X_TYPE_PLAYER_GIRL_BODY]);

	//プレイヤーガールの右腕
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_R], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_R]);

	//プレイヤーガールの左腕
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_ARM_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_ARM_L], &m_apMesh[X_TYPE_PLAYER_GIRL_ARM_L]);

	//プレイヤーガールの右足
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_legsR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_R], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_R], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_R]);

	//プレイヤーガールの左足
	D3DXLoadMeshFromX("data/MODEL/player_01/girl_legsL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_PLAYER_GIRL_LEG_L], NULL, &m_aNumMat[X_TYPE_PLAYER_GIRL_LEG_L], &m_apMesh[X_TYPE_PLAYER_GIRL_LEG_L]);

	//棘
	D3DXLoadMeshFromX("data/MODEL/stage/thorn.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_THORN], NULL, &m_aNumMat[X_TYPE_THORN], &m_apMesh[X_TYPE_THORN]);

	//雲
	D3DXLoadMeshFromX("data/MODEL/stage/cloud.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_CLOUD], NULL, &m_aNumMat[X_TYPE_CLOUD], &m_apMesh[X_TYPE_CLOUD]);

	//トランポリン
	D3DXLoadMeshFromX("data/MODEL/stage/trampoline.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_TRAMPLINE], NULL, &m_aNumMat[X_TYPE_TRAMPLINE], &m_apMesh[X_TYPE_TRAMPLINE]);

	//扇風機
	D3DXLoadMeshFromX("data/MODEL/stage/fan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_FAN], NULL, &m_aNumMat[X_TYPE_FAN], &m_apMesh[X_TYPE_FAN]);

	//飛行機
	D3DXLoadMeshFromX("data/MODEL/stage/airplane.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_AIRPLANE], NULL, &m_aNumMat[X_TYPE_AIRPLANE], &m_apMesh[X_TYPE_AIRPLANE]);

	//六芒星
	D3DXLoadMeshFromX("data/MODEL/stage/starring.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_STARRING], NULL, &m_aNumMat[X_TYPE_STARRING], &m_apMesh[X_TYPE_STARRING]);

	//レッドブル
	D3DXLoadMeshFromX("data/MODEL/stage/redbull.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_REDBULL], NULL, &m_aNumMat[X_TYPE_REDBULL], &m_apMesh[X_TYPE_REDBULL]);

	//スタート地点
	D3DXLoadMeshFromX("data/MODEL/stage/start.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_START], NULL, &m_aNumMat[X_TYPE_START], &m_apMesh[X_TYPE_START]);

	//ロケット
	D3DXLoadMeshFromX("data/MODEL/stage/rocket.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_ROCKET], NULL, &m_aNumMat[X_TYPE_ROCKET], &m_apMesh[X_TYPE_ROCKET]);

	//バナナ
	D3DXLoadMeshFromX("data/MODEL/stage/banana.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[X_TYPE_BANANA], NULL, &m_aNumMat[X_TYPE_BANANA], &m_apMesh[X_TYPE_BANANA]);
}	

//=============================================================================
//終了
//=============================================================================
void CXload::Uninit(void)
{
	for (int nCntXload = 0; nCntXload < X_TYPE_MAX; nCntXload++)
	{
		//メッシュの破棄
		if (m_apMesh[nCntXload] != NULL)
		{
			m_apMesh[nCntXload]->Release();
			m_apMesh[nCntXload] = NULL;
		}

		//マテリアルの破棄
		if (m_apBuffMat[nCntXload] != NULL)
		{
			m_apBuffMat[nCntXload]->Release();
			m_apBuffMat[nCntXload] = NULL;
		}
	}
}

//=============================================================================
//メッシュの割り当て
//=============================================================================
LPD3DXMESH CXload::GetMesh(const X_TYPE &type)
{
	return m_apMesh[type];
}

//=============================================================================
//マテリアル割り当て
//=============================================================================
LPD3DXBUFFER CXload::GetBuffMat(const X_TYPE &type)
{
	return m_apBuffMat[type];
}

//=============================================================================
//マテリアル数割り当て
//=============================================================================
DWORD CXload::GetNumMat(const X_TYPE &type)
{
	return m_aNumMat[type];
}
