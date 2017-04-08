#include "stdafx.h"
#include "MapGrid.h"
#include "Entity/Bullet.h"


MapGrid::MapGrid(void)
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_pMap = nullptr;
	m_pBulletHitSink = nullptr;
}


MapGrid::~MapGrid(void)
{
	if ( m_pMap )
	{
		delete[] m_pMap;
		m_pMap = nullptr;
	}
}

bool MapGrid::Initialize(  int nWidth, int nHeight  )
{
	if ( nWidth <= 0 || nHeight <= 0 )
	{
		ASSERT( FALSE );
		return false;
	}

	m_nWidth = nWidth;
	m_nHeight = nHeight;

// 	m_pMap = new Entity* [m_nWidth*m_nHeight];
// 	ZeroMemory( m_pMap, sizeof(Entity*)*(m_nWidth*m_nHeight) );
	m_pMap = new GridUnit[m_nWidth*m_nHeight];

	return true;
}

bool MapGrid::CanMove( Entity* pEntity, int xPos, int yPos )
{
	ASSERT( pEntity != nullptr );
	if ( !pEntity )
	{
		return false;
	}

	int nWidth = pEntity->GetWidth();
	int nHeigth = pEntity->GetHeight();

// 	if ( !IsVaildPos( xPos, yPos, nWidth, nHeigth ) )
// 	{
// 		return false;
// 	}
	

	// 是否有实体占用了
	for ( int i = 0; i < nWidth; ++i )
	{
		for ( int j = 0; j < nHeigth; ++j )
		{
// 			Entity* pEntityTemp = GetEntity( xPos + i, yPos + j );
// 			if ( pEntityTemp && (pEntityTemp != pEntity) )
// 			{
// 				return false;
// 			}
			int nNewX = xPos + i;
			int nNewY = yPos + j;
			if ( !IsVaildPos( nNewX, nNewY ) )
			{
				return false;
			}

			int nIndex = getMapIndex( nNewX, nNewY );
			GridUnit& mUnit = m_pMap[nIndex];
			for( int k = 0; k < mUnit.Count(); ++k )
			{
				if ( pEntity->GetType() == enBullet )
				{
					// 子弹可以穿透一切
					continue;
				}

				if ( pEntity != mUnit.Enum( k ) )
				{
					// 有其它不可穿透的实体占用
					return false;
				}
			}
		}
	}
	
	return true;
}


bool MapGrid::MoveEntity( Entity* pEntity, int xPos, int yPos )
{
	if ( !CanMove( pEntity, xPos, yPos ) )
	{
		return false;
	}
	
	// 从原来的格子里移除
	if ( pEntity->IsInWorld() )//必需的判断：新创建的实体，位置还没初始化
	{
		RemoveEntity( pEntity );
	}
	
	// 移动到新的格子里
	int nWidth = pEntity->GetWidth();
	int nHeight = pEntity->GetHeight();
	int nAddCount = 0;
	for( int i = 0; i < nWidth; ++i )
	{
		for ( int j = 0; j < nHeight; ++j )
		{
			int nIndex = getMapIndex( xPos + i, yPos + j );
			//m_pMap[nIndex] = pEntity;
			GridUnit& mUnit = m_pMap[nIndex];
			mUnit.Add( pEntity );
			++nAddCount;
			
		}
	}
	ASSERT( nAddCount == ( nWidth * nHeight ) );

	POINT newPos;
	newPos.x = xPos;
	newPos.y = yPos;
	pEntity->SetPos( newPos );

	return true;
}

// 
// Entity* MapGrid::GetEntity( int xPos, int yPos )
// {
// 	ASSERT( m_pMap != nullptr );
// 	if ( !m_pMap )
// 	{
// 		return nullptr;
// 	}
// 
// 	if ( !IsVaildPos( xPos, yPos ) )
// 	{
// 		return nullptr;
// 	}
// 
// 	int nIndex = getMapIndex( xPos, yPos );
// 	Entity* pEntityTemp = m_pMap[nIndex];
// 	if (pEntityTemp )
// 	{
// 		if ( pEntityTemp->GetWidth() < 0 )
// 		{
// 			ASSERT( FALSE );
// 		}
// 	}
// 
// 	return pEntityTemp;
// }

// bool MapGrid::IsVaildPos( int xPos, int yPos, int nEntityWidth/* = 0*/,
// 						 int nEntityHeight/* = 0*/ )
// {
// 	// x方向边界检测
// 	if ( xPos < 0 || xPos > ( m_nWidth - nEntityWidth ) ) 
// 	{
// 		return false;
// 	}
// 
// 	// y方向边界检测
// 	if ( yPos < 0 || yPos > ( m_nHeight - nEntityHeight ) )
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }

bool MapGrid::IsVaildPos( int xPos, int yPos )
{
	// x方向边界检测
	if ( xPos < 0 || xPos >= m_nWidth ) 
	{
		return false;
	}

	// y方向边界检测
	if ( yPos < 0 || yPos >= m_nHeight )
	{
		return false;
	}

	return true;
}

bool MapGrid::CanRespawn( int xPos, int yPos, 
				int nEntityWidth, int nEntityHeight )
{
// 	if ( !IsVaildPos( xPos, yPos, nEntityWidth, nEntityHeight ) )
// 	{
// 		return false;
// 	}

	// 是否有实体占用了
	for ( int i = 0; i < nEntityWidth; ++i )
	{
		for ( int j = 0; j < nEntityHeight; ++j )
		{
			int nNewX = xPos + i;
			int nNewY = yPos + j;
			if ( !IsVaildPos( nNewX, nNewY ) )
			{
				return false;
			}

			int nIndex = getMapIndex( nNewX, nNewY );
			GridUnit& mUnit = m_pMap[nIndex];

			//已被占用
			if ( mUnit.Count() > 0 )
			{
				return 0;
			}
// 			Entity* pEntityTemp = GetEntity( xPos + i, yPos + j );
// 			if ( pEntityTemp )
// 			{
// 				return false;
// 			}
		}
	}

	return true;
}


// Entity* MapGrid::GetAdjacentEntity( Entity* pEntity, PosDir enDir )
// {
// 	return nullptr;
// }

void MapGrid::CheckBullteHit( Bullet* pBullet )
{
	if ( !pBullet )
	{
		ASSERT( FALSE );
		return;
	}

	int nWidth = pBullet->GetWidth();
	int nHeight = pBullet->GetHeight();
	POINT mPos = pBullet->GetPos();
	for( int i = 0; i < nWidth; ++i )
	{
		for ( int j = 0; j < nWidth; ++j )
		{
			int nIndex = getMapIndex( mPos.x + i, mPos.y + j );
			GridUnit& mUnit = m_pMap[nIndex];
			

			for ( int k = 0; k < mUnit.Count(); ++k )
			{
				Entity* pEntity = mUnit.Enum( k );
				if ( !pEntity->IsInWorld() || pEntity == pBullet )
				{
					continue;
				}

				// 通知子弹击中事件
				m_pBulletHitSink->OnEventBulletHit( pBullet, pEntity );
			}
		}
	}
}

// 
// void MapGrid::CheckCollision( Entity* pSrcEntity )
// {
// 	if ( !pSrcEntity )
// 	{
// 		return;
// 	}
// 
// 	int nWidth = pSrcEntity->GetWidth();
// 	int nHeight = pSrcEntity->GetHeight();
// 	POINT mPos = pSrcEntity->GetPos();
// 
// 	// 右侧
// 	for( int i = 0; i < nHeight; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x += nWidth;
// 		mPosTemp.y += i;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirRight );
// 	}
// 
// 	// 左侧
// 	for( int i = 0; i < nHeight; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x -= 1;
// 		mPosTemp.y += i;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirLeft );
// 	}
// 
// 	// 上侧
// 	for( int i = 0; i < nWidth; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x += i;
// 		mPosTemp.y -= 1;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirUp );
// 	}
// 
// 	// 下侧
// 	for( int i = 0; i < nWidth; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x += i;
// 		mPosTemp.y += nHeight;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirDown );
// 	}
// 
// }


void MapGrid::RemoveEntity( Entity* pEntity )
{
	if ( !pEntity )
	{
		return;
	}

	int nWidth = pEntity->GetWidth();
	int nHeight = pEntity->GetHeight();

	int nRemoveCnt = 0;

	// 从格子里移除
	POINT oldPos = pEntity->GetPos();
	for( int i = 0; i < nWidth; ++i )
	{
		for ( int j = 0; j < nHeight; ++j )
		{
			int nIndex = getMapIndex( oldPos.x + i, oldPos.y + j );
			GridUnit& mUnit = m_pMap[nIndex];

			if ( (mUnit.Remove(pEntity)) )
			{
				//m_pMap[nIndex] = nullptr;
				++nRemoveCnt;
			}
			else
			{
				ASSERT( FALSE );
			}
		}
	}

	ASSERT( nRemoveCnt == ( nWidth*nHeight ) );
}


int MapGrid::getMapIndex( int xPos, int yPos )
{
	ASSERT( IsVaildPos( xPos, yPos ) );
	return ( yPos * m_nWidth + xPos );
}

// 
// bool MapGrid::isBulletHit( Bullet* pBullet, Entity* pEntity )
// {
// 	if ( !pBullet || !pEntity )
// 	{
// 		return false;
// 	}
// 
// 	//在子弹前进方向上相交，则命中
// 	//（如子弹向右，若实体在子弹的右侧，则命中）
// 	POINT mBltPos = pBullet->GetPos();
// 	POINT mEtyPos = pEntity->GetPos();
// 	switch( pBullet->GetDir() )
// 	{
// 	case enDirRight:
// 		{
// 			if ( (mBltPos.x + pBullet->GetWidth()) == mEtyPos.x )
// 			{
// 				return true;
// 			}
// 			break;
// 		}
// 	case enDirLeft:
// 		{
// 			if ( ( mEtyPos.x + pEntity->GetWidth() ) == mBltPos.x )
// 			{
// 				return true;
// 			}
// 			break;
// 		}
// 	case enDirUp:
// 		{
// 			if ( ( mEtyPos.y + pEntity->GetHeight() ) == mBltPos.y )
// 			{
// 				return true;
// 			}
// 			break;
// 		}
// 	case enDirDown:
// 		{
// 			if ( ( mBltPos.y + pBullet->GetHeight() ) == mEtyPos.y )
// 			{
// 				return true;
// 			}
// 			break;
// 		}
// 	}
// 
// 	return false;
// }


// 
// void MapGrid::checkBulletHitByPos( Entity* pSrcEntity, POINT mCheckPos, PosDir enCheckDir )
// {
// 	if ( !pSrcEntity )
// 	{
// 		return;
// 	}
// 
// 	int nWidth = pSrcEntity->GetWidth();
// 	int nHeight = pSrcEntity->GetHeight();
// 
// 	if ( !IsVaildPos( mCheckPos.x, mCheckPos.y, nWidth, nHeight ) )
// 	{ //子弹是否击中边界
// 		if ( pSrcEntity->GetType() == enBullet &&
// 			pSrcEntity->GetDir() == enCheckDir )
// 		{
// 			// 从网格中移除此实体
// 			//RemoveEntity( pSrcEntity );
// 
// 			// 子弹碰到边界自行爆炸
// 			if ( m_pBulletHitSink )
// 			{
// 				// 通知子弹事件
// 				m_pBulletHitSink->OnEventBulletHit( 
// 					dynamic_cast<Bullet*>(pSrcEntity), 
// 					nullptr );
// 			}
// 		}
// 	}
// 	else
// 	{//子弹是否击中实体或某实体是否被子弹击中
// 		Bullet* pBullet = nullptr;
// 		Entity* pTargetEntity = nullptr;
// 		{
// 			Entity* pCheckPosEntity = GetEntity( mCheckPos.x, mCheckPos.y );
// 			if ( !pCheckPosEntity )
// 			{
// 				return;
// 			}
// 			if ( pSrcEntity->GetType() == enBullet )
// 			{
// 				pBullet = dynamic_cast<Bullet*>(pSrcEntity);
// 				if ( !pBullet )
// 				{
// 					ASSERT( FALSE );
// 					return;
// 				}
// 				pTargetEntity = pCheckPosEntity;
// 			}
// 			else if ( pCheckPosEntity->GetType() == enBullet )
// 			{
// 				pBullet = dynamic_cast<Bullet*>(pCheckPosEntity);
// 				if ( !pBullet )
// 				{
// 					ASSERT( FALSE );
// 					return;
// 				}
// 				pTargetEntity = pSrcEntity;
// 			}
// 		}
// 
// 		if ( !pBullet )
// 		{
// 			return;
// 		}
// 
// 		if ( !isBulletHit( pBullet, pTargetEntity ) )
// 		{
// 			return;
// 		}
// 
// 		Entity* pOwner = pBullet->GetOwner();
// // 		if ( !pOwner )
// // 		{
// // 			ASSERT( FALSE );
// // 			return;
// // 		}
// 
// 		// 同一类型发出的子弹互相不伤害
// 		if ( pOwner && pOwner->GetType() == pTargetEntity->GetType() )
// 		{
// 			// 从网格中移除此实体
// 			//RemoveEntity( pBullet );
// 			if ( m_pBulletHitSink )
// 			{
// 				m_pBulletHitSink->OnEventBulletHit( pBullet, 
// 					nullptr );
// 			}
// 		}
// 		else
// 		{
// 			// 从网格中移除两实体
// 			//RemoveEntity( pBullet );
// 			//RemoveEntity( pTargetEntity );
// 			if ( m_pBulletHitSink )
// 			{
// 				m_pBulletHitSink->OnEventBulletHit( pBullet, 
// 					pTargetEntity );
// 			}
// 		}
// 	}
// }