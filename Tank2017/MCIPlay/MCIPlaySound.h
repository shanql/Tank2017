#pragma once

#include <mciapi.h>
#include <string>

/*!
 * \class MCIPlaySound
 *
 * \brief MCI���������ļ��򵥷�װ
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
	 * @brief ��������
	 * @param lpszSoundFile �����ļ���
	 * @return ����ʧ�ܷ���false
	*/
	bool PlayGameSound( LPCTSTR lpszSoundFile, bool bLoop  = false );

	/**
	 * @brief ֹͣ����
	*/
	void StopGameSound();

	/**
	 * @brief ��ȡ����Դ�ļ�
	*/
	std::wstring GetSoundFile() const { return m_strSoundFile; }

	/**
	 * @brief ���ö���
	*/
	void Reset();

	/**
	 * @brief �Ƿ�ѭ������
	*/
	bool IsLoop() const { return m_bLoop; }

private:
	/**
	 * @brief ���豸���Ͳ��� 
	 * @param bRePlay �Ƿ��ͷ��ʼ
	*/
	void sendPlay( bool bRePlay );

protected:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg LRESULT OnMmMcinotify(WPARAM wParam, LPARAM lParam);

private:
	MCIDEVICEID m_wDeviceId;		///< �豸ID
	std::wstring m_strSoundFile;	///< �����ļ�
	bool m_bLoop;					///< �Ƿ�ѭ������
	//int m_nVolume;					///< ����
	
};

