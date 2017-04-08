#pragma once
#include "aiobject.h"


class OpposingTank;
class OpposingTankAi :
	public AiObject
{
public:
	OpposingTankAi(OpposingTank* pOpposingTank );
	virtual ~OpposingTankAi(void);

	/**
	 * @brief ����ai�ٶ�,Ĭ��Ϊ80
	*/
	void SetAiSpeed( int nSpeed ) { m_nSpeed = nSpeed; }

	virtual void Run() override;

private:
	OpposingTank* m_pOpposingTank;
	DWORD m_dwLastTick;
	DWORD m_dwFireLastTick;
	int m_nSpeed;			///< ai�ٶ�
	int m_nFireSpeed;		///< �����ٶ�
};

