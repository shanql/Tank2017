#include "stdafx.h"
#include "Resource.h"
#include "BattleWorld.h"
#include "Ai/AiObject.h"
#include "Entity/PlayerTank.h"
#include "Entity/OpposingTank.h"
#include "Entity/EntityBorder.h"
#include "GlobalFunction.h"


using namespace Tank2017;

BattleWorld::BattleWorld(void)
{
}


BattleWorld::~BattleWorld(void)
{
	for ( auto it = m_EntityArray.begin(); 
		it != m_EntityArray.end(); ++it )
	{
		if ( *it  )
		{
			delete (*it);
		}
	}
	m_EntityArray.clear();
}

bool BattleWorld::Initialize( int nWidth, int nHeight)
{
	if ( !m_MapGrid.Initialize( nWidth, nHeight ) )
	{
		return false;
	}

	m_MapGrid.SetBulletHitSink( this );

	int nBorderW = 1; //�߽�ʵ���,��ʱ����Ϊ1
	int nBorderH = 1; //�߽�ʵ���,��ʱ����Ϊ1

	//�����ϡ��±߽�
	for ( int i = 0; i < GetWidth(); ++i )
	{
		int xPos = nBorderW * i;
		int yPos = 0;
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );
		yPos += nBorderH;
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );


		yPos = GetHeight() - nBorderH; 
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );
		yPos -= nBorderH;
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );
	}

	//�������ұ߽�
	for( int i = 2*nBorderH; i < GetHeight() - 2*nBorderH; ++i )
	{
		int xPos = 0;
		int yPos = nBorderH * i;
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );

		xPos = GetWidth() - nBorderW;
		ASSERT( CreateEntity( enEntityBorder, xPos, yPos ) );
	}


	return true;
}

void BattleWorld::RunDraw( CDC* pDc )
{
	if ( !pDc )
	{
		return;
	}

	EntityArray mEntityArrayTemp = m_EntityArray;
	for ( auto it = mEntityArrayTemp.begin(); 
		it != mEntityArrayTemp.end(); ++it )
	{
		Entity* pTemp = *it;
		ASSERT( pTemp != nullptr );
		if ( pTemp && pTemp->IsInWorld() )
		{
			pTemp->Draw( pDc );
		}
	}
}

void BattleWorld::RunLogic()
{
	// ��ײ���
	checkCollision();

	// ��������
	clearWorld();

	// ����ai�߼�
	runAiLogic();

	// ���ɵз�̹��
	autoGenerateOpposingTank();
}


Entity* BattleWorld::CreateEntity( EntityType enEntityType, int xPos, int yPos, 
								  int nSpeed/* = 0 */, PosDir enDir/* = enDirLeft*/ )
{
	Entity* pEntity = nullptr;
	switch( enEntityType )
	{
	case enPlayerTank:
		{
			PlayerTank* pPlayerTank = new PlayerTank;
			pPlayerTank->Initialize( Tank2017::gTankWidth / Tank2017::gGridUnitSize,
				Tank2017::gTankHeight / Tank2017::gGridUnitSize );
			pPlayerTank->LoadEntityBitmap( MAKEINTRESOURCE( IDB_BMP_TANK_PLAYER) );
			pEntity = pPlayerTank;
			break;
		}
	case enBullet:
		{
			Bullet* pBullet = new Bullet;
			pBullet->Initialize( ToMapSize(gBulletScreenW),
				ToMapSize(gBulletScreenH) );
			pEntity = pBullet;
			break;
		}
	case enOpposingTank:
		{
			OpposingTank* pTank = new OpposingTank;
			pTank->Initialize( Tank2017::gTankWidth / Tank2017::gGridUnitSize,
				Tank2017::gTankHeight / Tank2017::gGridUnitSize );
			pTank->LoadEntityBitmap( MAKEINTRESOURCE(IDB_BMP_TANK_OPPOSING) );
			pEntity = pTank;
			break;
		}
	case enEntityBorder:
		{
			Entity* pBorder = new EntityBorder;
			pBorder->Initialize( 1, 1 );
			pEntity = pBorder;
		}

	}

	if ( pEntity )
	{
		pEntity->SetDir( enDir );
		pEntity->SetSpeed( nSpeed );
		pEntity->CreateAi();

		if ( m_MapGrid.MoveEntity( pEntity, xPos, yPos ) )
		{
			enterWorld( pEntity );
		}
		else
		{
			pEntity = nullptr;
		}
	}

	return pEntity;
}

bool BattleWorld::Move( Entity* pEntity, int xPos, int yPos )
{
	if ( m_MapGrid.MoveEntity( pEntity, xPos, yPos ) )
	{
		//m_MapGrid.CheckCollision( pEntity );
		return true;
	}
	return false;
}

bool BattleWorld::ContiuneMove( Entity* pEntity )
{
	if ( !pEntity )
	{
		return false;
	}

	int nStep = pEntity->GetSpeed();
	POINT mPos = pEntity->GetPos();
	switch( pEntity->GetDir() )
	{
	case enDirDown:
		{
			mPos.y += nStep;
			break;
		}
	case enDirUp:
		{
			mPos.y -= nStep;
			break;
		}
	case enDirLeft:
		{
			mPos.x -= nStep;
			break;
		}
	case enDirRight:
		{
			mPos.x += nStep;
			break;
		}
	}

	return Move( pEntity, mPos.x, mPos.y );
}

POINT BattleWorld::GetValidPos( int nEntityWidth, int nEntityHeight )
{
	POINT mPos = { 0, 0 };
	for( int i = 0; i < m_MapGrid.GetWidth(); i += nEntityWidth )
	{
		for( int j = 0; j < m_MapGrid.GetHeight(); j += nEntityHeight )
		{
			if ( m_MapGrid.CanRespawn( i, j, nEntityWidth,
				nEntityHeight ) )
			{
				mPos.x = i;
				mPos.y = j;
				return mPos;
			}
		}
	}

	return mPos;
}

void BattleWorld::OnEventBulletHit( Bullet* pBullet, Entity* pTargetEntity )
{
	if ( !pBullet || !pTargetEntity )
	{
		ASSERT( FALSE );
		return;
	}

	Entity* pBulletOwner = pBullet->GetOwner();

	switch( pTargetEntity->GetType() )
	{
	case enEntityBorder:
		{
			leaveWorld( pBullet );
			break;
		}
	case enBullet:
		{
			Entity* pBulletOwner = pBullet->GetOwner();
			Entity* pTargetOwner = pTargetEntity->GetOwner();
			if ( pBulletOwner && pTargetOwner )
			{
				if ( pBulletOwner->GetType() != pTargetEntity->GetType() )
				{//����ͬ��Ӫ�ӵ�
					leaveWorld( pBullet );
					leaveWorld( pTargetEntity );
				}
			}
			break;
		}
	case enOpposingTank:
	case enPlayerTank:
		{
			Entity* pBulletOwner = pBullet->GetOwner();
			if ( pBulletOwner && 
				pBulletOwner->GetType() != pTargetEntity->GetType() )
			{//�Է��ӵ�
				pTargetEntity->SetHP( pTargetEntity->GetHP() - 1 );
				bool bTargetDead = false;
				if ( pTargetEntity->GetHP() <= 0 )
				{
					pTargetEntity->OnBeenKilled( pBullet );

					if ( pBullet->GetOwner() )
					{
						pBullet->GetOwner()->OnKillTarget( pTargetEntity );
					}
					bTargetDead = true;
				}

				if ( bTargetDead ) 
				{
					leaveWorld( pTargetEntity );
					Tank2017::PlayGameSound( MAKEINTRESOURCE(TANK_BOMB) );
				}
				leaveWorld( pBullet );
			}
		}
	}


//	bool bTargetDead = false;
//
// 	pBullet->SetHP( 0 );
// 	leaveWorld( pBullet );

// 	pBullet->SetHP( pBullet->GetHP() - 1 );
// 	if ( pBullet->GetHP() <= 0 )
// 	{
// 		pBullet->OnBeenKilled( pTargetEntity );
// 
// 		if ( pTargetEntity )
// 		{
// 			pTargetEntity->OnKillTarget(pBullet);
// 		}
// 
// 		leaveWorld( pBullet );
// 	}

// 	if ( pTargetEntity->GetType() != enEntityBorder )//�Ǳ߽�
// 	{
// 		pTargetEntity->SetHP( pTargetEntity->GetHP() - 1 );
// 		if ( pTargetEntity->GetHP() <= 0 )
// 		{
// 			pTargetEntity->OnBeenKilled( pBullet );
// 
// 			if ( pBullet->GetOwner() )
// 			{
// 				pBullet->GetOwner()->OnKillTarget( pTargetEntity );
// 			}
// 
// 			bTargetDead = true;
// 		}
// 	}
// 
// 	// ��ӵ���ߴ��Ƴ��Լ�
// 	if ( pBullet->GetOwner() )
// 	{
// 		pBullet->GetOwner()->RmvFromOwnEntityList( pBullet );
// 	}
// 	// �Ƴ����������ӵ����
// 	pBullet->RmvFromOwnEntityList(nullptr);
// 	leaveWorld( pBullet );
// 	
// 	
// 	if ( bTargetDead )
// 	{
// 		// ��ӵ���ߴ��Ƴ��Լ�
// 		if ( pTargetEntity->GetOwner() )
// 		{
// 			pTargetEntity->GetOwner()->RmvFromOwnEntityList( pTargetEntity );
// 		}
// 		// �Ƴ����������ӵ����
// 		pTargetEntity->RmvFromOwnEntityList(nullptr);
// 
// 		leaveWorld( pTargetEntity );
// 
// 		if ( pTargetEntity )
// 		{
// 			// ��ӵ���ߴ��Ƴ��Լ�
// 			if ( pTargetEntity->GetOwner() )
// 			{
// 				pTargetEntity->GetOwner()->RmvFromOwnEntityList( pTargetEntity );
// 			}
// 			// �Ƴ����������ӵ����
// 			pTargetEntity->RmvFromOwnEntityList(nullptr);
// 
// 			leaveWorld( pTargetEntity );
// 		}	
// 	}

// 	// ������ң���ʱ�޵�
// 	if ( pTargetEntity && pTargetEntity->GetType() != enPlayerTank )
// 	{
// 		leaveWorld( pTargetEntity );
// 	}
	
}


void BattleWorld::enterWorld( Entity* pEntity )
{
	if ( !pEntity )
	{
		return;
	}


	for ( auto it = m_EntityArray.begin(); it != m_EntityArray.end(); ++it )
	{
		if ( *it == pEntity )
		{
			return;
		}
	}

 	m_EntityArray.push_back( pEntity );
	pEntity->SetWorld( this );
	pEntity->SetInWorld( true );
}


void BattleWorld::leaveWorld( Entity* pEntity )
{
	if ( !pEntity )
	{
		return;
	}

	// ��ӵ���ߴ��Ƴ��Լ�
	if ( pEntity->GetOwner() )
	{
		pEntity->GetOwner()->RmvFromOwnEntityList( pEntity );
	}
	// �Ƴ����������ӵ����
	pEntity->RmvFromOwnEntityList(nullptr);

	for ( auto it = m_EntityArray.begin(); it != m_EntityArray.end(); ++it )
	{
		Entity* pTemp = (*it);
		ASSERT( pTemp != nullptr );
		if ( pTemp == pEntity )
		{
			//���������Ƴ���ʵ��
			ASSERT( pEntity->IsInWorld() == true );
			pEntity->SetInWorld( false );

			//���������Ƴ���ʵ��
			m_MapGrid.RemoveEntity( pEntity );
			return;
		}
	}

	ASSERT( FALSE );
}


void BattleWorld::autoGenerateOpposingTank()
{
	int nCount = 0;
	for( auto it = m_EntityArray.begin(); it != m_EntityArray.end(); ++it )
	{
		Entity* pTemp = *it;
		if ( pTemp && pTemp->IsInWorld() &&
			pTemp->GetType() == enOpposingTank )
		{
			++nCount;
		}
	}

	if ( nCount < 15 )
	{
		int nPosX = rand() % GetWidth();
		int nPosY = rand() % GetHeight();
		PosDir enDir = (PosDir)( rand() % 4 + 1 );
		int nSpeed = 1;
		int nRandNum = rand() % 100;
		if ( nRandNum >= 70 )
		{
			nSpeed = 2;
		}
		CreateEntity( enOpposingTank, nPosX, nPosY, nSpeed, enDir );
	}
}

void BattleWorld::runAiLogic()
{
	EntityArray mEntityArrayTemp = m_EntityArray;
	for ( auto it = mEntityArrayTemp.begin(); 
		it != mEntityArrayTemp.end();++it )
	{
		Entity* pTemp = *it;
		ASSERT( pTemp != nullptr );
		if ( pTemp && pTemp->IsInWorld() )
		{
			AiObject* pAi= (*it)->GetAi();
			if ( pAi )
			{
				pAi->Run();
			}
		}
	}
}

void BattleWorld::checkCollision( )
{
	EntityArray mEntityArrayTemp = m_EntityArray;
	for ( auto it = mEntityArrayTemp.cbegin(); 
		it != mEntityArrayTemp.cend(); ++it )
	{
		Entity* pTemp = (*it);
		ASSERT( pTemp != nullptr );
		if ( pTemp && pTemp->IsInWorld() && pTemp->GetType() == enBullet )
		{
			//m_MapGrid.CheckCollision( pTemp );
			m_MapGrid.CheckBullteHit( dynamic_cast<Bullet*>(pTemp) );
		}
	}
}


void BattleWorld::clearWorld()
{
	for ( auto it = m_EntityArray.begin(); 
		it != m_EntityArray.end(); )
	{
		Entity* pTemp = (*it);
		ASSERT( pTemp != nullptr );
		if ( pTemp && pTemp->IsInWorld() )
		{
			++it;
		}
		else
		{
			it = m_EntityArray.erase( it );
			if ( pTemp )
			{
				delete pTemp;
				pTemp = nullptr;
			}
		}
	}
}