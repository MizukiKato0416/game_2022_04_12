//=============================================================================
//
// �g���t�B�[���[������ [trophy.h]
// Author : �H������
//
//=============================================================================
#ifndef _TROPHY_H_
#define _TROPHY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTrophy : public CObject
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class TROPHY
	{
		AIRPLANE = 0,	// ��s�@
		FAN,			// ��@
		REDBULL,		// ���b�h�u��
		STARRING,		// �X�^�[�����O
		THORN,			// �Ƃ�
		ROCKET,			// ���P�b�g
		BANANA,			// �o�i�i
		TRAMPOLINE,		// �g�����|����
		M_1000,			// 1000m
		M_5000,			// 5000m
		M_10000,		// 10000m
		MEASUREMENT_IMPOSSIBLE,	// ����s�\
		EVENING,		// �[��
		NIGHT,			// ��
		GIRL,			// ���L�q
		HARD,			// �n�[�h
		GROUND,			// �n��
		PLAY_00,		// ���v���C
		PLAY_05,		// 5�v���C
		PLAY_10,		// 10�v���C
		ENDROLL,		// �G���h���[��
		ROCKY_ANGRY,	// ���b�L�[����{��
		KIYO,			// �L���̃u���[�L��
		COMPLETE,		// �R���v���[�g
		MAX				// �ő吔
	};

	CTrophy(PRIORITY priorty = PRIORITY::NONE);	// �f�t�H���g�R���X�g���N�^
	~CTrophy();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:
	CObject2D* m_buck;	// �߂�{�^��
	CObject2D *m_letter;	// �����|���S��
	vector<CObject2D*> m_icon;	// �A�C�R��
	vector<TROPHY> m_type;	// ���̃g���t�B�[��
	int m_count_get_trophy;	// true�̃g���t�B�[��
};

#endif // !_TROPHY_H_