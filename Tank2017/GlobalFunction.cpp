#include "stdafx.h"

#include <playsoundapi.h>
#include <mciapi.h>

#include "GlobalFunction.h"
#include "MCIPlay/MCIPlaySndManager.h"
#include "GlobalDefine.h"


namespace Tank2017
{
	void PlayGameSound( LPCTSTR pszSound )
	{
		if( !pszSound )
		{
			ASSERT( FALSE );
			return;
		}
		::PlaySound( pszSound, AfxGetInstanceHandle(),
			SND_RESOURCE | SND_NODEFAULT | SND_ASYNC );
	}

	void PlayMusic( LPCTSTR pszFileName, bool bLoop /*= false*/ )
	{
		if ( !pszFileName )
		{
			ASSERT( FALSE );
			return;
		}

		MCIPlaySndManager::GetInstance().PlayGameSound( pszFileName, bLoop );
	}

	void StopMusic( LPCTSTR pszFileName )
	{
		if ( !pszFileName )
		{
			ASSERT( FALSE );
			return;
		}

		MCIPlaySndManager::GetInstance().StopGameSound( pszFileName );
	}

	int ToMapSize( int nScreenSize )
	{
		return (nScreenSize+Tank2017::gGridUnitSize-1) / Tank2017::gGridUnitSize;
	}

	int ToScreenSize( int nMapSize )
	{
		return nMapSize * Tank2017::gGridUnitSize;
	}
}