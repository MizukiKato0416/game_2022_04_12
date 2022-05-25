//===========================================
//��b�̏���
//Author:KatoMizuki
//===========================================
#ifndef _WIND_H_
#define _WIND_H_

#include "object.h"

//�O���錾
class CEffect2D;
class CObject2D;

//================================================
//�}�N����`
//================================================
#define EFFECT_CLICK_RING_NUM	(2)		//�����O�G�t�F�N�g�̐�
#define EFFECT_CLICK_STAR_NUM	(3)		//���G�t�F�N�g�̐�

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffectClick : public CObject
{
public:
	CEffectClick(CObject::PRIORITY Priority = CObject::PRIORITY::CLICK_EFFECT);	//�R���X�g���N�^
	~CEffectClick();															//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffectClick *Create(const D3DXVECTOR3 &pos);

private:
	void Sparkle(void);		//�L���L���G�t�F�N�g�̏���
	void Ring(void);		//�����O�G�t�F�N�g�̏���
	void Star(void);		//���G�t�F�N�g�̏���

	CEffect2D *m_pRing[EFFECT_CLICK_RING_NUM];			//�����O�G�t�F�N�g
	CObject2D *m_pStar[EFFECT_CLICK_STAR_NUM];			//���G�t�F�N�g
	CEffect2D *m_pStarBg[EFFECT_CLICK_STAR_NUM];		//���G�t�F�N�g�̗��̂ڂ���
	CEffect2D *m_pSparkle;								//�L���L���G�t�F�N�g
	D3DXVECTOR3 m_pos;									//�ʒu
	int m_nCounter;										//�J�E���^�[
	float m_fStarDiffer;								//�X�^�[�̒��S����̋���
	float m_fStarRot[EFFECT_CLICK_STAR_NUM];			//�X�^�[�̌���
	D3DXVECTOR3 m_ringAddSize[EFFECT_CLICK_RING_NUM];	//�����O�G�t�F�N�g�̃T�C�Y�̉��Z��	
};

#endif // !_WIND_H_