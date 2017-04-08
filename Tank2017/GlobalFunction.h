#pragma once

namespace Tank2017
{
	/**
	 * @brief ��������
	 * @param pszSound ������Դ�ļ����ú�ת����Դid(MAKEINTRESOURCE)
	*/
	void PlayGameSound( LPCTSTR pszSound );

	/**
	 * @brief ��������
	 * @param bLoop �Ƿ�ѭ������
	*/
	void PlayMusic( LPCTSTR pszFileName, bool bLoop = false );

	/**
	 * @brief ֹͣ����
	*/
	void StopMusic( LPCTSTR pszFileName );
}