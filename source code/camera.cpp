//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
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
//�}�N����`
//========================================================
#define CAMERA_V_SPEED_Y			(0.03f)									//�J�����̉��ړ��X�s�[�h
#define CAMERA_V__MOUSE_SPEED_Y		(0.003f)								//�J�����̉��ړ��X�s�[�h�i�}�E�X�̎��j
#define CAMERA_V_SPEED_XZ			(0.01f)									//�J�����̏c�ړ��X�s�[�h
#define CAMERA_V__MOUSE_SPEED_XZ	(-0.001f)								//�J�����̉��ړ��X�s�[�h�i�}�E�X�̎��j
#define CAMERA_RESULT_DISTANCE		(200.0f)								//���U���g�̎��_�ƒ����_�̋���
#define CAMERA_V_MAX_POS_Y			(400.0f)								//���_��y���W�ő�l
#define CAMERA_V_MIN_POS_Y			(50.0f)									//���_��y���W�ŏ��l
#define CAMERA_MAX_RENDERER			(200000.0f)								//camera�ł̕`��ő�Z�l
#define CAMERA_MIN_RENDERER			(50.0f)									//camera�ł̕`��ŏ�Z�l
#define CAMERA_SWAY_SMALL_X_RAND	(float (rand() % 200 + -100) / 100)		//�h�ꕝ(x���W)�����߂邽�߂̃����_���l
#define CAMERA_SWAY_SMALL_Y_RAND	(float (rand() % 200 + -100) / 100)		//�h�ꕝ(y���W)�����߂邽�߂̃����_���l
#define CAMERA_SWAY_LARGE_X_RAND	(float (rand() % 600 + -300) / 100)		//�h�ꕝ(x���W)�����߂邽�߂̃����_���l
#define CAMERA_SWAY_LARGE_Y_RAND	(float (rand() % 1200 + -600) / 100)	//�h�ꕝ(y���W)�����߂邽�߂̃����_���l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̃J�����̌���
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�@��
	m_numRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������ς����
	m_rotDiffer = 0.0f;								//�ړI�ƌ����̍�
	m_viewport.X = (DWORD)0.0f;						//�`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)0.0f;						//�`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;							//�`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 0.0f;							//�`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)0.0f;					//�`�悷���ʂ̕�
	m_viewport.Height = (DWORD)0.0f;				//�`�悷���ʂ̍���
	m_bRotateX = false;								//�J����X������]���Ă��邩�ǂ���
	m_bRotateY = false;								//�J����Y������]���Ă��邩�ǂ���
	m_nNum = 0;										//camera�̌̎��ʔԍ�
	m_state = CAMERA_STATE::NONE;					//�J�����̏��
	m_fDifferVR = 0.0f;								//���_�ƒ����_�̋���
	m_type = TYPE::NONE;							//���
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CCamera::~CCamera()
{

}

//================================================
//����������
//================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type)
{
	m_rot = rot;																	//�J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̃J�����̌���
	m_posV = pos;									//���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//�@��
	m_numRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//������ς����
	m_rotDiffer = 0.0f;								//�ړI�ƌ����̍�
	m_viewport.X = (DWORD)viewportX;				//�`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)viewportY;				//�`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;							//�`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 1.0f;							//�`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)viewportWidth;		//�`�悷���ʂ̕�
	m_viewport.Height = (DWORD)viewporHeight;		//�`�悷���ʂ̍���
	m_bRotateX = false;								//�J����X������]���Ă��邩�ǂ���
	m_bRotateY = false;								//�J����Y������]���Ă��邩�ǂ���
	m_state = CAMERA_STATE::NORMAL;					//�J�����̏��
	m_type = type;									//���

	if (m_type == TYPE::MAIN)
	{
		//���_�̏ꏊ�𒍎��_�����Ɉړ�
		m_fDifferVR = CAMERA_DISTANCE;
		m_posV.x = m_posR.x + sinf(m_rot.y) * m_fDifferVR;
		m_posV.z = m_posR.z + cosf(m_rot.y) * m_fDifferVR;
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CCamera::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CCamera::Update(void)
{
	//�J�����̎�ނɂ���ĕ�����
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
//��������
//================================================
CCamera *CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight, TYPE type)
{
	//�C���X�^���X�̐���
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
//�ݒ菈��
//=======================================================================
void CCamera::Set(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(50.0f),									//��p
								(float)m_viewport.Width / (float)m_viewport.Height,		//�䗦
								CAMERA_MIN_RENDERER,									//Z�����̕`��͈�
								CAMERA_MAX_RENDERER);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�J�����̈ʒu���ǂꂭ�炢�������������߂�
	D3DXVECTOR3 sway = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_state)
	{
	case CAMERA_STATE::NORMAL:				//�ʏ�
		break;
	case CAMERA_STATE::SWAY_SMALL:			//�������h��
		sway.x = CAMERA_SWAY_SMALL_X_RAND;
		sway.y = CAMERA_SWAY_SMALL_Y_RAND;
		break;
	case CAMERA_STATE::SWAY_LARGE:			//�傫���h��
		sway.x = CAMERA_SWAY_LARGE_X_RAND;
		sway.y = CAMERA_SWAY_LARGE_Y_RAND;
		break;
	default:
		break;
	}

	D3DXVECTOR3 pos(m_posV.x + sway.x, m_posV.y + sway.y, m_posV.z + sway.z);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &pos, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=======================================================================
//���_�擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=======================================================================
//�����_�擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=======================================================================
//���_�ݒ菈��
//=======================================================================
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//=======================================================================
//�����_�ݒ菈��
//=======================================================================
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}

//=======================================================================
//���_�̌����擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetRotV(void)
{
	return m_rot;
}

//=======================================================================
//���_�̌����ݒ菈��
//=======================================================================
void CCamera::SetRotV(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=======================================================================
//camera�̌̎��ʔԍ��ݒ菈��
//=======================================================================
void CCamera::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=======================================================================
//camera�̌̎��ʔԍ��擾����
//=======================================================================
int CCamera::GetNum(void)
{
	return m_nNum;
}

//================================================
//��]����
//================================================
void CCamera::Rotate(void)
{
	//X����]�������ԂȂ�
	if (m_bRotateX == true)
	{
		//�ړI�̌������v�Z
		if (m_rotAsk.x > D3DX_PI)
		{
			m_rotAsk.x = -D3DX_PI - (D3DX_PI - m_rotAsk.x);
		}
		else if (m_rotAsk.x < -D3DX_PI)
		{
			m_rotAsk.x = D3DX_PI - (-D3DX_PI - m_rotAsk.x);
		}

		//���݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
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

		//�����ɉ��Z
		m_rot.x += m_numRot.x * 0.2f;

		//����̒l�ɒB�������]����߂�
		if (m_rot.x - m_rotAsk.x < 0.001f && m_rot.x - m_rotAsk.x > -0.001f)
		{
			m_bRotateX = false;
		}
	}

	//Y����]�������ԂȂ�
	if (m_bRotateY == true)
	{
		//�ړI�̌������v�Z
		if (m_rotAsk.y > D3DX_PI)
		{
			m_rotAsk.y = -D3DX_PI - (D3DX_PI - m_rotAsk.y);
		}
		else if (m_rotAsk.y < -D3DX_PI)
		{
			m_rotAsk.y = D3DX_PI - (-D3DX_PI - m_rotAsk.y);
		}

		//���݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
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

		//�����ɉ��Z
		m_rot.y += m_numRot.y * 0.2f;

		//����̒l�ɒB�������]����߂�
		if (m_rot.y - m_rotAsk.y < 0.001f && m_rot.y - m_rotAsk.y > -0.001f)
		{
			m_bRotateY = false;
		}
	}

	//�΂��傫���Ȃ�����-2�΂���
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		m_rot.x += D3DX_PI * 2.0f;
	}

	//�΂��傫���Ȃ�����-2�΂���
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{	//-�΂�菬�����Ȃ�����+2�΂���
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//���C���J�����̍X�V����
//================================================
void CCamera::MainCameraUpdate(void)
{
	//�p�b�hD�擾����
	CInputPadD *pInputPadD = CManager::GetInstance()->GetInputPadD();
	DIJOYSTATE2 JoyStick = pInputPadD->GetGamepad();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInstance()->GetInputPadX();

	//�I�u�W�F�N�g��������|�C���^
	CObject *pThisObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pThisObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pThisObject;
		if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�v���C���[�ɒǏ]������
			D3DXVECTOR3 pos = pThisObject->GetPos();
			m_posR = D3DXVECTOR3(pos.x + sinf(m_rot.y) * 0.0f, pos.y + 70.0f, pos.z + cosf(m_rot.y) * 0.0f);
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//���_�̏ꏊ�𒍎��_�����Ɉړ�
	m_posV.x = m_posR.x + m_fDifferVR * sinf(m_rot.x) * sinf(m_rot.y);
	m_posV.z = m_posR.z + m_fDifferVR * sinf(m_rot.x) * cosf(m_rot.y);
	m_posV.y = m_posR.y + m_fDifferVR * cosf(m_rot.x);

	//�}�E�X�擾����
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�}�E�X�̈ړ��ʎ擾
	D3DXVECTOR2 mouseVelocity = pInputMouse->GetMouseVelocity();

	//================================================
	//�}�E�X�ɂ�鎋�_�ړ�����
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
	//�E�X�e�B�b�N����
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

	//��]����
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
//���}�b�v�̍X�V����
//================================================
void CCamera::SmallMapUpdate(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CObject *pThisObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pThisObject = pThisObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pThisObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pThisObject;
		if (pThisObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�v���C���[�ɒǏ]������
			D3DXVECTOR3 pos = pThisObject->GetPos();
			m_posV = D3DXVECTOR3(pos.x, 5000.0f, pos.z);
		}
		pThisObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//���_�̏ꏊ�𒍎��_�����Ɉړ�
	m_posV.x = m_posR.x + m_fDifferVR * sinf(m_rot.x) * sinf(m_rot.y);
	m_posV.z = m_posR.z + m_fDifferVR * sinf(m_rot.x) * cosf(m_rot.y);
	m_posV.y = m_posR.y + m_fDifferVR * cosf(m_rot.x);
}
