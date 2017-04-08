#pragma once

#include <mciapi.h>
#include <string>

/*!
 * \class MCIPlaySound
 *
 * \brief MCI播放声音文件简单封装
 *
 * \author shanql
 * \date 2017/04/02
 */
class MCIPlaySound: public CWnd
{
	
public:
	MCIPlaySound(void);
	virtual ~MCIPlaySound(void);

	/**
	 * @brief 播放声音
	 * @param lpszSoundFile 声音文件名
	 * @return 播放失败返回false
	*/
	bool PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop  = false );

	/**
	 * @brief 停止声音
	*/
	void StopGameSound();

	/**
	 * @brief 获取播放源文件
	*/
	std::wstring GetSoundFile() const { return m_strSoundFile; }

	/**
	 * @brief 重置对象
	*/
	void Reset();

	/**
	 * @brief 是否循环播放
	*/
	bool IsLoop() const { return m_bLoop; }

private:
	/**
	 * @brief 向设备发送播放 
	 * @param bRePlay 是否从头开始
	*/
	void sendPlay( bool bRePlay );

protected:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg LRESULT OnMmMcinotify(WPARAM wParam, LPARAM lParam);

private:
	MCIDEVICEID m_wDeviceId;		///< 设备ID
	std::wstring m_strSoundFile;	///< 声音文件
	bool m_bLoop;					///< 是否循环播放
	//int m_nVolume;					///< 音量
	
};

