//================================================
//シーン処理
//Author:加藤瑞葵
//================================================
#include "object.h"
#include "manager.h"
#include "pause.h"

//================================================
//静的メンバ変数宣言
//================================================
CObject *CObject::m_pTop[PRIORITY_MAX] = {};
CObject *CObject::m_pCur[PRIORITY_MAX] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CObject::CObject(int nPriority)
{
	if (m_pTop[nPriority] == nullptr && m_pCur[nPriority] == nullptr)
	{
		//前のオブジェクト情報がなければTOPにする
		m_pTop[nPriority] = this;
		//つぎのオブジェクト情報がなければCURにする
		m_pCur[nPriority] = this;
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}
	else
	{
		//前のオブジェクト情報があったら前のオブジェクト情報を入れてあげる
		m_pPrev = m_pCur[nPriority];
		//前のオブジェクトの次のオブジェクト情報をこのオブジェクトにする
		m_pCur[nPriority]->m_pNext = this;
		//一番最後にする
		m_pCur[nPriority] = this;
		m_pNext = nullptr;
	}
	m_objType = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_bDeath = false;
}

//================================================
//デストラクタ
//================================================
CObject::~CObject()
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	pObject = this;

	//トップでもカレントでもない場合
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//自分の前のオブジェクトが持っている次のオブジェクト情報を自分の次のオブジェクト情報にする
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報を自分の前のオブジェクト情報にする
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//トップだったらトップを次のオブジェクトにずらす
		m_pTop[m_nPriority] = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報をnullptrにする
		if (pObject->m_pNext != nullptr)
		{
			pObject->m_pNext->m_pPrev = nullptr;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//カレントだったらカレントを前のオブジェクトにずらす
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//自分の前のオブジェクトが持っている次のオブジェクト情報をnullptrにする
		if (pObject->m_pPrev != nullptr)
		{
			pObject->m_pPrev->m_pNext = nullptr;
		}
	}
}

//================================================
//終了処理
//================================================
void CObject::ReleaseAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			//先頭のポインタを代入
			pObject = m_pTop[nCntPriority];
			while (pObject != nullptr)
			{
				//現在のオブジェクトのポインタを保存
				pSaveObject = pObject->m_pNext;
				pObject->Uninit();
				if (pObject->m_bDeath == true)
				{
					//破棄
					delete pObject;
					pObject = nullptr;
				}
				//次のオブジェクトのポインタにする
				pObject = pSaveObject;
			}
		}
	}
}

//================================================
//更新処理
//================================================
void CObject::UpdateAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject->m_pNext;
			//死亡フラグチェック
			if (pObject->m_bDeath == false)
			{
				if (CPause::GetPause() == false)
				{
					pObject->Update();
				}
				else
				{
					if (nCntPriority == PRIORITY_FADE || nCntPriority == PRIORITY_PAUSE)
					{
						pObject->Update();
					}
				}
			}
			pObject = pSaveObject;
		}
	}


	pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject->m_pNext;
			//死亡フラグチェック
			if (pObject->m_bDeath == true)
			{
				//破棄
				delete pObject;
				pObject = nullptr;
			}
			//次のオブジェクトのポインタにする
			pObject = pSaveObject;
		}
	}
}

//================================================
//描画処理
//================================================
void CObject::DrawAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != nullptr)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject->m_pNext;
			pObject->Draw();
			pObject = pSaveObject;
		}
	}
}

//================================================
//単体を破棄する処理
//================================================
void CObject::Release(void)
{
	m_bDeath = true;	
}

//================================================
//オブジェクトの種類の設定処理
//================================================
void CObject::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//================================================
//オブジェクトの種類の設定処理
//================================================
CObject::OBJTYPE CObject::GetObjType(void)
{
	return m_objType;
}

//================================================
//引数のオブジェクトの次のオブジェクト情報取得処理
//================================================
CObject *CObject::GetObjNext(CObject *pObject)
{
	return pObject->m_pNext;
}

//================================================
//オブジェクト取得処理
//================================================
CObject *CObject::GetTopObj(int nPriority)
{
	return m_pTop[nPriority];
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CObject::GetPos(void)
{
	return m_pos;
}

//================================================
//1フレーム前の位置設定処理
//================================================
void CObject::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//================================================
//1フレーム前の位置取得処理
//================================================
D3DXVECTOR3 CObject::GetPosOld(void)
{
	return m_posOld;
}

//================================================
//位置設定処理
//================================================
void CObject::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//================================================
//サイズ取得処理
//================================================
D3DXVECTOR3 CObject::GetSize(void)
{
	return m_size;
}

//================================================
//サイズ設定処理
//================================================
void CObject::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//================================================
//プライオリティ設定処理
//================================================
void CObject::SetPriority(int nPriority)
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	pObject = this;

	//トップでもカレントでもない場合
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//自分の前のオブジェクトが持っている次のオブジェクト情報を自分の次のオブジェクト情報にする
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報を自分の前のオブジェクト情報にする
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//トップだったらトップを次のオブジェクトにずらす
		m_pTop[m_nPriority] = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報をnullptrにする
		if (pObject->m_pNext != nullptr)
		{
			pObject->m_pNext->m_pPrev = nullptr;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//カレントだったらカレントを前のオブジェクトにずらす
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//自分の前のオブジェクトが持っている次のオブジェクト情報をnullptrにする
		if (pObject->m_pPrev != nullptr)
		{
			pObject->m_pPrev->m_pNext = nullptr;
		}
	}



	if (m_pTop[nPriority] == nullptr && m_pCur[nPriority] == nullptr)
	{
		//前のオブジェクト情報がなければTOPにする
		m_pTop[nPriority] = this;
		//つぎのオブジェクト情報がなければCURにする
		m_pCur[nPriority] = this;
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}
	else
	{
		//前のオブジェクト情報があったら前のオブジェクト情報を入れてあげる
		m_pPrev = m_pCur[nPriority];
		//前のオブジェクトの次のオブジェクト情報をこのオブジェクトにする
		m_pCur[nPriority]->m_pNext = this;
		//一番最後にする
		m_pCur[nPriority] = this;
		m_pNext = nullptr;
	}

	m_nPriority = nPriority;
}
