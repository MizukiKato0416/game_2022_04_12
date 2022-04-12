//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#include "main.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "object.h"

//========================================================
//マクロ定義
//========================================================
#define CAMERA_V_SPEED_Y			(0.03f)									//カメラの横移動スピード
#define CAMERA_V__MOUSE_SPEED_Y		(0.003f)								//カメラの横移動スピード（マウスの時）
#define CAMERA_V_SPEED_XZ			(0.01f)									//カメラの縦移動スピード
#define CAMERA_V__MOUSE_SPEED_XZ	(-0.001f)								//カメラの横移動スピード（マウスの時）
#define CAMERA_RESULT_DISTANCE		(200.0f)								//リザルトの視点と注視点の距離
#define CAMERA_V_MAX_POS_Y			(400.0f)								//視点のy座標最大値
#define CAMERA_V_MIN_POS_Y			(50.0f)									//視点のy座標最小値
#define CAMERA_MAX_RENDERER			(200000.0f)								//cameraでの描画最大Z値
#define CAMERA_MIN_RENDERER			(50.0f)									//cameraでの描画最小Z値
#define CAMERA_SWAY_SMALL_X_RAND	(float (rand() % 200 + -100) / 100)		//揺れ幅(x座標)を決めるためのランダム値
#define CAMERA_SWAY_SMALL_Y_RAND	(float (rand() % 200 + -100) / 100)		//揺れ幅(y座標)を決めるためのランダム値
#define CAMERA_SWAY_LARGE_X_RAND	(float (rand() % 600 + -300) / 100)		//揺れ幅(x座標)を決めるためのランダム値
#define CAMERA_SWAY_LARGE_Y_RAND	(float (rand() % 1200 + -600) / 100)	//揺れ幅(y座標)を決めるためのランダム値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//カメラの向き
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的のカメラの向き
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//法線
	m_numRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを変える量
	m_rotDiffer = 0.0f;								//目的と向きの差
	m_viewport.X = (DWORD)0.0f;						//描画する画面の左上X座標
	m_viewport.Y = (DWORD)0.0f;						//描画する画面の左上Y座標
	m_viewport.MinZ = 0.0f;							//描画するz座標の範囲の最小値
	m_viewport.MaxZ = 0.0f;							//描画するz座標の範囲の最大値
	m_viewport.Width = (DWORD)0.0f;					//描画する画面の幅
	m_viewport.Height = (DWORD)0.0f;				//描画する画面の高さ
	m_bRotateX = false;								//カメラX軸が回転しているかどうか
	m_bRotateY = false;								//カメラY軸が回転しているかどうか
	m_nNum = 0;										//cameraの個体識別番号
	m_state = CAMERA_STATE::NONE;					//カメラの状態
	m_fDifferVR = 0.0f;								//視点と注視点の距離
	m_type = TYPE::NONE;							//種類
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CCamera::~CCamera()
{

}

//================================================
//初期化処理
//================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type)
{
	m_rot = rot;																	//カメラの向き
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的のカメラの向き
	m_posV = pos;									//現在の視点
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の注視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//法線
	m_numRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを変える量
	m_rotDiffer = 0.0f;								//目的と向きの差
	m_viewport.X = (DWORD)viewportX;				//描画する画面の左上X座標
	m_viewport.Y = (DWORD)viewportY;				//描画する画面の左上Y座標
	m_viewport.MinZ = 0.0f;							//描画するz座標の範囲の最小値
	m_viewport.MaxZ = 1.0f;							//描画するz座標の範囲の最大値
	m_viewport.Width = (DWORD)viewportWidth;		//描画する画面の幅
	m_viewport.Height = (DWORD)viewporHeight;		//描画する画面の高さ
	m_bRotateX = false;								//カメラX軸が回転しているかどうか
	m_bRotateY = false;								//カメラY軸が回転しているかどうか
	m_state = CAMERA_STATE::NORMAL;					//カメラの状態
	m_type = type;									//種類

	if (m_type == TYPE::MAIN)
	{
		//視点の場所を注視点を元に移動
		m_fDifferVR = CAMERA_DISTANCE;
		m_posV.x = m_posR.x + sinf(m_rot.y) * m_fDifferVR;
		m_posV.z = m_posR.z + cosf(m_rot.y) * m_fDifferVR;
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CCamera::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CCamera::Update(void)
{
	//カメラの種類によって分ける
	switch (m_type)
	{
	case CCamera::TYPE::MAIN:
		MainCameraUpdate();
		break;
	case CCamera::TYPE::SMALL_MAP:
		SmallMapUpdate();
		break;
	default:
		break;
	}
}

//================================================
//生成処理
//================================================
CCamera *CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type)
{
	//インスタンスの生成
	CCamera *pCamera = nullptr;
	if (pCamera == nullptr)
	{
		pCamera = new CCamera;
		if (pCamera != nullptr)
		{
			pCamera->Init(pos, rot, viewportX, viewportY,viewportWidth, viewporHeight, type);
		}
	}
	return pCamera;
}


//=======================================================================
//設定処理
//=======================================================================
void CCamera::Set(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(50.0f),									//画角
								(float)m_viewport.Width / (float)m_viewport.Height,		//比率
								CAMERA_MIN_RENDERER,									//Z方向の描画範囲
								CAMERA_MAX_RENDERER);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//カメラの位置をどれくらい動かすかを決める
	D3DXVECTOR3 sway = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_state)
	{
	case CAMERA_STATE::NORMAL:				//通常
		break;
	case CAMERA_STATE::SWAY_SMALL:			//小さい揺れ
		sway.x = CAMERA_SWAY_SMALL_X_RAND;
		sway.y = CAMERA_SWAY_SMALL_Y_RAND;
		break;
	case CAMERA_STATE::SWAY_LARGE:			//大きい揺れ
		sway.x = CAMERA_SWAY_LARGE_X_RAND;
		sway.y = CAMERA_SWAY_LARGE_Y_RAND;
		break;
	default:
		break;
	}

	D3DXVECTOR3 pos(m_posV.x + sway.x, m_posV.y + sway.y, m_posV.z + sway.z);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &pos, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=======================================================================
//視点取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=======================================================================
//注視点取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=======================================================================
//視点設定処理
//=======================================================================
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//=======================================================================
//注視点設定処理
//=======================================================================
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}

//=======================================================================
//視点の向き取得処理
//=======================================================================
D3DXVECTOR3 CCamera::GetRotV(void)
{
	return m_rot;
}

//=======================================================================
//視点の向き設定処理
//=======================================================================
void CCamera::SetRotV(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=======================================================================
//cameraの個体識別番号設定処理
//=======================================================================
void CCamera::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=======================================================================
//cameraの個体識別番号取得処理
//=======================================================================
int CCamera::GetNum(void)
{
	return m_nNum;
}

//================================================
//回転処理
//================================================
void CCamera::Rotate(void)
{
	//X軸回転させる状態なら
	if (m_bRotateX == true)
	{
		//目的の向きを計算
		if (m_rotAsk.x > D3DX_PI)
		{
			m_rotAsk.x = -D3DX_PI - (D3DX_PI - m_rotAsk.x);
		}
		else if (m_rotAsk.x < -D3DX_PI)
		{
			m_rotAsk.x = D3DX_PI - (-D3DX_PI - m_rotAsk.x);
		}

		//現在の向きごとにそれぞれ向きを変える量を計算
		if (m_rot.x < 0.0f && -m_rot.x + m_rotAsk.x > D3DX_PI)
		{
			m_numRot.x = (-D3DX_PI - m_rot.x) + -(D3DX_PI - m_rotAsk.x);
		}
		else if (m_rot.x >= D3DX_PI / 2.0f && m_rot.x - m_rotAsk.x > D3DX_PI)
		{
			m_numRot.x = (D3DX_PI - m_rot.x) - (-D3DX_PI - m_rotAsk.x);
		}
		else
		{
			m_numRot.x = (m_rotAsk.x - m_rot.x);
		}

		//向きに加算
		m_rot.x += m_numRot.x * 0.2f;

		//既定の値に達したら回転をやめる
		if (m_rot.x - m_rotAsk.x < 0.001f && m_rot.x - m_rotAsk.x > -0.001f)
		{
			m_bRotateX = false;
		}
	}

	//Y軸回転させる状態なら
	if (m_bRotateY == true)
	{
		//目的の向きを計算
		if (m_rotAsk.y > D3DX_PI)
		{
			m_rotAsk.y = -D3DX_PI - (D3DX_PI - m_rotAsk.y);
		}
		else if (m_rotAsk.y < -D3DX_PI)
		{
			m_rotAsk.y = D3DX_PI - (-D3DX_PI - m_rotAsk.y);
		}

		//現在の向きごとにそれぞれ向きを変える量を計算
		if (m_rot.y < 0.0f && -m_rot.y + m_rotAsk.y > D3DX_PI)
		{
			m_numRot.y = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_rotAsk.y);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_rotAsk.y > D3DX_PI)
		{
			m_numRot.y = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_rotAsk.y);
		}
		else
		{
			m_numRot.y = (m_rotAsk.y - m_rot.y);
		}

		//向きに加算
		m_rot.y += m_numRot.y * 0.2f;

		//既定の値に達したら回転をやめる
		if (m_rot.y - m_rotAsk.y < 0.001f && m_rot.y - m_rotAsk.y > -0.001f)
		{
			m_bRotateY = false;
		}
	}

	//πより大きくなったら-2πする
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		m_rot.x += D3DX_PI * 2.0f;
	}

	//πより大きくなったら-2πする
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-πより小さくなったら+2πする
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//メインカメラの更新処理
//================================================
void CCamera::MainCameraUpdate(void)
{
	//パッドD取得処理
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//パッド取得処理
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	//オブジェクト情報を入れるポインタ
	CObject *pThisObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pThisObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pThisObject;
		if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーに追従させる
			D3DXVECTOR3 pos = pThisObject->GetPos();
			m_posR = D3DXVECTOR3(pos.x + sinf(m_rot.y) * 0.0f, pos.y + 70.0f, pos.z + cosf(m_rot.y) * 0.0f);
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//視点の場所を注視点を元に移動
	m_posV.x = m_posR.x + m_fDifferVR * sinf(m_rot.x) * sinf(m_rot.y);
	m_posV.z = m_posR.z + m_fDifferVR * sinf(m_rot.x) * cosf(m_rot.y);
	m_posV.y = m_posR.y + m_fDifferVR * cosf(m_rot.x);

	//マウス取得処理
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//マウスの移動量取得
	D3DXVECTOR2 mouseVelocity = pInputMouse->GetMouseVelocity();

	//================================================
	//マウスによる視点移動処理
	//================================================
	if (mouseVelocity.x != 0.0f)
	{
		m_rot.y += mouseVelocity.x * CAMERA_V__MOUSE_SPEED_Y;
	}
	if (mouseVelocity.y != 0.0f)
	{
		m_rot.x += mouseVelocity.y * CAMERA_V__MOUSE_SPEED_XZ;
	}

	//================================================
	//右スティック処理
	//================================================
	if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_LEFT, m_nNum) == true ||
		(float)pInputPadD->GetGamepad().lZ < 0.0f && m_bRotateY == false)
	{
		m_rot.y -= CAMERA_V_SPEED_Y;
	}
	else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_RIGHT, m_nNum) == true ||
		(float)pInputPadD->GetGamepad().lZ > 0.0f && m_bRotateY == false)
	{
		m_rot.y += CAMERA_V_SPEED_Y;
	}
	if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_UP, m_nNum) == true ||
		(float)pInputPadD->GetGamepad().lRz < 0.0f && m_bRotateX == false)
	{
		m_rot.x += CAMERA_V_SPEED_XZ;
	}
	else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_DOWN, m_nNum) == true ||
		(float)pInputPadD->GetGamepad().lRz > 0.0f && m_bRotateX == false)
	{
		m_rot.x -= CAMERA_V_SPEED_XZ;
	}

	//回転処理
	Rotate();

	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.x >= D3DX_PI / 8.0f * 7.0f)
	{
		m_rot.x = D3DX_PI / 8.0f * 7.0f;
	}
	else if (m_rot.x <= D3DX_PI / 8.0f)
	{
		m_rot.x = D3DX_PI / 8.0f;
	}
}

//================================================
//小マップの更新処理
//================================================
void CCamera::SmallMapUpdate(void)
{
	//オブジェクト情報を入れるポインタ
	CObject *pThisObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pThisObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pThisObject;
		if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーに追従させる
			D3DXVECTOR3 pos = pThisObject->GetPos();
			m_posV = D3DXVECTOR3(pos.x, 5000.0f, pos.z);
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//視点の場所を注視点を元に移動
	m_posV.x = m_posR.x + m_fDifferVR * sinf(m_rot.x) * sinf(m_rot.y);
	m_posV.z = m_posR.z + m_fDifferVR * sinf(m_rot.x) * cosf(m_rot.y);
	m_posV.y = m_posR.y + m_fDifferVR * cosf(m_rot.x);
}
