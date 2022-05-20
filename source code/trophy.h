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
		AIRPLANE = 0,
		FAN,
		REDBULL,
		STARRING,
		THORN,
		ROCKET,
		BANANA,
		TRAMPOLINE,
		M_1000,
		M_5000,
		M_10000,
		MEASUREMENT_IMPOSSIBLE,
		EVENING,
		NIGHT,
		GIRL,
		MAX
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
};

#endif // !_TROPHY_H_