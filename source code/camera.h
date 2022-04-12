//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_CAMERA					(1)						//カメラの最大数
#define MAX_MAIN_CAMERA				(1)						//メインカメラの最大数
#define CAMERA_DISTANCE				(220.0f)				//視点と注視点の距離
#define CAMERA_SMALL_MAP_DISTANCE	(5000.0f)				//小マップの視点と注視点の距離
#define CAMERA_DISTANCE_SPECIAL		(380.0f)				//必殺技を撃つときの視点と注視点の距離
#define CAMERA_ROCK_ON_ROT_X		(1.5f)					//ロックオン時のカメラの向きX
#define CAMERA_INIT_ROT_X			(1.5f)					//カメラの向きX

//================================================
//クラスの定義
//================================================
//クラスの定義
class CCamera
{
public:
	//カメラの状態
	enum class CAMERA_STATE
	{
		NONE = 0,
		NORMAL,			//通常
		SWAY_SMALL,		//小さい揺れ
		SWAY_LARGE,		//大きい揺れ
		MAX
	};

	//カメラの種類
	enum class TYPE
	{
		NONE = 0,
		MAIN,			//メインカメラ
		SMALL_MAP,		//小マップ
		MAX
	};

	//メンバ関数
	CCamera();				//コンストラクタ
	~CCamera();				//デストラクタ

	HRESULT Init(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	static CCamera *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type);
	void Set(void);
	D3DXVECTOR3 GetPosV(void);					//視点取得処理
	D3DXVECTOR3 GetPosR(void);					//注視点取得処理
	void SetPosV(D3DXVECTOR3 pos);				//視点設定処理
	void SetPosR(D3DXVECTOR3 pos);				//注視点設定処理
	D3DXVECTOR3 GetRotV(void);					//視点の向き取得処理
	void SetRotV(D3DXVECTOR3 rot);				//視点の向き設定処理
	void SetNum(int nNum);						//cameraの個体識別番号設定処理
	int GetNum(void);							//cameraの個体識別番号取得処理
	//カメラの状態設定処理
	void SetState(CAMERA_STATE state) { m_state = state; }
	//カメラの状態取得処理
	CAMERA_STATE GetState(void) { return m_state; }
	//ビューポート取得処理
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }
	//ビューマトリックス取得処理
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	//視点と注視点の距離加算処理
	void AddDiffer(float fAddDiffer) { m_fDifferVR += fAddDiffer; }
	//視点と注視点の距離設定処理
	void SetDiffer(float fDiffer) { m_fDifferVR = fDiffer; }
	//視点と注視点の距離取得処理
	float GetDiffer(void) { return m_fDifferVR; }
	//目的の向き設定処理
	void SetRotAsk(D3DXVECTOR3 rotAsk) { m_rotAsk = rotAsk; }
	//カメラをX軸回転させるかどうか設定処理
	void SetRotateX(bool bRotateX) { m_bRotateX = bRotateX; }
	//カメラをY軸回転させるかどうか設定処理
	void SetRotateY(bool bRotateY) { m_bRotateY = bRotateY; }

private:
	//メンバ関数
	void Rotate(void);						//回転処理
	void MainCameraUpdate(void);			//メインカメラの更新処理
	void SmallMapUpdate(void);				//小マップの更新処理

	D3DXVECTOR3 m_posV;						//現在の視点
	D3DXVECTOR3 m_posVDest;					//目的の視点
	D3DXVECTOR3 m_posR;						//現在の注視点
	D3DXVECTOR3 m_posRDest;					//目的の注視点
	D3DXVECTOR3 m_vecU;						//上方向ベクトル
	D3DXVECTOR3 m_rot;						//視点の向き
	D3DXVECTOR3 m_rotAsk;					//目的の向き
	D3DXVECTOR3 m_numRot;					//向きを変える量
	float m_rotDiffer;						//目的の向きとの差
	D3DXMATRIX m_mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					//ビューマトリックス
	D3DVIEWPORT9 m_viewport;				//ビューポート
	D3DXMATRIX m_mtxWorldCamera;			//ワールドマトリックス
	bool m_bRotateX;						//カメラX軸が回転中かどうか
	bool m_bRotateY;						//カメラY軸が回転中かどうか
	int m_nNum;								//cameraの個体識別番号
	CAMERA_STATE m_state;					//カメラの状態
	float m_fDifferVR;						//視点と注視点の距離
	TYPE m_type;							//種類
};

#endif //!_CAMERA_H_

