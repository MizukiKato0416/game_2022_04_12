//===========================================
//�����L���O����
//Authore:��������
//===========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "object.h"
#include "number.h"
#include "score.h"

//�O���錾
class CTcpClient;
class CCommunicationData;

//================================================
//�}�N����`
//================================================
#define MAX_RANKING (6)								//�����L���O�̍ő吔
#define MAX_SCORE_DATA (MAX_RANKING + 1)			//�X�R�A�f�[�^�̍ő吔
#define RANKING_POLYGON_WIDTH (30.0f * 1.0f)		//�|���S���̕�
#define RANKING_POLYGON_HEIGHT (60.0f * 1.0f)		//�|���S���̍���

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
	bool GetConnect(void) { return m_bConnect; }
	bool GetOnece(void) { return m_bOnece; }

	static CRanking *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);
	static void Connect(CTcpClient *pCommu, CCommunicationData *pCommuData, D3DXVECTOR3 pos, D3DXVECTOR3 size, bool *bConnect, bool *bOnece);
	static void CreateScore(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static CScore *m_apScore[MAX_RANKING];	//�X�R�A�̃|�C���^
	CTcpClient *m_pCommu;					//�ʐM�p
	CCommunicationData *m_pCommuData;		//�ʐM�f�[�^
	int m_nScore[MAX_SCORE_DATA];			//�X�R�A
	int m_nNowScore;						//����̃X�R�A
	bool m_bConnect;						//�ʐM�ł�����
	bool m_bOnece;							//��񂾂�
	D3DCOLORVALUE	m_col;					//�J���[
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_RANKING_H_