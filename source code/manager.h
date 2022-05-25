//===========================================
//�}�l�[�W������
//Author:��������
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "object.h"
#include "camera.h"
#include "light.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CInputPadD;
class CInputMouse;
class CTexture;
class CXload;
class CTitle;
class CGame01;
class CResult;
class CRocketScene;
class CFade;
class CMotionRoad;
class CPlayData;
class CTrophy;
class CSound;
class CEndingScene;
class CDialog;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CManager
{
public:
	//���[�h�̎��
	enum class MODE
	{
		TITLE = 0,		//�^�C�g��
		TROPHY,			//�g���t�B�[���[��
		GAME01,			//�Q�[��01
		ROCKET_SCENE,	//���P�b�g�V�[��
		RESULT,			//���U���g
		ENDING,			//�G���f�B���O
		MAX
	};

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManager *GetInstance(void);											//�C���X�^���X�擾����
	static CRenderer *GetRenderer(void);										//�����_���[�擾����
	static CInputKeyboard *GetInputKeyboard(void);								//�L�[�{�[�h�擾����
	static CInputPadX *GetInputPadX(void);										//�p�b�h(X)�擾����
	static CInputPadD *GetInputPadD(void);										//�p�b�h(D)�擾����
	static CInputMouse *GetInputMouse(void);									//�}�E�X�擾����
	static CLight *GetLight(void);												//���C�g�擾����
	static CTexture *GetTexture(void);											//�e�N�X�`���擾����
	static CCamera** GetCamera(void);											//�J�����擾����
	static CXload *GetXload(void);												//x�t�@�C���ǂݍ��ݎ擾����
	static CTitle *GetTitle(void);												//�^�C�g���擾����
	static CTrophy *GetTrophy(void);											//�g���t�B�[���[���擾����
	static CGame01 *GetGame01(void);											//�Q�[��01�擾����
	static CResult *GetResult(void);											//���U���g�擾����
	static CRocketScene *GetRocketScene(void);									//���P�b�g�V�[���擾����
	static CEndingScene *GetEndingScene(void) { return m_pEndingScene; };		//�G���f�B���O�V�[���擾����
	static void SetMode(MODE mode);												//���[�h�ݒ�
	static MODE GetMode(void);													//���[�h�擾
	static CFade *GetFade(void);												//�t�F�[�h�擾����
	static CMotionRoad *GetMotionRoad(void);									//���[�V�������[�h�擾����
	static CPlayData *GetPlayData(void);										//�v���C�f�[�^�擾����
	static CDialog *GetDialog(void) { return m_pDialog; }						//��b�擾����
	static CSound *GetSound(void) { return m_pSound; }							//�T�E���h�擾����
	static HWND GetWindowHandle(void) { return m_hWnd; }						//hwnd�擾����

private:
	//�����o�֐�
	CManager();				//�R���X�g���N�^
	~CManager();			//�f�X�g���N�^

	static CManager *s_pManager;						//�}�l�[�W���[�̃C���X�^���X
	static CRenderer *m_pRenderer;						//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	static CInputPadX *m_pInputPadX;					//�p�b�h(X)�̃|�C���^
	static CInputPadD *m_pInputPadD;					//�p�b�h(D)�̃|�C���^
	static CInputMouse *m_pInputMouse;					//�}�E�X�̃|�C���^
	static CLight *m_apLight[MAX_LIGHT];				//���C�g�̃|�C���^
	static CTexture *m_pTexture;						//�e�N�X�`���̃|�C���^
	static CCamera* m_apCamera[MAX_CAMERA];				//�J�����̃|�C���^
	static CXload *m_pXload;							//x�t�@�C���ǂݍ��݂̃|�C���^
	static CTitle *m_pTitle;							//�^�C�g���̃|�C���^
	static CTrophy *m_pTrophy;							//�g���t�B�[���̃|�C���^
	static CGame01 *m_pGame01;							//�Q�[��01�̃|�C���^
	static CResult *m_pResult;							//���U���g�̃|�C���^
	static CRocketScene *m_pRocketScene;				//���P�b�g�V�[���̃|�C���^
	static CEndingScene *m_pEndingScene;				//�G���f�B���O�V�[���̃|�C���^
	static MODE m_mode;									//���[�h
	static CFade *m_pFade;								//�t�F�[�h�̃|�C���^
	static CMotionRoad *m_pMotionRoad;					//���[�V�������[�h�̃|�C���^
	static CPlayData *m_pPlayData;						//�v���C�f�[�^�̃|�C���^
	static CDialog *m_pDialog;							//��b�̃|�C���^
	static CSound *m_pSound;							//�T�E���h
	static HWND m_hWnd;									//�E�B���h�E�n���h��
};


#endif // !_MANAGER_H_