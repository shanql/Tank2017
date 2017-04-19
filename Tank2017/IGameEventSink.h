#pragma once

/*!
 * \class IGameEventSink
 *
 * \brief ��Ϸ�¼��ӿ�
 *
 * \author shanql
 * \date 2017/04/11
 */
class IGameEventSink
{
public:
	/**
	 * @brief ��Ϸ�ѿ�ʼ�¼�
	*/
	virtual void OnEventGameStarted() = 0;

	/**
	 * @brief ��Ϸ����ͣ�¼�
	*/
	virtual void OnEventGamePaused() = 0;

	/**
	 * @brief ��Ϸ�����¼�
	*/
	virtual void OnEventGameContinue() = 0;

	/**
	 * @brief ��Ϸ�ѽ����¼�
	*/
	virtual void OnEventGameEnded() = 0;
};