#pragma once
#include "entity.h"


class PlayerTank :
	public Entity
{
public:
	PlayerTank(void);
	virtual ~PlayerTank(void);

	bool LoadEntityBitmap( LPCTSTR lpszImageId );

	virtual void Draw( CDC* pDC ) override;
	//virtual void InitSize( const BITMAP& entityBmp ) override;

	/**
	 * @brief ����
	 * @return ����ɹ�����true, ���򷵻�false
	*/
	bool Fire();

private:
	CBitmap m_bmpImage;			///< ʵ��ͼƬ
};

