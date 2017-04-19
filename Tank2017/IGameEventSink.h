#pragma once

/*!
 * \class IGameEventSink
 *
 * \brief 游戏事件接口
 *
 * \author shanql
 * \date 2017/04/11
 */
class IGameEventSink
{
public:
	/**
	 * @brief 游戏已开始事件
	*/
	virtual void OnEventGameStarted() = 0;

	/**
	 * @brief 游戏已暂停事件
	*/
	virtual void OnEventGamePaused() = 0;

	/**
	 * @brief 游戏继续事件
	*/
	virtual void OnEventGameContinue() = 0;

	/**
	 * @brief 游戏已结束事件
	*/
	virtual void OnEventGameEnded() = 0;
};