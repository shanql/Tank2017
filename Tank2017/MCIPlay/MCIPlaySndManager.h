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
	 * @brief ��������
	 * @param lpszSoundFile �����ļ�
	*/
	void PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop = false );

	/**
	 * @brief ֹͣ����
	 * @param lpszSoundFile �����ļ�
	*/
	void StopGameSound( LPCTSTR lpszSoundFile );

private:
	/**
	 * @brief ����һ�����Ŷ���
	*/
	MCIPlaySound* activePlayObject();

	/**
	 * @brief �ͷ�һ�����Ŷ���
	*/
	void freePlayObject( MCIPlaySound* pPlayObject );

private:
	typedef std::list<MCIPlaySound*> MCIPlayObjArray;
	typedef std::map<std::string,MCIPlaySound*> MCPPlayObjMap;

	MCIPlayObjArray m_PlayObjArrayActive;		///< ��Ĳ��Ŷ���
	MCIPlayObjArray m_PlayObjArrayFree;			///< ���еĲ��Ŷ���
};

