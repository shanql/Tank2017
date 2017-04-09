#include "stdafx.h"
#include "MCIPlaySndManager.h"
#include "MCIPlaySound.h"


MCIPlaySndManager::MCIPlaySndManager(void)
{
	
}


MCIPlaySndManager::~MCIPlaySndManager(void)
{
	for( auto it = m_PlayObjArrayActive.begin(); 
		it != m_PlayObjArrayActive.end();++it )
	{
		if ( *it )
		{
			(*it)->DestroyWindow();
			delete (*it);
		}
	}
	m_PlayObjArrayActive.clear();

	for( auto it = m_PlayObjArrayFree.begin(); 
		it != m_PlayObjArrayFree.end(); ++it )
	{
		if ( *it  )
		{
			(*it)->DestroyWindow();
			delete (*it);
		}
	}
	m_PlayObjArrayFree.clear();
}

MCIPlaySndManager& MCIPlaySndManager::GetInstance()
{
	static MCIPlaySndManager g_Inst;
	return g_Inst;
}


void MCIPlaySndManager::PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop/* = false */ )
{
	if ( !lpszSoundFile )
	{
		return;
	}
	std::wstring strSndFile = lpszSoundFile;
	for( auto it = m_PlayObjArrayActive.begin(); 
		it != m_PlayObjArrayActive.end();++it )
	{
		if ( (*it)->GetSoundFile() == strSndFile )
		{
			(*it)->PlayGameSound( lpszSoundFile, bLoop );
			return;
		}
	}

	MCIPlaySound* pPlaySndObj = activePlayObject();
	ASSERT( pPlaySndObj != nullptr );
	if ( !pPlaySndObj )
	{
		return;
	}

	//TODO: 此处播放失败，需要回收这个对象
	if ( !pPlaySndObj->PlayGameSound( lpszSoundFile, bLoop ) )
	{
		freePlayObject( pPlaySndObj );
	}
}


void MCIPlaySndManager::StopGameSound( LPCTSTR lpszSoundFile )
{
	if ( !lpszSoundFile )
	{
		return;
	}

	MCIPlaySound* pPlaySndObj = nullptr;
	
	std::wstring strSndFile = lpszSoundFile;
	for( auto it = m_PlayObjArrayActive.begin(); 
		it != m_PlayObjArrayActive.end();++it )
	{
		if ( (*it)->GetSoundFile() == strSndFile )
		{
			pPlaySndObj = (*it);
			break;
		}
	}

	if ( !pPlaySndObj )
	{
		return;
	}

	pPlaySndObj->StopGameSound();
	freePlayObject( pPlaySndObj );

}


MCIPlaySound* MCIPlaySndManager::activePlayObject()
{
	MCIPlaySound* pPlaySndObj = nullptr;
	if ( m_PlayObjArrayFree.size() > 0 )
	{
		pPlaySndObj = m_PlayObjArrayFree.back();
		m_PlayObjArrayFree.pop_back();
	}

	if ( pPlaySndObj == nullptr )
	{
		pPlaySndObj = new MCIPlaySound();
	}

	m_PlayObjArrayActive.push_back( pPlaySndObj );
	pPlaySndObj->Reset();
	return pPlaySndObj;
}


void MCIPlaySndManager::freePlayObject( MCIPlaySound* pPlayObject )
{
	bool bExistAtActive = false;
	for( auto it = m_PlayObjArrayActive.begin(); 
		it != m_PlayObjArrayActive.end();++it )
	{
		if ( *it == pPlayObject )
		{
			m_PlayObjArrayActive.erase( it );
			bExistAtActive = true;
			break;
		}
	}
	if ( !bExistAtActive )
	{
		ASSERT( FALSE );
		return;
	}

	bool bExistAtFree = false;
	for( auto it = m_PlayObjArrayFree.begin(); 
		it != m_PlayObjArrayFree.end(); ++it )
	{
		if ( *it == pPlayObject )
		{
			bExistAtFree = true;
			break;
		}
	}

	if ( bExistAtFree )
	{
		ASSERT( FALSE );
		return;
	}

	m_PlayObjArrayFree.push_back( pPlayObject );
}