//================================================
//飛行機の処理
//Author:KatoMizuki
//================================================
#include "airplane.h"
#include "model_single.h"

//================================================
//マクロ定義
//================================================

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
	CHappenig::Init();

	//モデルの生成
	CHappenig::SetModel(CModelSingle::Create(m_pos, m_rot, CXload::X_TYPE_AIRPLANE, NULL, true));

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::SPARKLE);

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
				if (GetModel()->GetParent() == nullptr)
				{
					//モデルの型にキャスト
					CModel *pModel = (CModel*)object[count_object];
					//親子関係をつける
					GetModel()->SetParent(pModel);
				}
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
