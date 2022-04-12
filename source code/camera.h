//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_CAMERA					(1)						//�J�����̍ő吔
#define MAX_MAIN_CAMERA				(1)						//���C���J�����̍ő吔
#define CAMERA_DISTANCE				(220.0f)				//���_�ƒ����_�̋���
#define CAMERA_SMALL_MAP_DISTANCE	(5000.0f)				//���}�b�v�̎��_�ƒ����_�̋���
#define CAMERA_DISTANCE_SPECIAL		(380.0f)				//�K�E�Z�����Ƃ��̎��_�ƒ����_�̋���
#define CAMERA_ROCK_ON_ROT_X		(1.5f)					//���b�N�I�����̃J�����̌���X
#define CAMERA_INIT_ROT_X			(1.5f)					//�J�����̌���X

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CCamera
{
public:
	//�J�����̏��
	enum class CAMERA_STATE
	{
		NONE = 0,
		NORMAL,			//�ʏ�
		SWAY_SMALL,		//�������h��
		SWAY_LARGE,		//�傫���h��
		MAX
	};

	//�J�����̎��
	enum class TYPE
	{
		NONE = 0,
		MAIN,			//���C���J����
		SMALL_MAP,		//���}�b�v
		MAX
	};

	//�����o�֐�
	CCamera();				//�R���X�g���N�^
	~CCamera();				//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	static CCamera *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type);
	void Set(void);
	D3DXVECTOR3 GetPosV(void);					//���_�擾����
	D3DXVECTOR3 GetPosR(void);					//�����_�擾����
	void SetPosV(D3DXVECTOR3 pos);				//���_�ݒ菈��
	void SetPosR(D3DXVECTOR3 pos);				//�����_�ݒ菈��
	D3DXVECTOR3 GetRotV(void);					//���_�̌����擾����
	void SetRotV(D3DXVECTOR3 rot);				//���_�̌����ݒ菈��
	void SetNum(int nNum);						//camera�̌̎��ʔԍ��ݒ菈��
	int GetNum(void);							//camera�̌̎��ʔԍ��擾����
	//�J�����̏�Ԑݒ菈��
	void SetState(CAMERA_STATE state) { m_state = state; }
	//�J�����̏�Ԏ擾����
	CAMERA_STATE GetState(void) { return m_state; }
	//�r���[�|�[�g�擾����
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }
	//�r���[�}�g���b�N�X�擾����
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	//���_�ƒ����_�̋������Z����
	void AddDiffer(float fAddDiffer) { m_fDifferVR += fAddDiffer; }
	//���_�ƒ����_�̋����ݒ菈��
	void SetDiffer(float fDiffer) { m_fDifferVR = fDiffer; }
	//���_�ƒ����_�̋����擾����
	float GetDiffer(void) { return m_fDifferVR; }
	//�ړI�̌����ݒ菈��
	void SetRotAsk(D3DXVECTOR3 rotAsk) { m_rotAsk = rotAsk; }
	//�J������X����]�����邩�ǂ����ݒ菈��
	void SetRotateX(bool bRotateX) { m_bRotateX = bRotateX; }
	//�J������Y����]�����邩�ǂ����ݒ菈��
	void SetRotateY(bool bRotateY) { m_bRotateY = bRotateY; }

private:
	//�����o�֐�
	void Rotate(void);						//��]����
	void MainCameraUpdate(void);			//���C���J�����̍X�V����
	void SmallMapUpdate(void);				//���}�b�v�̍X�V����

	D3DXVECTOR3 m_posV;						//���݂̎��_
	D3DXVECTOR3 m_posVDest;					//�ړI�̎��_
	D3DXVECTOR3 m_posR;						//���݂̒����_
	D3DXVECTOR3 m_posRDest;					//�ړI�̒����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXVECTOR3 m_rot;						//���_�̌���
	D3DXVECTOR3 m_rotAsk;					//�ړI�̌���
	D3DXVECTOR3 m_numRot;					//������ς����
	float m_rotDiffer;						//�ړI�̌����Ƃ̍�
	D3DXMATRIX m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;				//�r���[�|�[�g
	D3DXMATRIX m_mtxWorldCamera;			//���[���h�}�g���b�N�X
	bool m_bRotateX;						//�J����X������]�����ǂ���
	bool m_bRotateY;						//�J����Y������]�����ǂ���
	int m_nNum;								//camera�̌̎��ʔԍ�
	CAMERA_STATE m_state;					//�J�����̏��
	float m_fDifferVR;						//���_�ƒ����_�̋���
	TYPE m_type;							//���
};

#endif //!_CAMERA_H_

