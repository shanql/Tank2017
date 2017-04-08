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
	

	// �Ƿ���ʵ��ռ����
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
					// �ӵ����Դ�͸һ��
					continue;
				}

				if ( pEntity != mUnit.Enum( k ) )
				{
					// ���������ɴ�͸��ʵ��ռ��
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
	
	// ��ԭ���ĸ������Ƴ�
	if ( pEntity->IsInWorld() )//������жϣ��´�����ʵ�壬λ�û�û��ʼ��
	{
		RemoveEntity( pEntity );
	}
	
	// �ƶ����µĸ�����
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
// 	// x����߽���
// 	if ( xPos < 0 || xPos > ( m_nWidth - nEntityWidth ) ) 
// 	{
// 		return false;
// 	}
// 
// 	// y����߽���
// 	if ( yPos < 0 || yPos > ( m_nHeight - nEntityHeight ) )
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }

bool MapGrid::IsVaildPos( int xPos, int yPos )
{
	// x����߽���
	if ( xPos < 0 || xPos >= m_nWidth ) 
	{
		return false;
	}

	// y����߽���
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

	// �Ƿ���ʵ��ռ����
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

			//�ѱ�ռ��
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

				// ֪ͨ�ӵ������¼�
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
// 	// �Ҳ�
// 	for( int i = 0; i < nHeight; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x += nWidth;
// 		mPosTemp.y += i;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirRight );
// 	}
// 
// 	// ���
// 	for( int i = 0; i < nHeight; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x -= 1;
// 		mPosTemp.y += i;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirLeft );
// 	}
// 
// 	// �ϲ�
// 	for( int i = 0; i < nWidth; ++i )
// 	{
// 		POINT mPosTemp = mPos;
// 		mPosTemp.x += i;
// 		mPosTemp.y -= 1;
// 		checkBulletHitByPos( pSrcEntity, mPosTemp, enDirUp );
// 	}
// 
// 	// �²�
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

	// �Ӹ������Ƴ�
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
// 	//���ӵ�ǰ���������ཻ��������
// 	//�����ӵ����ң���ʵ�����ӵ����Ҳ࣬�����У�
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
// 	{ //�ӵ��Ƿ���б߽�
// 		if ( pSrcEntity->GetType() == enBullet &&
// 			pSrcEntity->GetDir() == enCheckDir )
// 		{
// 			// ���������Ƴ���ʵ��
// 			//RemoveEntity( pSrcEntity );
// 
// 			// �ӵ������߽����б�ը
// 			if ( m_pBulletHitSink )
// 			{
// 				// ֪ͨ�ӵ��¼�
// 				m_pBulletHitSink->OnEventBulletHit( 
// 					dynamic_cast<Bullet*>(pSrcEntity), 
// 					nullptr );
// 			}
// 		}
// 	}
// 	else
// 	{//�ӵ��Ƿ����ʵ���ĳʵ���Ƿ��ӵ�����
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
// 		// ͬһ���ͷ������ӵ����಻�˺�
// 		if ( pOwner && pOwner->GetType() == pTargetEntity->GetType() )
// 		{
// 			// ���������Ƴ���ʵ��
// 			//RemoveEntity( pBullet );
// 			if ( m_pBulletHitSink )
// 			{
// 				m_pBulletHitSink->OnEventBulletHit( pBullet, 
// 					nullptr );
// 			}
// 		}
// 		else
// 		{
// 			// ���������Ƴ���ʵ��
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