//===========================================
//�Q�[�W����
//Author:KatoMizuki
//===========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//�O���錾

//================================================
//�}�N����`
//================================================
#define GAUGE_SHOT_POS_X	(SCREEN_WIDTH / 2.0f - GAUGE_SHOT_SIZE_X / 2.0f)	//�V���b�g�Q�[�W�̈ʒuX
#define GAUGE_SHOT_POS_Y	(33.0f + GAUGE_SHOT_SIZE_Y / 2.0f)					//�V���b�g�Q�[�W�̈ʒuY
#define GAUGE_SHOT_SIZE_X	(608.0f)											//�V���b�g�Q�[�W�̃T�C�YX
#define GAUGE_SHOT_SIZE_Y	(29.0f)												//�V���b�g�Q�[�W�̃T�C�YY

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGauge : public CObject2D
{
public:
	CGauge(CObject::PRIORITY Priority = CObject::PRIORITY::UI);		//�R���X�g���N�^
	~CGauge();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nMaxNum, const int nNum);

	void AddGauge(int nNum);					//�Q�[�W��������
	void SetGauge(int nNum);					//�Q�[�W�ݒ菈��
	int GetGauge(void) { return m_nNum; }		//�Q�[�W�擾����
	void SetMaxNum(int nMaxNum);				//�Q�[�W�ő吔�l�ݒ菈��
	int GetMaxNum(void) { return m_nMaxNum; }	//�Q�[�W�ő吔�l�擾����

private:
	int m_nMaxNum;					//�Q�[�W�̍ő吔�l
	int m_nNum;						//�Q�[�W�̌��ݐ��l
	D3DXVECTOR3 m_sizeMax;			//�T�C�Y�̍ő�l
};

#endif // !_GAUGE_H_