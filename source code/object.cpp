//=============================================================================
//
// オブジェクト処理 [object.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "object.h"
#include "pause.h"
#include "manager.h"
#include "game01.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<CObject*> CObject::m_object[(int)PRIORITY::MAX];

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject::CObject(PRIORITY priolty)
{
	m_obj_type = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_priority = (int)priolty;
	m_deth = false;

	m_object[m_priority].push_back(this);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// 全部削除
//=============================================================================
void CObject::ReleaseAll(void)
{
	/*for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		if (object_size > 0)
		{
			for (int count_object = object_size - 1; count_object >= 0; count_object--)
			{
				if (m_object[count_priolty][count_object]->m_priority != static_cast<int>(PRIORITY::FADE))
				{
					if (m_object[count_priolty][count_object]->m_deth == false)
					{
						m_object[count_priolty][count_object]->Uninit();
					}
					if (m_object[count_priolty][count_object]->m_deth == true)
					{
						delete m_object[count_priolty][count_object];
						m_object[count_priolty][count_object] = nullptr;
						m_object[count_priolty].pop_back();
					}
				}
			}
		}
	}
*/
	for (int nCnt = 0; nCnt < (int)PRIORITY::MAX; nCnt++)
	{
		int nPrioltySize = m_object[nCnt].size();

		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE))
			{
				delete m_object[nCnt][nCntPop];
			}
		}

		nPrioltySize = m_object[nCnt].size();
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE))
			{
				m_object[nCnt].pop_back();
				nPrioltySize = m_object[nCnt].size();
				nCntPop--;
			}
		}
	}
}

//=============================================================================
// 全部更新
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			if (m_object[count_priolty][count_object]->m_deth == true)
			{
				delete m_object[count_priolty][count_object];
				m_object[count_priolty][count_object] = NULL;
				m_object[count_priolty].erase(m_object[count_priolty].begin() + count_object);
				object_size = m_object[count_priolty].size();
				count_object--;
			}
			else
			{
				if (CManager::GetMode() == CManager::MODE::GAME01)
				{
					if (CPause::GetPause() == false)
					{
						if (CManager::GetInstance()->GetGame01()->GetDialog() == false)
						{
							m_object[count_priolty][count_object]->Update();
						}
						else
						{
							if (count_priolty == (int)PRIORITY::GAME || count_priolty == (int)PRIORITY::FADE ||
								count_priolty == (int)PRIORITY::CLICK_EFFECT || count_priolty == (int)PRIORITY::NEXT_DIALOG_UI)
							{
								m_object[count_priolty][count_object]->Update();
							}
						}
					}
					else
					{
						if (count_priolty == (int)PRIORITY::PAUSE || count_priolty == (int)PRIORITY::FADE || count_priolty == (int)PRIORITY::CLICK_EFFECT)
						{
							m_object[count_priolty][count_object]->Update();
						}
					}
				}
				else
				{
					m_object[count_priolty][count_object]->Update();
				}
			}
		}
	}
}

//=============================================================================
// 全部描画
//=============================================================================
void CObject::DrawAll(void)
{
	for (int count_priolty = 0; count_priolty < (int)PRIORITY::MAX; count_priolty++)
	{
		int object_size = m_object[count_priolty].size();
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

//================================================
//プライオリティ設定処理
//================================================
void CObject::SetPriority(const int &nPriority)
{
	//次のオブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	pObject = this;

	m_object[nPriority].push_back(this);
	int nThisPriority = this->m_priority;
	int object_size = m_object[nThisPriority].size();
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		if (m_object[nThisPriority][count_object] == this)
		{
			m_object[nThisPriority].erase(m_object[nThisPriority].begin() + count_object);
			object_size = m_object[nThisPriority].size();
			break;
		}
	}

	this->m_priority = nPriority;
}
