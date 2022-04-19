//================================================
//プレイデータ管理処理
//Author:加藤瑞葵
//================================================
#include "play_data.h"
#include "model_single.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CPlayData::CPlayData()
{	
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;
}

//================================================
//デストラクタ
//================================================
CPlayData::~CPlayData()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPlayData::Init(void)
{
	FILE *file;
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;

	file = fopen("data/trophy_frag.txt", "r");

	for (int count_flag = 0; count_flag < (int)CModelSingle::HAPPENING_TYPE::MAX - 1; count_flag++)
	{
		int buf = 0;
		fscanf(file, "%*s%*s%d", &buf);
		m_trophy_flag.push_back(static_cast<bool>(buf));
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPlayData::Uninit(void)
{
	FILE *file;

	file = fopen("data/trophy_frag.txt", "w");

	for (int count_flag = 0; count_flag < (int)CModelSingle::HAPPENING_TYPE::MAX - 1; count_flag++)
	{
		fprintf(file, "frag_%d : %d\n", count_flag, static_cast<int>(m_trophy_flag[count_flag]));
	}
}