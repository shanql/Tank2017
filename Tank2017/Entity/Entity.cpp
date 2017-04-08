#include "stdafx.h"
#include "Entity.h"
#include "../MapGrid.h"
#include "../Ai/AiObject.h"


Entity::Entity(void)
{
	m_Pos = POINT();
	m_Dir = enDirLeft;
	m_enType = enEntityNull;
	m_nHeight = 1;
	m_nWidth = 1;
	m_nSpeed = 0;
	m_bInWorld = false;
	m_nHP = 1;
	m_pWorld = nullptr;
	m_pAi = nullptr;
	m_pOwner = nullptr;
}


Entity::~Entity(void)
{
	if ( m_pAi )
	{
		delete m_pAi;
		m_pAi = nullptr;
	}
}

bool Entity::Initialize( int nWidth, int nHeight )
{
	if ( nWidth < 0 || nHeight < 0 )
	{
		ASSERT( FALSE );
		return false;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	return true;
}

void Entity::RegisterEventObserver( IEntityEvent* pEventObserver )
{
	for( auto it = m_EventObservers.begin(); it !=
		m_EventObservers.end(); ++it )
	{
		if ( (*it) == pEventObserver )
		{
			return;
		}
	}

	m_EventObservers.push_back( pEventObserver );
}

void Entity::Draw( CDC* pDC )
{
	pDC->Rectangle( 
		m_Pos.x * Tank2017::gGridUnitSize,
		m_Pos.y * Tank2017::gGridUnitSize,
		(m_Pos.x + m_nWidth) * Tank2017::gGridUnitSize,
		(m_Pos.y + m_nHeight) * Tank2017::gGridUnitSize );
}

void Entity::RmvFromOwnEntityList( Entity* pEntity )
{
	
	if ( pEntity == nullptr )
	{
		//移除所有
		for( auto it = m_OwnEntityList.begin(); it !=
			m_OwnEntityList.end(); ++it )
		{
			Entity* pTemp = *it;
			ASSERT( pTemp != nullptr );
			if ( pTemp )
			{
				pTemp->SetOwner( nullptr );
			}
		}
		m_OwnEntityList.clear();
	}
	else
	{
		//移除单个
		for ( auto it = m_OwnEntityList.begin(); 
			it != m_OwnEntityList.end(); ++it )
		{
			if ( (*it) == pEntity )
			{
				pEntity->SetOwner( nullptr );
				m_OwnEntityList.erase( it );
				return;
			}
		}

		ASSERT( FALSE );
	}

	
}

void Entity::AddToOwnEntityList( Entity* pEntity )
{
	ASSERT( pEntity != nullptr );
	if ( !pEntity )
	{
		return;
	}

	for ( auto it = m_OwnEntityList.begin(); 
		it != m_OwnEntityList.end(); ++it )
	{
		if ( (*it) == pEntity )
		{
			ASSERT( FALSE );
			return;
		}
	}

	m_OwnEntityList.push_back( pEntity );
	pEntity->SetOwner( this );
}


void Entity::OnBeenKilled( Entity* pEntity )
{
	// 通知监听者死亡事件
	for( auto it = m_EventObservers.begin(); it !=
		m_EventObservers.end(); ++it )
	{
		if ( (*it) )
		{
			(*it)->OnEventBeenKilled();
		}
	}

}

void Entity::OnKillTarget( Entity* pTarget )
{
	ASSERT( pTarget != nullptr );
	if ( !pTarget )
	{
		return;
	}

	// 通知监听者杀死目标事件
	for( auto it = m_EventObservers.begin(); it !=
		m_EventObservers.end(); ++it )
	{
		if ( (*it) )
		{
			(*it)->OnEventKillTarget( pTarget );
		}
	}
}