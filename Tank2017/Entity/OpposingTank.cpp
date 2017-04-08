#include "stdafx.h"
#include "OpposingTank.h"
#include "../MapGrid.h"
#include "Ai/OpposingTankAi.h"


OpposingTank::OpposingTank(void)
{
	m_enType = enOpposingTank;
}


OpposingTank::~OpposingTank(void)
{
}


// bool OpposingTank::LoadEntityBitmap( LPCTSTR lpszImageId )
// {
// 	if ( !lpszImageId )
// 	{
// 		return false;
// 	}
// 
// 	if ( !m_bmpImage.LoadBitmap( lpszImageId ) )
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }
// 
// void OpposingTank::Draw( CDC* pDC ) 
// {
// 	if ( !pDC )
// 	{
// 		return;
// 	}
// 	CDC buffDC;
// 	buffDC.CreateCompatibleDC( pDC );
// 	CBitmap* pOldBmp = buffDC.SelectObject( &m_bmpImage );
// 	int nIndex = -1;
// 	switch( m_Dir )
// 	{
// 	case enDirUp:
// 		{
// 			nIndex = 0;
// 			break;
// 		}
// 	case enDirDown:
// 		{
// 			nIndex = 2;
// 			break;
// 		}
// 	case enDirLeft:
// 		{
// 			nIndex = 3;
// 			break;
// 		}
// 	case enDirRight:
// 		{
// 			nIndex = 1;
// 			break;
// 		}
// 	}
// 
// 	if ( nIndex >= 0 )
// 	{
// 		BITMAP mMapInfo;
// 		m_bmpImage.GetBitmap( &mMapInfo );
// 		int nWidth = mMapInfo.bmWidth / 4;
// 		int nHeight = mMapInfo.bmHeight;
// 		::TransparentBlt(
// 			*pDC, 
// 			m_Pos.x * Tank2017::gGridUnitSize,
// 			m_Pos.y * Tank2017::gGridUnitSize, 
// 			nWidth,
// 			nHeight, 
// 			buffDC,
// 			nIndex*nWidth,
// 			0,
// 			nWidth,
// 			nHeight,
// 			RGB( 255, 255, 255 ) );
// 	}
// 
// 	buffDC.SelectObject( pOldBmp );
// }


void OpposingTank::CreateAi()
{
	m_pAi = new OpposingTankAi( this );
}
