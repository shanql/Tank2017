#include "stdafx.h"
#include "MCIPlaySound.h"


BEGIN_MESSAGE_MAP(MCIPlaySound, CWnd)
	ON_MESSAGE(MM_MCINOTIFY, &MCIPlaySound::OnMmMcinotify)
END_MESSAGE_MAP()

MCIPlaySound::MCIPlaySound(void)
{
	m_wDeviceId = 0;
	m_bLoop = false;				
	//m_nVolume = 0;				
	Create( NULL, NULL, 0, CRect(0, 0, 100, 100 ), GetDesktopWindow(), 0 );
}


MCIPlaySound::~MCIPlaySound(void)
{
	StopGameSound();
}


bool MCIPlaySound::PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop/* = false*/ )
{
	if ( !lpszSoundFile )
	{
		ASSERT( FALSE );
		return false;
	}


	if ( m_wDeviceId > 0 )
	{
		//playTemp( true );
		sendPlay( true );
		return true;
	}

	if ( m_wDeviceId == 0 )
	{
		MCI_OPEN_PARMS mOpenParms;
		ZeroMemory( &mOpenParms, sizeof(mOpenParms) );
		mOpenParms.lpstrElementName = lpszSoundFile;

		MCIERROR nRet = ::mciSendCommand( m_wDeviceId, MCI_OPEN,
			MCI_OPEN_ELEMENT, (DWORD_PTR)&mOpenParms );
		if( nRet )
		{
			TCHAR szError[128] = {0};
			mciGetErrorString( nRet, szError, _countof(szError) );
			TRACE( _T("open device for %s failed with error: %s\n"),
				lpszSoundFile, szError );
			return false;
		}

		m_wDeviceId = mOpenParms.wDeviceID;
		m_strSoundFile = lpszSoundFile;
		m_bLoop = bLoop;
		sendPlay( false );
	}

	return true;
}


void MCIPlaySound::StopGameSound()
{
	if ( m_wDeviceId == 0 )
	{
		return;
	}

	MCI_GENERIC_PARMS mCloseParms;
	ZeroMemory( &mCloseParms, sizeof(mCloseParms) );
	MCIERROR nRet = ::mciSendCommand( m_wDeviceId, MCI_CLOSE,
		0, (DWORD_PTR)&mCloseParms );
	if ( nRet )
	{
		ASSERT( nRet == 0 );
		return;
	}

	m_wDeviceId = 0;
	m_strSoundFile = L"";

}

void MCIPlaySound::Reset()
{
	StopGameSound();
	m_wDeviceId = 0;
	m_bLoop = false;
}


LRESULT MCIPlaySound::OnMmMcinotify(WPARAM wParam, LPARAM lParam)
{
	//TRACE(_T("OnMmcinotify\n"));
	switch( wParam )
	{
	case MCI_NOTIFY_SUCCESSFUL:
		{
			if ( (MCIDEVICEID)lParam == m_wDeviceId )
			{
				//判断是否要循环播放
				if ( IsLoop() )
				{
					sendPlay( true );
				}
			}
			break;
		}
	}
	return 0;
}


void MCIPlaySound::sendPlay( bool bRePlay )
{
	ASSERT( m_wDeviceId > 0 );
	if ( m_wDeviceId <= 0 )
	{
		return;
	}

	if ( bRePlay )
	{
		MCI_SEEK_PARMS mSeekParms;
		ZeroMemory( &mSeekParms, sizeof(mSeekParms) );
		MCIERROR nRet = ::mciSendCommand( m_wDeviceId, MCI_SEEK,
			MCI_SEEK_TO_START, (DWORD_PTR)&mSeekParms );
		if ( nRet )
		{
			TCHAR szError[128] = {0};
			mciGetErrorString( nRet, szError, _countof(szError) );
			TRACE( _T("seek sound %s failed with error: %s\n"),
				m_strSoundFile, szError );
		}
	}

	MCI_PLAY_PARMS mPlayParms;
	ZeroMemory( &mPlayParms, sizeof(mPlayParms) );
	mPlayParms.dwCallback = MAKELONG( GetSafeHwnd(), 0 );
	DWORD dwFlags = MCI_NOTIFY;

	//if ( bLoop ) dwFlags |= MCI_DGV_PLAY_REPEAT;
	MCIERROR nRet = ::mciSendCommand( m_wDeviceId, MCI_PLAY,
		dwFlags, (DWORD_PTR)&mPlayParms );
	if ( nRet )
	{
		TCHAR szError[128] = {0};
		mciGetErrorString( nRet, szError, _countof(szError) );
		TRACE( _T("play sound %s failed with error: %s\n"),
			m_strSoundFile, szError );
	}
}