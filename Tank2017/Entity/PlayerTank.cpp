#include "stdafx.h"
#include "PlayerTank.h"
#include "../MapGrid.h"
#include "../BattleWorld.h"
#include "GlobalFunction.h"


PlayerTank::PlayerTank(void)
{
	m_enType = enPlayerTank;
}


PlayerTank::~PlayerTank(void)
{
}

bool PlayerTank::LoadEntityBitmap( LPCTSTR lpszImageId )
{
	if ( !lpszImageId )
	{
		return false;
	}

	if ( !m_bmpImage.LoadBitmap( lpszImageId ) )
	{
		return false;
	}

	return true;
}

void PlayerTank::Draw( CDC* pDC ) 
{
	if ( !pDC )
	{
		return;
	}
	CDC buffDC;
	buffDC.CreateCompatibleDC( pDC );
	CBitmap* pOldBmp = buffDC.SelectObject( &m_bmpImage );
	int nIndex = -1;
	switch( m_Dir )
	{
	case enDirUp:
		{
			nIndex = 0;
			break;
		}
	case enDirDown:
		{
			nIndex = 2;
			break;
		}
	case enDirLeft:
		{
			nIndex = 3;
			break;
		}
	case enDirRight:
		{
			nIndex = 1;
			break;
		}
	}

	if ( nIndex >= 0 )
	{
// 		pDC->BitBlt( m_Pos.x, m_Pos.y, m_nWidth, m_nHeight, 
// 			&buffDC, nIndex*m_nWidth, 0, SRCCOPY );
		BITMAP mMapInfo;
		m_bmpImage.GetBitmap( &mMapInfo );
		int nWidth = mMapInfo.bmWidth / 4;
		int nHeight = mMapInfo.bmHeight;

		CDC buff2DC;
		buff2DC.CreateCompatibleDC( pDC );
		CBitmap mBuff2Bmp;
		mBuff2Bmp.CreateCompatibleBitmap( pDC, nWidth, nHeight );
		CBitmap* pBuff2OldBmp = buff2DC.SelectObject( &mBuff2Bmp );

		//先在画在buff2DC上，后面进行缩放拉伸
		::TransparentBlt(
			buff2DC,//*pDC, 
			0,//m_Pos.x * Tank2017::gGridUnitSize,
			0,//m_Pos.y * Tank2017::gGridUnitSize, 
			nWidth,
			nHeight, 
			buffDC,
			nIndex*nWidth,
			0,
			nWidth,
			nHeight,
			RGB( 255, 255, 255 ) );

		::StretchBlt( 
			*pDC,
			m_Pos.x * Tank2017::gGridUnitSize,
			m_Pos.y * Tank2017::gGridUnitSize,
			GetWidth() * Tank2017::gGridUnitSize,
			GetHeight() * Tank2017::gGridUnitSize,
			buff2DC,
			0,//nIndex*nWidth,
			0,
			nWidth,
			nHeight,
			SRCCOPY );

		buff2DC.SelectObject( pBuff2OldBmp );
	}

	buffDC.SelectObject( pOldBmp );
}

bool PlayerTank::Fire()
{
	BattleWorld* pWorld = this->GetWorld();
	if ( !pWorld )
	{
		return false;
	}

	// 获取子弹位置及方向 
	POINT mPos = this->GetPos();
	int nBulletH = Tank2017::ToMapSize( Tank2017::gBulletScreenH); // Tank2017::gBulletHeight / Tank2017::gGridUnitSize;
	int nBulletW = Tank2017::ToMapSize( Tank2017::gBulletScreenW);//Tank2017::gBulletWidth / Tank2017::gGridUnitSize;
	switch( this->GetDir() )
	{
	case enDirRight:
		{
			mPos.x += this->GetWidth();
			mPos.y += this->GetHeight() / 2 - nBulletH / 2;
			break;
		}
	case enDirLeft:
		{
			mPos.x -= nBulletW;
			mPos.y += this->GetHeight() / 2 - nBulletH / 2;
			break;
		}
	case enDirUp:
		{
			mPos.x += this->GetWidth() / 2 - nBulletW  / 2;
			mPos.y -= nBulletH;
			break;
		}
	case enDirDown:
		{
			mPos.x += this->GetWidth() / 2 - nBulletW / 2;
			mPos.y += this->GetHeight();
			break;
		}
	}

	Entity* pEntity = pWorld->CreateEntity( enBullet,
		mPos.x, mPos.y, 1, this->GetDir() ); 
	// TODO:这里子弹设置成1, 不然有问题，子弹两格一移动，碰撞检测会出问题
	if ( pEntity )
	{
		Bullet* pBullet = dynamic_cast<Bullet*>(pEntity);
		if ( pBullet )
		{
			//pBullet->SetOwner( this );
			this->AddToOwnEntityList( pBullet );
			return true;
		}
		else
		{
			ASSERT( FALSE );
		}

	}
	
	return false;
}