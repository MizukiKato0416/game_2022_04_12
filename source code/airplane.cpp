//================================================
//飛行機の処理
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"
#include "model.h"
#include "player.h"

//================================================
//マクロ定義
//================================================
#define AIRPLANE_MOVE_COUNT		(180)			//前に進む時間

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CAirplane::CAirplane(CObject::PRIORITY Priority) :CHappenig(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHitPlayer = false;
	m_nMoveCounter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CAirplane::~CAirplane()
{

}

//================================================
//初期化処理
//================================================
HRESULT CAirplane::Init()
{
	//変数初期化
	m_bHitPlayer = false;
	m_nMoveCounter = 0;

	CHappenig::Init();

	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::AIR_PLANE);

	//位置を設定
	SetPos(m_pos);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CAirplane::Uninit(void)
{
	CHappenig::Uninit();
}

//================================================
//更新処理
//================================================
void CAirplane::Update(void)
{
	CHappenig::Update();

	if (m_bHitPlayer == false)
	{
		//プレイヤーと当たったら
		if (HitPlayer() == true)
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
					if (GetModel()->GetModel()->GetParent() == nullptr)
					{
						//プレイヤーの型にキャスト
						CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

						//親子関係をつける
						GetModel()->GetModel()->SetObjParent(true);
						GetModel()->GetModel()->SetMtxParent(pPlayer->GetMtx());

						//当たっているフラグを立てる
						m_bHitPlayer = true;

						//モデルの位置を取得
						D3DXVECTOR3 modelPos = GetModel()->GetPos();
						//プレイヤーの位置を取得
						D3DXVECTOR3 playerPos = pPlayer->GetPos();
						//プレイヤーの向きを取得
						D3DXVECTOR3 playerRot = pPlayer->GetRot();

						//プレイヤーの高さをモデルの高さにする
						playerPos.y = modelPos.y;
						//位置を設定
						pPlayer->SetPos(playerPos);

						//回転していたら
						if (playerRot.x != 0.0f)
						{
							//0にする
							playerRot.x = 0.0f;
							//向きを設定
							pPlayer->SetRot(playerRot);
						}

						//前に進む力を設定
						pPlayer->SetMoveForward(40.0f);
					}
				}
			}
		}
	}
	else
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
				//プレイヤーの型にキャスト
				CPlayer *pPlayer = static_cast<CPlayer*>(object[count_object]);

				//カウンターを加算
				m_nMoveCounter++;

				//既定の値より大きくなったら
				if (m_nMoveCounter > AIRPLANE_MOVE_COUNT)
				{
					//ジャンプ力を設定
					pPlayer->SetJump(30.0f);
					//消す
					Uninit();
					return;
				}

				//モデルの位置を取得
				D3DXVECTOR3 modelPos = GetModel()->GetPos();
				//プレイヤーの位置を取得
				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				//プレイヤーの向きを取得
				D3DXVECTOR3 playerRot = pPlayer->GetRot();
				//プレイヤーの移動量を取得
				D3DXVECTOR3 playerMove = pPlayer->GetMove();

				//プレイヤーの高さをモデルの高さにする
				playerPos.y = modelPos.y;
				//位置を設定
				pPlayer->SetPos(playerPos);

				//回転していたら
				if (playerRot.x != 0.0f)
				{
					//0にする
					playerRot.x = 0.0f;
					//向きを設定
					pPlayer->SetRot(playerRot);
				}

				//重力を0にする
				playerMove.y = 0.0f;
				//移動量を設定
				pPlayer->SetMove(playerMove);
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CAirplane::Draw(void)
{
	CHappenig::Draw();
}

//================================================
//生成処理
//================================================
CAirplane* CAirplane::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	//インスタンスの生成
	CAirplane *pAirplane = nullptr;
	if (pAirplane == nullptr)
	{
		pAirplane = new CAirplane();
		if (pAirplane != nullptr)
		{
			pAirplane->m_pos = pos;
			pAirplane->m_rot = rot;
			pAirplane->Init();
		}
	}
	return pAirplane;
}
