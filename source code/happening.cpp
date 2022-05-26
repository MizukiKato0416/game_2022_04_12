//=============================================================================
//
// �n�v�j���O���� [bhappening.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "happening.h"
#include "model_single.h"
#include "model.h"
#include "camera.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define HAPPENING_ADD_CAMERA_POS		(20.0f)		//�J�����̈ʒu���ړ��������
#define HAPPENING_ADD_CAMERA_DIFFER		(-40.0f)	//�J�����̎��_�ƒ����_�̋����𑝂₷��
#define HAPPENING_ZOOM_CAMERA_DIFFER	(400.0f)	//�Y�[�����̃J�����̎��_�ƒ����_�̋���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CHappenig::m_bHit = false;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CHappenig::CHappenig(CObject::PRIORITY Priority) : CObject(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model = nullptr;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CHappenig::~CHappenig()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CHappenig::Init(void)
{
	//���f���̏㒸�_�̈ʒu���擾
	D3DXVECTOR3 vtxPos[8];
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		vtxPos[nCntVtx] = GetModel()->GetModel()->GetVtxPos(nCntVtx);
	}

	//���f���̃T�C�YY�𕗂̃G�t�F�N�g�̃T�C�Y��3����2�������΂�
	vtxPos[0].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[1].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[4].y += HAPPENING_ADD_SIZE_Y;
	vtxPos[5].y += HAPPENING_ADD_SIZE_Y;

	vtxPos[0].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[2].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[4].x -= HAPPENING_ADD_SIZE_X;
	vtxPos[6].x -= HAPPENING_ADD_SIZE_X;

	vtxPos[1].x += HAPPENING_ADD_SIZE_X;
	vtxPos[3].x += HAPPENING_ADD_SIZE_X;
	vtxPos[5].x += HAPPENING_ADD_SIZE_X;
	vtxPos[7].x += HAPPENING_ADD_SIZE_X;

	//�T�C�Y��ݒ�
	for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
	{
		GetModel()->GetModel()->SetVtxPos(nCntVtx, vtxPos[nCntVtx]);
	}

	SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CHappenig::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CHappenig::Update(void)
{
	
}

//=============================================================================
// �`��
//=============================================================================
void CHappenig::Draw(void)
{

}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CHappenig::HitPlayer(void)
{
	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		//�v���C���[��������
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�����蔻�������ݒ�Ȃ�
			if (m_model->GetColl() == true)
			{
				//8���_�̎擾
				D3DXVECTOR3 vtxPos[MODEL_VTX];
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
				{
					vtxPos[nCntVtx] = m_model->GetModel()->GetVtxPos(nCntVtx);
				}

				//8���_�̃��[���h�}�g���b�N�X���擾
				D3DXMATRIX *pVtxMtxWorld = m_model->GetModel()->GetVtxMtxWorld();
				//8���_�̐ݒ�
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++, pVtxMtxWorld++)
				{
					//���[���h�}�g���b�N�X�ݒ�
					m_model->SetMtxWorld();
					//���f���̐ݒ�
					//m_model->GetModel()->SetVtxMtxWorld(vtxPos[nCntVtx], nCntVtx);
					vtxPos[nCntVtx] = D3DXVECTOR3(pVtxMtxWorld->_41, pVtxMtxWorld->_42, pVtxMtxWorld->_43);
				}


				//���_���璸�_�܂ł̃x�N�g���Z�o�p
				D3DXVECTOR3 vtxVec[6][2];
				//���_���璸�_�܂ł̃x�N�g���Z�o
				//���̖�
				vtxVec[0][0] = vtxPos[0] - vtxPos[1];
				vtxVec[0][1] = vtxPos[3] - vtxPos[1];
				//�E�̖�
				vtxVec[1][0] = vtxPos[1] - vtxPos[5];
				vtxVec[1][1] = vtxPos[7] - vtxPos[5];
				//�O�̖�
				vtxVec[2][0] = vtxPos[5] - vtxPos[4];
				vtxVec[2][1] = vtxPos[6] - vtxPos[4];
				//���̖�
				vtxVec[3][0] = vtxPos[4] - vtxPos[0];
				vtxVec[3][1] = vtxPos[2] - vtxPos[0];
				//��̖�
				vtxVec[4][0] = vtxPos[1] - vtxPos[0];
				vtxVec[4][1] = vtxPos[4] - vtxPos[0];
				//���̖�
				vtxVec[5][0] = vtxPos[7] - vtxPos[6];
				vtxVec[5][1] = vtxPos[2] - vtxPos[6];

				//�@���ۑ��p�ϐ�
				D3DXVECTOR3 vecNor[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					//�e�ʂ̖@�������߂�
					D3DXVec3Cross(&vecNor[nCntSurfase], &vtxVec[nCntSurfase][0], &vtxVec[nCntSurfase][1]);

					//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
					D3DXVec3Normalize(&vecNor[nCntSurfase], &vecNor[nCntSurfase]);
				}

				//�Ώۂ̌��݈ʒu�擾
				D3DXVECTOR3 pos = object[count_object]->GetPos();

				//���_�̈ʒu����Ώۂ̌��݂̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPos[6];
				//���̖�
				vecPos[0] = pos - vtxPos[0];
				//�E�̖�
				vecPos[1] = pos - vtxPos[1];
				//�O�̖�
				vecPos[2] = pos - vtxPos[5];
				//���̖�
				vecPos[3] = pos - vtxPos[4];
				//��̖�
				vecPos[4] = pos - vtxPos[1];
				//���̖�
				vecPos[5] = pos - vtxPos[7];

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDot[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					fVecDot[nCntSurfase] = D3DXVec3Dot(&vecNor[nCntSurfase], &vecPos[nCntSurfase]);
				}

				//�S�Ă̓��ς̌v�Z���ʂ��}�C�i�X�̎�
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f &&
					fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f)
				{
					//�������Ă���
					return true;
				}
			}
		}
	}
	return false;
}

//=============================================================================
//�J�������v���C���[���Y�[������
//=============================================================================
void CHappenig::SetCameraZoom(void)
{
	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::PLAYER));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		//�v���C���[��������
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//�v���C���[�̈ʒu���擾
			D3DXVECTOR3 playerPos = object[count_object]->GetPos();
			//�����_���擾
			D3DXVECTOR3 cameraPosR = pCamera->GetPosR();
			//�������߂�
			D3DXVECTOR3 posDiffer = cameraPosR - playerPos;

			if (posDiffer.y > 0.0f)
			{
				cameraPosR.y -= HAPPENING_ADD_CAMERA_POS;
			}
			else if (posDiffer.y < 0.0f)
			{
				cameraPosR.y += HAPPENING_ADD_CAMERA_POS;
			}

			if (posDiffer.y > -HAPPENING_ADD_CAMERA_POS && posDiffer.y < HAPPENING_ADD_CAMERA_POS)
			{
				cameraPosR.y = playerPos.y;
			}

			//�����_���v���C���[�̈ʒu�ɐݒ�
			pCamera->SetPosR(cameraPosR);

			//����̒l�����傫���Ƃ�
			if (pCamera->GetDiffer() > HAPPENING_ZOOM_CAMERA_DIFFER)
			{
				//�J�����̎��_�ƒ����_�̋�������������
				pCamera->AddDiffer(HAPPENING_ADD_CAMERA_DIFFER);
				//�K��l�����������Ȃ�����
				if (pCamera->GetDiffer() < HAPPENING_ZOOM_CAMERA_DIFFER)
				{
					//�J�����̎��_�ƒ����_�̋�����ݒ�
					pCamera->SetDiffer(400.0f);
				}
			}
		}
	}
}

//=============================================================================
//���f���̍폜����
//=============================================================================
void CHappenig::DeleteModel(void)
{
	if (m_model != nullptr)
	{
		m_model->Uninit();
		m_model = nullptr;
	}
}
