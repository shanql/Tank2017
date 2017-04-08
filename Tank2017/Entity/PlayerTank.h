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
	 * @brief 开火
	 * @return 发射成功返回true, 否则返回false
	*/
	bool Fire();

private:
	CBitmap m_bmpImage;			///< 实体图片
};

