//=============================================================================
//
// ハプニング処理 [bhappening.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "happening.h"
#include "model_single.h"
#include "model.h"
#include "camera.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define HAPPENING_ADD_CAMERA_POS		(20.0f)		//カメラの位置を移動させる量
#define HAPPENING_ADD_CAMERA_DIFFER		(-40.0f)	//カメラの視点と注視点の距離を増やす量
#define HAPPENING_ZOOM_CAMERA_DIFFER	(400.0f)	//ズーム時のカメラの視点と注視点の距離

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CHappenig::m_bHit = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CHappenig::CHappenig(CObject::PRIORITY Priority) : CObject(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model = nullptr;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CHappenig::~CHappenig()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CHappenig::Init(void)
{
	//モデルの上頂点の位置を取得
	D3DXVECTOR3 vtxPos[8];
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		vtxPos[nCntVtx] = GetModel()->GetModel()->GetVtxPos(nCntVtx);
	}

	//モデルのサイズYを風のエフェクトのサイズの3分の2引き延ばす
	vtxPos[0].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[1].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[4].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[5].y += HAPPENING_ADD_SIZE_Y;

	vtxPos[0].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[2].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[4].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[6].x -= HAPPENING_ADD_SIZE_X;

	vtxPos[1].x += HAPPENING_ADD_SIZE_X;
	vtxPos[3].x += HAPPENING_ADD_SIZE_X;
	vtxPos[5].x += HAPPENING_ADD_SIZE_X;
	vtxPos[7].x += HAPPENING_ADD_SIZE_X;

	//サイズを設定
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		GetModel()->GetModel()->SetVtxPos(nCntVtx, vtxPos[nCntVtx]);
	}

	SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CHappenig::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CHappenig::Update(void)
{
	
}

//=============================================================================
// 描画
//=============================================================================
void CHappenig::Draw(void)
{

}

//=============================================================================
// プレイヤーとの当たり判定
//=============================================================================
bool CHappenig::HitPlayer(void)
{
	//オブジェクト情報を入れるポインタ
	vector<CObject*> object;

	//先頭のポインタを代入
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		//プレイヤーだった時
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//当たり判定をする設定なら
			if (m_model->GetColl() == true)
			{
				//8頂点の取得
				D3DXVECTOR3 vtxPos[MODEL_VTX];
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
				{
					vtxPos[nCntVtx] = m_model->GetModel()->GetVtxPos(nCntVtx);
				}

				//8頂点のワールドマトリックスを取得
				D3DXMATRIX *pVtxMtxWorld = m_model->GetModel()->GetVtxMtxWorld();
				//8頂点の設定
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++, pVtxMtxWorld++)
				{
					//ワールドマトリックス設定
					m_model->SetMtxWorld();
					//モデルの設定
					//m_model->GetModel()->SetVtxMtxWorld(vtxPos[nCntVtx], nCntVtx);
					vtxPos[nCntVtx] = D3DXVECTOR3(pVtxMtxWorld->_41, pVtxMtxWorld->_42, pVtxMtxWorld->_43);
				}


				//頂点から頂点までのベクトル算出用
				D3DXVECTOR3 vtxVec[6][2];
				//頂点から頂点までのベクトル算出
				//奥の面
				vtxVec[0][0] = vtxPos[0] - vtxPos[1];
				vtxVec[0][1] = vtxPos[3] - vtxPos[1];
				//右の面
				vtxVec[1][0] = vtxPos[1] - vtxPos[5];
				vtxVec[1][1] = vtxPos[7] - vtxPos[5];
				//前の面
				vtxVec[2][0] = vtxPos[5] - vtxPos[4];
				vtxVec[2][1] = vtxPos[6] - vtxPos[4];
				//左の面
				vtxVec[3][0] = vtxPos[4] - vtxPos[0];
				vtxVec[3][1] = vtxPos[2] - vtxPos[0];
				//上の面
				vtxVec[4][0] = vtxPos[1] - vtxPos[0];
				vtxVec[4][1] = vtxPos[4] - vtxPos[0];
				//下の面
				vtxVec[5][0] = vtxPos[7] - vtxPos[6];
				vtxVec[5][1] = vtxPos[2] - vtxPos[6];

				//法線保存用変数
				D3DXVECTOR3 vecNor[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					//各面の法線を求める
					D3DXVec3Cross(&vecNor[nCntSurfase], &vtxVec[nCntSurfase][0], &vtxVec[nCntSurfase][1]);

					//ベクトルを正規化する(ベクトルの大きさを1にする)
					D3DXVec3Normalize(&vecNor[nCntSurfase], &vecNor[nCntSurfase]);
				}

				//対象の現在位置取得
				D3DXVECTOR3 pos = object[count_object]->GetPos();

				//頂点の位置から対象の現在の位置のベクトルを算出
				D3DXVECTOR3 vecPos[6];
				//奥の面
				vecPos[0] = pos - vtxPos[0];
				//右の面
				vecPos[1] = pos - vtxPos[1];
				//前の面
				vecPos[2] = pos - vtxPos[5];
				//左の面
				vecPos[3] = pos - vtxPos[4];
				//上の面
				vecPos[4] = pos - vtxPos[1];
				//下の面
				vecPos[5] = pos - vtxPos[7];

				//算出したベクトルと法線のベクトルの内積を求める
				float fVecDot[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					fVecDot[nCntSurfase] = D3DXVec3Dot(&vecNor[nCntSurfase], &vecPos[nCntSurfase]);
				}

				//全ての内積の計算結果がマイナスの時
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f &&
					fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f)
				{
					//当たっている
					return true;
				}
			}
		}
	}
	return false;
}

//=============================================================================
//カメラがプレイヤーをズームする
//=============================================================================
void CHappenig::SetCameraZoom(void)
{
	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;

	//オブジェクト情報を入れるポインタ
	vector<CObject*> object;

	//先頭のポインタを代入
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		//プレイヤーだった時
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーの位置を取得
			D3DXVECTOR3 playerPos = object[count_object]->GetPos();
			//注視点を取得
			D3DXVECTOR3 cameraPosR = pCamera->GetPosR();
			//差を求める
			D3DXVECTOR3 posDiffer = cameraPosR - playerPos;

			if (posDiffer.y > 0.0f)
			{
				cameraPosR.y -= HAPPENING_ADD_CAMERA_POS;
			}
			else if (posDiffer.y < 0.0f)
			{
				cameraPosR.y += HAPPENING_ADD_CAMERA_POS;
			}

			if (posDiffer.y > -HAPPENING_ADD_CAMERA_POS && posDiffer.y < HAPPENING_ADD_CAMERA_POS)
			{
				cameraPosR.y = playerPos.y;
			}

			//注視点をプレイヤーの位置に設定
			pCamera->SetPosR(cameraPosR);

			//既定の値よりも大きいとき
			if (pCamera->GetDiffer() > HAPPENING_ZOOM_CAMERA_DIFFER)
			{
				//カメラの視点と注視点の距離を狭くする
				pCamera->AddDiffer(HAPPENING_ADD_CAMERA_DIFFER);
				//規定値よりも小さくなったら
				if (pCamera->GetDiffer() < HAPPENING_ZOOM_CAMERA_DIFFER)
				{
					//カメラの視点と注視点の距離を設定
					pCamera->SetDiffer(400.0f);
				}
			}
		}
	}
}

//=============================================================================
//モデルの削除処理
//=============================================================================
void CHappenig::DeleteModel(void)
{
	if (m_model != nullptr)
	{
		m_model->Uninit();
		m_model = nullptr;
	}
}
