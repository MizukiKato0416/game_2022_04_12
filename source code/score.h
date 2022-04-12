//===========================================
//�X�R�A����
//Authore:��������
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "object.h"
#include "number.h"

//================================================
//�}�N����`
//================================================
#define MAX_SCORE_POLYGON (8)				//�|���S���̍ő吔
#define SCORE_POLYGON_WIDTH (30.0f)			//�|���S���̕�
#define SCORE_POLYGON_HEIGHT (60.0f)		//�|���S���̍���

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScore : public CObject
{
public:
	CScore(int nPriority = PRIORITY_UI);	//�R���X�g���N�^
	~CScore();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void);
	CNumber *GetNumber(int nNumber);

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//number�̃C���X�^���X
	int m_nScore;									//�X�R�A
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_size;								//�T�C�Y

};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SCORE_H_