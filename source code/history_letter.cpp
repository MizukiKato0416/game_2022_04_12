//=============================================================================
//
// トロフィールー処理 [trophy.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "history_letter.h"
#include "manager.h"
#include "object2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CHistory::m_in_object = false;

//=============================================================================
// マクロ定義
//=============================================================================
#define HISTORY_SIZE (D3DXVECTOR3(300.0f, 60.0f, 0.0f))
#define HISTORY_POS (D3DXVECTOR3(SCREEN_WIDTH + (300.0f / 2), 0.0f + (60.0f / 2), 0.0f))
#define HISTORY_STOP_POS_X (SCREEN_WIDTH - (300.0f / 2))
#define HISTORY_MOVE_SPEED (10.5f)
#define HISTORY_TIME (120)

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CHistory::CHistory(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_history = nullptr;
	m_cout_stop = 0;
	m_stop = false;	
	m_in_or_out = false;	
	m_history_in = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CHistory::~CHistory()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CHistory::Init(void)
{
	m_history = CObject2D::Create(HISTORY_POS, HISTORY_SIZE, static_cast<int>(CObject::PRIORITY::HISTORY_LETTER));
	switch (m_type)
	{
	case CTrophy::TROPHY::AIRPLANE:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_airport.png"));
		break;
	case CTrophy::TROPHY::FAN:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_fan.png"));
		break;
	case CTrophy::TROPHY::REDBULL:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_redbull.png"));
		break;
	case CTrophy::TROPHY::STARRING:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_star.png"));
		break;
	case CTrophy::TROPHY::THORN:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_thorn.png"));
		break;
	case CTrophy::TROPHY::ROCKET:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_rocket.png"));
		break;
	case CTrophy::TROPHY::BANANA:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_banana.png"));
		break;
	case CTrophy::TROPHY::TRAMPOLINE:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_trampoline.png"));
		break;
	case CTrophy::TROPHY::M_1000:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_1000m.png"));
		break;
	case CTrophy::TROPHY::M_5000:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_5000m.png"));
		break;
	case CTrophy::TROPHY::M_10000:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_10000m.png"));
		break;
	case CTrophy::TROPHY::MEASUREMENT_IMPOSSIBLE:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_error.png"));
		break;
	case CTrophy::TROPHY::EVENING:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_evenig.png"));
		break;
	case CTrophy::TROPHY::NIGHT:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_night.png"));
		break;
	case CTrophy::TROPHY::GIRL:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_rokiko.png"));
		break;
	case CTrophy::TROPHY::HARD:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_hard.png"));
		break;
	case CTrophy::TROPHY::GROUND:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_ground.png"));
		break;
	case CTrophy::TROPHY::PLAY_00:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_first.png"));
		break;
	case CTrophy::TROPHY::PLAY_05:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_5.png"));
		break;
	case CTrophy::TROPHY::PLAY_10:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_10.png"));
		break;
	case CTrophy::TROPHY::ENDROLL:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_end.png"));
		break;
	case CTrophy::TROPHY::ROCKY_ANGRY:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_angry.png"));
		break;
	case CTrophy::TROPHY::KIYO:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_kiyo.png"));
		break;
	case CTrophy::TROPHY::COMPLETE:
		m_history->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("achievement_complete.png"));
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CHistory::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CHistory::Update(void)
{
	D3DXVECTOR3 pos = m_history->GetPos();

	if (m_in_object == false || m_history_in == true)
	{
		m_in_object = true;
		m_history_in = true;
		if (m_stop == true)
		{
			m_cout_stop++;
			if (m_cout_stop >= HISTORY_TIME)
			{
				m_stop = false;
				m_in_or_out = true;
			}
		}
		if (m_in_or_out == false && m_stop == false)
		{
			pos.x -= HISTORY_MOVE_SPEED;
			m_history->SetPos(pos, m_history->GetSize());
			if (pos.x <= HISTORY_STOP_POS_X)
			{
				m_stop = true;
			}
		}
		else if (m_in_or_out == true && m_stop == false)
		{
			pos.x += HISTORY_MOVE_SPEED;
			m_history->SetPos(pos, m_history->GetSize());
			if (pos.x >= HISTORY_POS.x)
			{
				m_in_object = false;
				m_history->Uninit();
				Uninit();
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CHistory::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CHistory *CHistory::Create(CTrophy::TROPHY type)
{
	//インスタンスの生成
	CHistory *history = nullptr;
	if (history == nullptr)
	{
		history = new CHistory();
		if (history != nullptr)
		{
			history->m_type = type;
			history->Init();
		}
	}
	return history;
}