#pragma once

#include "PlayerTank.h"

//�з�̹��
class OpposingTank :
	public PlayerTank
{
public:
	OpposingTank(void);
	virtual ~OpposingTank(void);

// 	bool LoadEntityBitmap( LPCTSTR lpszImageId );
// 
// 	virtual void Draw( CDC* pDC ) override;

	virtual void CreateAi() override;

private:
	CBitmap m_bmpImage;			///< ʵ��ͼƬ
};

