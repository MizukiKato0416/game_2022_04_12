//===========================================
//会話の処理
//Author:KatoMizuki
//===========================================
#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "object.h"
#include "object2D.h"
#include "manager.h"

//前方宣言
class CLetter;
class CNextDialogUI;

//================================================
//マクロ定義
//================================================

//================================================
//構造体の定義
//================================================
//会話の構成
typedef struct
{
	int nPersonPose;		//キャラポーズ
	int nPersonFace;		//キャラ顔
	int nFrame;				//フレーム

} DIALOG_BODY;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CDialog : public CObject
{
public:
	//ポーズの種類
	enum class POSE
	{
		NORMAL = 0,	    //仁王立ち
		DOMINATE,	    //腰に手を当てる
		HNDS_UP,	    //両手を挙げる
		MAX
	};
	//顔の種類
	enum class FACE
	{
		SMILE = 0,		//笑顔
		SURPRISE,		//驚き
		EMBARRASSED,	//照れ
		STUNNED,		//呆然
		ANGER,			//怒り
		CRY,			//泣き
		MELTS,			//とろけ顔
		MAX
	};
	//フレームの種類
	enum class FRAME
	{
		NORMAL = 0,		//普通
		MAX
	};
	//会話文を出すシーンの種類
	enum class SCENE_TYPE
	{
		NONE = 0,
		CLICK_SCENE,		//クリック連打のシーン
		ENDROLL_SCENE,		//エンドロールのシーン
		MAX
	};

	CDialog(CObject::PRIORITY Priority = CObject::PRIORITY::DIALOG);	//コンストラクタ
	~CDialog();															//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDialog *Create(const SCENE_TYPE &sceneType);
	bool Dialog(const int &nCntDialog);		//セリフ処理
	void UninitDialog(void);				//セリフ破棄処理
	void SetDialog(const int &nNumDialog);	//セリフ設定処理
	//全文が表示されたかどうか設定処理
	void SetDialogFinish(bool bDialogFinish) { m_bDialogFinish = bDialogFinish; }
	//全文が表示されたかどうか取得処理
	bool GetDialogFinish(void) { return m_bDialogFinish; }

private:
	vector<DIALOG_BODY> m_dialogBody;	//会話の構成
	vector<CLetter*> m_pLetter;			//レターのポインタ
	vector<wstring> m_dialog;			//セリフ
	int m_nDialogDelay;					//セリフのディレイ
	int m_nDialogCntX;					//セリフの行のカウンター
	int m_nDialogCntY;					//セリフの列のカウンター
	int m_nLetterCreateCounter;			//1文字を出すまでの時間
	CObject2D* m_pPersonPose;			//ポーズのポインタ
	CObject2D* m_pPersonFace;			//顔のポインタ
	CObject2D* m_pFrame;				//フレームのポインタ
	POSE m_poseType;					//ポーズの種類
	FACE m_faceType;					//顔の種類
	FRAME m_frameType;					//フレームの種類
	bool m_bCreateFinish;				//枠組みを作り終えたかどうか
	int m_nDialogNum;					//何番目のセリフを生成しているか
	CNextDialogUI *m_pNextDialogUI;		//次のセリフに行くUIのポインタ
	int m_nCountFrame;					//フレームのカウンタ
	bool m_bDialogFinish;				//全文が表示されたかどうか
	int m_nMaxDialog;					//総数
	SCENE_TYPE m_sceneType;				//会話を出すシーンの種類
	bool m_bRead;						//読み込み始めるかどうか
	CManager::MODE m_nextScene;			//シーンの遷移先
	bool m_bUninit;						//消すかどうか
};
#endif // !_DIALOG_H_