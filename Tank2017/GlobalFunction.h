#pragma once

namespace Tank2017
{
	/**
	 * @brief 播放声音
	 * @param pszSound 声音资源文件，用宏转换资源id(MAKEINTRESOURCE)
	*/
	void PlayGameSound( LPCTSTR pszSound );

	/**
	 * @brief 播放音乐
	 * @param bLoop 是否循环播放
	*/
	void PlayMusic( LPCTSTR pszFileName, bool bLoop = false );

	/**
	 * @brief 停止音乐
	*/
	void StopMusic( LPCTSTR pszFileName );
}