//================================================
//�L�[�{�[�h���͏���
//Author:��������
//================================================
#include "input_keyboard.h"
#include "input.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyState));
}

//================================================
//�f�X�g���N�^
//================================================
 CInputKeyboard::~ CInputKeyboard()
{

}

//================================================
//����������
//================================================
HRESULT  CInputKeyboard::Init(const HINSTANCE &hInstance, const HWND &hWnd)
{
	CInput::Init(hInstance);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//================================================
//�I������
//================================================
void  CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//================================================
//�X�V����
//================================================
void  CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �ǂ̃L�[�������ꂽ��
//=============================================================================
int CInputKeyboard::GetAllKeyUpdate(void)
{
	bool bTrigger = false;	// �g���K�[�łǂ���������Ă�
	bool bPress = false;	// �v���X�łǂ���������Ă�
	int nKeyCode = 0;	// �z��
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		bPress = (m_aKeyState[nCntKey] & 0x80) ? true : false;
		bTrigger = (m_aKeyStateTrigger[nCntKey] & 0x80) ? true : false;
		if (bPress == true)
		{
			nKeyCode = nCntKey;
			break;
		}
		else if (bTrigger == true)
		{
			nKeyCode = nCntKey;
			break;
		}
	}

	return nKeyCode;
}

//=======================================================================
//�L�[�{�[�h�̓��͏��擾
//=======================================================================
bool CInputKeyboard::GetPress(const int &nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetTrigger(const int &nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetRelease(const int &nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}