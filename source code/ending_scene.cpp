//================================================
//エンディングシーン処理
//Authore:加藤瑞葵
//================================================
#include "ending_scene.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "object2D.h"
#include "next_dialog_ui.h"
#include "input_mouse.h"
#include "play_data.h"
#include "trophy.h"
#include "history_letter.h"
#include "dialog.h"

#ifdef _DEBUG
#include "input_keyboard.h"
#endif // !_DEBUG

//================================================
//マクロ定義
//================================================
#define ENDING_SCENE_ENDROLL_SIZE_Y			(5045.0f)		//エンドロールのサイズY
#define ENDING_SCENE_ENDROLL_SPEED			(3.0f)			//エンドロールの速さ
#define ENDING_SCENE_ENDROLL_SPEED_SKIP		(9.0f)			//SKIPするときのエンドロールの速さ
#define ENDING_SCENE_CREATE_DIALOG_TIME		(60)			//会話が出てくるまでの時間

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEndingScene::CEndingScene()
{
	m_pObject2D = nullptr;
	m_pNextDialogUI = nullptr;
	m_pDialog = nullptr;
	m_nConter = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEndingScene::~CEndingScene()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEndingScene::Init(void)
{
	//サウンド取得
	CSound *sound;
	sound = CManager::GetInstance()->GetSound();
	//止める
	sound->Stop();
	//再生する
	sound->Play(CSound::SOUND_LABEL::ENDROOL_BGM);
	sound->ControllVoice(CSound::SOUND_LABEL::ENDROOL_BGM, 0.7f);

	//変数初期化
	m_pNextDialogUI = nullptr;
	m_nConter = 0;

	//エンドロールの生成
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f, 0.0f),
                                    D3DXVECTOR3(SCREEN_WIDTH, ENDING_SCENE_ENDROLL_SIZE_Y, 0.0f),
		                            static_cast<int>(CObject::PRIORITY::UI));
	m_pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("endroll.png"));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEndingScene::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CEndingScene::Update(void)
{
	//位置を取得
	D3DXVECTOR3 pos = m_pObject2D->GetPos();

	//位置Yを既定の値増加
	pos.y -= ENDING_SCENE_ENDROLL_SPEED;

	//最後まで行ったら
	if (pos.y <= 0.0f - ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f + SCREEN_HEIGHT)
	{
		//止める
		pos.y = 0.0f - ENDING_SCENE_ENDROLL_SIZE_Y / 2.0f + SCREEN_HEIGHT;

		//カウンターを加算
		m_nConter++;

		if (m_nConter > ENDING_SCENE_CREATE_DIALOG_TIME)
		{
			if (m_pDialog == nullptr)
			{
				//会話文の生成
				m_pDialog = CDialog::Create(CDialog::SCENE_TYPE::ENDROLL_SCENE);

				//トロフィーのフラグ状態を取得
				vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
				//トロフィーを取得したことがなかったら
				if (flag[(int)CTrophy::TROPHY::ENDROLL] == false)
				{
					//取得させる
					flag[(int)CTrophy::TROPHY::ENDROLL] = true;
					//フラグを立てる
					CManager::GetInstance()->GetPlayData()->SetFlag(flag);
					CHistory::Create(CTrophy::TROPHY::ENDROLL);
				}
			}
		}
	}
	else
	{
		//マウス取得処理
		CInputMouse *pInputMouse;
		pInputMouse = CManager::GetInstance()->GetInputMouse();

		//マウスを押した瞬間
		if (pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			//さらに位置Yを既定の値増加
			pos.y -= ENDING_SCENE_ENDROLL_SPEED_SKIP;
		}
	}

	//位置設定
	m_pObject2D->SetPos(pos, m_pObject2D->GetSize());

#ifdef _DEBUG
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enterキーを押したら
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//フェード取得処理
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::TITLE);
		}
	}
#endif // !_DEBUG
}

//================================================
//描画処理
//================================================
void CEndingScene::Draw(void)
{
	
}