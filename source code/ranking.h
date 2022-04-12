//===========================================
//�����L���O����
//Authore:��������
//===========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "object.h"
#include "number.h"
#include "score.h"

//================================================
//�}�N����`
//================================================
#define MAX_RANKING (6)								//�����L���O�̍ő吔
#define MAX_SCORE_DATA (MAX_RANKING + 1)			//�X�R�A�f�[�^�̍ő吔
#define RANKING_POLYGON_WIDTH (30.0f * 1.4f)		//�|���S���̕�
#define RANKING_POLYGON_HEIGHT (60.0f * 1.4f)		//�|���S���̍���

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CRanking : public CObject
{
public:
	CRanking(CObject::PRIORITY Priority = CObject::PRIORITY::RANKING);		//�R���X�g���N�^
	~CRanking();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CScore *m_apScore[MAX_RANKING];			//�X�R�A�̃|�C���^
	int m_nScore[MAX_SCORE_DATA];			//�X�R�A
	int m_nNowScore;						//����̃X�R�A
	D3DCOLORVALUE	m_col;					//�J���[
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_RANKING_H_