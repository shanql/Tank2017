#pragma once

#include <list>
#include <map>
#include <string>


class MCIPlaySound;

/*!
 * \class MCIPlaySndManager
 *
 * \brief 
 *
 * \author shanql
 * \date 2017/04/02
 */
class MCIPlaySndManager
{
private:
	MCIPlaySndManager(void);

public:
	static MCIPlaySndManager& GetInstance();
	virtual ~MCIPlaySndManager(void);

	/**
	 * @brief 播放声音
	 * @param lpszSoundFile 声音文件
	*/
	void PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop = false );

	/**
	 * @brief 停止声音
	 * @param lpszSoundFile 声音文件
	*/
	void StopGameSound( LPCTSTR lpszSoundFile );

private:
	/**
	 * @brief 激活一个播放对象
	*/
	MCIPlaySound* activePlayObject();

	/**
	 * @brief 释放一个播放对象
	*/
	void freePlayObject( MCIPlaySound* pPlayObject );

private:
	typedef std::list<MCIPlaySound*> MCIPlayObjArray;
	typedef std::map<std::string,MCIPlaySound*> MCPPlayObjMap;

	MCIPlayObjArray m_PlayObjArrayActive;		///< 活动的播放对象
	MCIPlayObjArray m_PlayObjArrayFree;			///< 空闲的播放对象
};

