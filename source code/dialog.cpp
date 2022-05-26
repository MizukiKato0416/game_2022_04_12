//================================================
//会話の処理
//Author:KatoMizuki
//================================================
#include "object.h"
#include "dialog.h"
#include "letter.h"
#include "sound.h"
#include "manager.h"
#include "next_dialog_ui.h"
#include "input_mouse.h"
#include "fade.h"
#include "trophy.h"
#include "play_data.h"
#include "history_letter.h"

//================================================
//マクロ定義
//================================================
#define DIALOG_MAX_STRING				(256)									//文字の最大量
#define DIALOG_LETTER_CREATE_COUNT		(3)										//1文字出すまでの時間
#define DIALOG_ROCKY_UI_POS_Y			(260.0f)								//ロッキー君のUIの位置Y
#define DIALOG_ROCKY_UI_SIZE_X			(545.0f * 1.0f)							//ロッキー君のUIのサイズX
#define DIALOG_ROCKY_UI_SIZE_Y			(566.0f * 1.0f)							//ロッキー君のUIのサイズY
#define DIALOG_ROCKY_FACE_UI_SIZE_X		(545.0f * 0.7f)							//ロッキー君の顔UIのサイズX
#define DIALOG_ROCKY_FACE_UI_SIZE_Y		(566.0f * 0.7f)							//ロッキー君の顔UIのサイズY
#define DIALOG_ROCKY_FACE_UI_POS_X		(SCREEN_WIDTH / 2.0f - 10.0f)			//ロッキー君の顔UIの位置X
#define DIALOG_ROCKY_FACE_UI_POS_Y		(230.0f)								//ロッキー君の顔UIの位置Y
#define DIALOG_FRAME_POS_Y				(230.0f)								//セリフのフレーム位置Y

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CDialog::CDialog(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_dialogBody.clear();
	m_pLetter.clear();
	m_dialog.clear();
	m_nDialogDelay = 0;
	m_nDialogCntX = 0;
	m_nDialogCntY = 0;
	m_nLetterCreateCounter = 0;
	m_pPersonPose = nullptr;
	m_pPersonFace = nullptr;
	m_pFrame = nullptr;
	m_poseType = POSE::NORMAL;
	m_faceType = FACE::SMILE;
	m_frameType = FRAME::NORMAL;
	m_bCreateFinish = false;
	m_nDialogNum = 0;
	m_pNextDialogUI = nullptr;
	m_nCountFrame = 0;
	m_bDialogFinish = false;
	m_nMaxDialog = 0;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CDialog::~CDialog()
{
	
}

//================================================
//初期化処理
//================================================
HRESULT CDialog::Init()
{
	//変数初期化
	m_nLetterCreateCounter = DIALOG_LETTER_CREATE_COUNT;
	m_pPersonPose = nullptr;
	m_pPersonFace = nullptr;
	m_pFrame = nullptr;
	m_poseType = POSE::NORMAL;
	m_faceType = FACE::SMILE;
	m_frameType = FRAME::NORMAL;
	m_bCreateFinish = false;
	m_nDialogNum = 0;
	m_pNextDialogUI = nullptr;
	m_nCountFrame = 0;
	m_bDialogFinish = false;

	char cString[DIALOG_MAX_STRING];
	FILE *file;
	file = fopen("data/dialog_ss.txt", "r");

	if (file != NULL)
	{
		//一行ずつ保存
		while (fgets(cString, DIALOG_MAX_STRING, file) != NULL)
		{
			//BEGIN_DIALOGと書かれていたら
			if (strncmp("BEGIN_DIALOG\n", cString, 14) == 0)
			{
				//初期化
				DIALOG_BODY dialogBody;
				dialogBody.nPersonPose = 0;
				dialogBody.nPersonFace = 0;
				dialogBody.nFrame = 0;

				//配列を増やす
				m_dialogBody.push_back(dialogBody);
				//ポーズを読み込む
				fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nPersonPose);
				//顔を読み込む
				fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nPersonFace);
				//フレームを読み込む
				fscanf(file, "%*s%*s%d", &m_dialogBody[m_nMaxDialog].nFrame);

				char name_buf[1][DIALOG_MAX_STRING];
				string name;

				fscanf(file, "%s", name_buf[0]);

				name = name_buf[0];

				// SJIS → wstring
				int iBufferSize = MultiByteToWideChar(CP_ACP,
					0,
					name.c_str(),
					-1,
					(wchar_t*)NULL,
					0);

				// バッファの取得
				wchar_t* cpUCS2 = new wchar_t[iBufferSize];

				// SJIS → wstring
				MultiByteToWideChar(CP_ACP,
					0,
					name.c_str(),
					-1,
					cpUCS2,
					iBufferSize);

				// stringの生成
				wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

				// バッファの破棄
				delete[] cpUCS2;

				m_dialog.push_back(utextbuf);

				//総数を増やす
				m_nMaxDialog++;
			}
			else if (strncmp("END_SCRIPT", cString, 11) == 0)
			{//END_SCRIPTと書かれていたら
				break;
			}
		}
	}
	fclose(file);
	return S_OK;
}

//================================================
//終了処理
//================================================
void CDialog::Uninit(void)
{
	Release();
}

//================================================
//更新処理
//================================================
void CDialog::Update(void)
{
	if (m_bCreateFinish == true)
	{
		//総数以下だったら
		if (m_nDialogNum < m_nMaxDialog)
		{
			//セリフの生成と全文が表示されたかどうかを取得
			m_bDialogFinish = Dialog(m_nDialogNum);
		}
		//全文が表示されたら
		if (m_bDialogFinish)
		{
			if (m_pNextDialogUI == nullptr)
			{
				//次のセリフに行くUIを生成
				m_pNextDialogUI = CNextDialogUI::Create(D3DXVECTOR3(NEXT_DILOG_UI_POS_X, NEXT_DILOG_UI_POS_Y, 0.0f),
					                                    D3DXVECTOR3(NEXT_DILOG_UI_SIZE, NEXT_DILOG_UI_SIZE, 0.0f));
				m_pNextDialogUI->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("click_ui.png"));
				//全文を表示した状態にする
				m_bDialogFinish = true;
			}


			//マウス取得処理
			CInputMouse *pInputMouse;
			pInputMouse = CManager::GetInstance()->GetInputMouse();

			//マウスを押した瞬間
			if (pInputMouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				//次のセリフにする
				m_nDialogNum++;

				//総数以下だったら
				if (m_nDialogNum < m_nMaxDialog)
				{
					//セリフ生成
					SetDialog(m_nDialogNum);
				}
				else
				{
					//サウンド取得
					CSound *sound;
					sound = CManager::GetInstance()->GetSound();
					//再生する
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);

					//フェード取得処理
					CFade *pFade;
					pFade = CManager::GetInstance()->GetFade();

					if (pFade->GetFade() == CFade::FADE_NONE)
					{
						//タイトルシーンに遷移
						pFade->SetFade(CManager::MODE::TITLE);

						//トロフィーのフラグ状態を取得
						vector<bool> flag = CManager::GetInstance()->GetPlayData()->GetFlag();
						//トロフィーを取得したことがなかったら
						if (flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] == false)
						{
							//取得させる
							flag[(int)CTrophy::TROPHY::ROCKY_ANGRY] = true;
							//フラグを立てる
							CManager::GetInstance()->GetPlayData()->SetFlag(flag);
							CHistory::Create(CTrophy::TROPHY::ROCKY_ANGRY);
						}
					}
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CDialog::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CDialog *CDialog::Create(void)
{
	//インスタンスの生成
	CDialog *pDialog = nullptr;
	if (pDialog == nullptr)
	{
		pDialog = new CDialog();
		if (pDialog != nullptr)
		{
			pDialog->Init();
		}
	}
	return pDialog;
}


//================================================
//セリフ処理
//================================================
bool CDialog::Dialog(const int &nCntDialog)
{
	wchar_t cReturn[] = L"#";
	int nDialogSize = m_dialog[nCntDialog].size();

	if (m_nDialogDelay < nDialogSize)
	{
		//フレームのカウンターを加算
		m_nCountFrame++;
		//既定の値より大きくなったら
		if (m_nCountFrame > m_nLetterCreateCounter)
		{
			if (m_dialog[nCntDialog][m_nDialogDelay] == *cReturn)
			{
				//改行するので0にする
				m_nDialogCntX = 0;
				m_nDialogCntY++;

				//消す
				m_dialog[nCntDialog].erase(m_dialog[nCntDialog].begin() + m_nDialogDelay);
				nDialogSize--;
				m_nDialogDelay--;
			}
			else
			{
				m_pLetter.push_back(new CLetter);

				m_pLetter[m_nDialogDelay]->SetPos(D3DXVECTOR3(200.0f + (15.0f * 2.0f) * m_nDialogCntX, 600.0f + (15.0f * 2.0f) * m_nDialogCntY, 0.0f));
				m_pLetter[m_nDialogDelay]->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
				m_pLetter[m_nDialogDelay]->SetText(m_dialog[nCntDialog][m_nDialogDelay]);
				m_pLetter[m_nDialogDelay]->SetFontSize(300);
				m_pLetter[m_nDialogDelay]->SetFontWeight(500);
				m_pLetter[m_nDialogDelay]->Init();

				//サウンド取得
				CSound *sound;
				sound = CManager::GetInstance()->GetSound();
				//再生する
				sound->Play(CSound::SOUND_LABEL::DIALOG_SE);
				sound->ControllVoice(CSound::SOUND_LABEL::DIALOG_SE, 3.4f);

				//カウンターを加算
				m_nDialogCntX++;
			}

			//カウンターを加算
			m_nDialogDelay++;

			//0にする
			m_nCountFrame = 0;
		}
	}
	else
	{
		return true;
	}
	return false;
}

//================================================
//セリフ破棄処理
//================================================
void CDialog::UninitDialog(void)
{
	m_nDialogCntX = 0;
	m_nDialogCntY = 0;
	m_nDialogDelay = 0;

	int nSize = m_pLetter.size();

	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		m_pLetter[nCnt]->Uninit();
		m_pLetter[nCnt] = nullptr;
	}
	m_pLetter.clear();

	if (m_pNextDialogUI != nullptr)
	{
		//次のセリフに行くUIを消す
		m_pNextDialogUI->Uninit();
		m_pNextDialogUI = nullptr;
	}

	m_bCreateFinish = false;
	m_bDialogFinish = false;
}

//================================================
//セリフ設定処理
//================================================
void CDialog::SetDialog(const int &nNumDialog)
{
	//セリフ破棄処理
	UninitDialog();

	m_nDialogNum = nNumDialog;

	//ポーズタイプに代入
	m_poseType = (CDialog::POSE)m_dialogBody[nNumDialog].nPersonPose;
	//顔タイプに代入
	m_faceType = (CDialog::FACE)m_dialogBody[nNumDialog].nPersonFace;
	//フレームタイプに代入
	m_faceType = (CDialog::FACE)m_dialogBody[nNumDialog].nPersonFace;

	//生成されていなかったら
	if (m_pPersonPose == nullptr)
	{
		//ポーズの生成
		m_pPersonPose = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, DIALOG_ROCKY_UI_POS_Y, 0.0f),
			                              D3DXVECTOR3(DIALOG_ROCKY_UI_SIZE_X, DIALOG_ROCKY_UI_SIZE_Y, 0.0f),
			                              static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pPersonPose->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("rocky_pose.png"));
	}
	//生成されていなかったら
	if (m_pPersonFace == nullptr)
	{
		//顔の生成
		m_pPersonFace = CObject2D::Create(D3DXVECTOR3(DIALOG_ROCKY_FACE_UI_POS_X, DIALOG_ROCKY_FACE_UI_POS_Y, 0.0f),
			                              D3DXVECTOR3(DIALOG_ROCKY_FACE_UI_SIZE_X, DIALOG_ROCKY_FACE_UI_SIZE_Y, 0.0f),
			                              static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pPersonFace->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("rocky_face.png"));
	}
	//生成されていなかったら
	if (m_pFrame == nullptr)
	{
		//フレームの生成
		m_pFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - DIALOG_FRAME_POS_Y / 2.0f, 0.0f),
			                         D3DXVECTOR3(SCREEN_WIDTH, DIALOG_FRAME_POS_Y, 0.0f),
			                         static_cast<int>(CObject::PRIORITY::DIALOG));
		m_pFrame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("comment_frame.png"));
	}

	if (nNumDialog == 0)
	{
		//テクスチャの設定
		m_pPersonPose->SetTex((int)m_poseType, (int)POSE::MAX);
		//テクスチャの設定
		m_pPersonFace->SetTex((int)m_faceType, (int)FACE::MAX);
	}
	else
	{
		//前に指定したポーズと今回指定しているポーズが違う場合
		if (m_dialogBody[nNumDialog - 1].nPersonPose != m_dialogBody[nNumDialog].nPersonPose)
		{
			//テクスチャの設定
			m_pPersonPose->SetTex((int)m_poseType, (int)POSE::MAX);
		}
		//前に指定した顔と今回指定している顔が違う場合
		if (m_dialogBody[nNumDialog - 1].nPersonFace != m_dialogBody[nNumDialog].nPersonFace)
		{
			//テクスチャの設定
			m_pPersonFace->SetTex((int)m_faceType, (int)FACE::MAX);
		}
	}
	m_bCreateFinish = true;
}
