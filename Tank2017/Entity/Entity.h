#pragma once

#include <vector>
#include "GlobalDefine.h"

class Entity;
class BattleWorld;
class AiObject;

// λ�ó���
enum PosDir
{
	enDirNull,
	enDirLeft,		
	enDirRight,
	enDirUp,
	enDirDown,
};


enum EntityType
{
	enEntityNull,	///< ��Чʵ��
	enPlayerTank,	///< ̹�����
	enBullet,		///< �ӵ�
	enOpposingTank,	///< �з�̹��
	enEntityBorder,	///< �߽�
};

enum EntityEvent
{
	enEventHitTarget,	///< ����Ŀ��
	enEventHitted,		///< ������
};

// ʵ���¼�
class IEntityEvent
{
public:
	virtual void OnEventBeenKilled() = 0;
	virtual void OnEventKillTarget( Entity* pKillTarget ) = 0;
};



// ʵ�����
class Entity
{
public:
	typedef std::vector<Entity*> EntityArray;

	Entity(void);
	virtual ~Entity(void);

	/**
	 * @brief ʵ����ʼ��
	*/
	//bool Initialize( LPCTSTR lpszImageFile );
	bool Initialize( int nWidth, int nHeight );


	/**
	 * @brief ע��۲���
	*/
	void RegisterEventObserver( IEntityEvent* pEventObserver );

	/**
	 * @brief λ������
	*/
	void SetPos( const POINT& pos ){ m_Pos = pos; }

	/**
	 * @brief ��ȡλ��
	*/
	POINT GetPos() const { return m_Pos; }

	/**
	 * @brief ���ó���
	*/
	void SetDir( PosDir mDir ) { m_Dir = mDir; }

	/**
	 * @brief ��ȡ����
	*/
	PosDir GetDir( ) const { return m_Dir;}

	/**
	 * @brief ��������
	*/
	//void SetType( EntityType enType ) { m_enType = enType;}

	/**
	 * @brief ��ȡ����
	*/
	EntityType GetType() const { return m_enType; }

	/**
	 * @brief ��������
	*/
	void SetWorld( BattleWorld* pWorld ) { m_pWorld = pWorld; }

	/**
	 * @brief �������
	*/
	BattleWorld* GetWorld() { return m_pWorld; }

	/**
	 * @brief ��ȡ���
	*/
	int GetWidth() const { return m_nWidth;}

	/**
	 * @brief ��ȡ�߶�
	*/
	int GetHeight() const { return m_nHeight; }

	/**
	 * @brief �����ٶ� 
	*/
	void SetSpeed( int nSpeed ) { m_nSpeed = nSpeed; }

	/**
	 * @brief ��ȡ�ٶ�
	*/
	int GetSpeed() const { return m_nSpeed; }

	/**
	 * @brief ��ȡai
	 * @return ��ai�ķ���nullptr
	*/
	AiObject* GetAi() { return m_pAi; }

	/**
	 * @brief ���ý�������
	*/
	void SetInWorld( bool bInWorld ) { m_bInWorld = bInWorld; }

	/**
	 * @brief �Ƿ���������
	*/
	bool IsInWorld() { return m_bInWorld; }

	/**
	 * @brief ����
	*/
	virtual void Draw( CDC* pDC );

	/**
	 * @brief ����ai
	*/
	virtual void CreateAi() {}

	/**
	 * @brief ��ɱ��Ӧ
	 * @param pEntity ��Ϊnullptr,���ʾ��ɱ�����ӵ������߽磩��
	 *				  ����ָ���������һ����ʵ��
	*/
	void OnBeenKilled( Entity* pEntity );

	/**
	 * @brief ɱ��Ŀ����Ӧ
	 * @param pTarget ����ʵ�����
	*/
	void OnKillTarget( Entity* pTarget );


	/**
	 * @brief �Ƴ�ӵ�е�ʵ��(�жϹ�ϵ)
	 * @param pEntity ��pEntity==nullptrʱ����ʾ�Ƴ�����
	 * @note �Ƴ�ӵ�е�ʵ���ͬʱ��Ҳ������ӵ�е�ʵ���OwnerΪnullptr
	*/
	void RmvFromOwnEntityList( Entity* pEntity );


	/**
	 * @brief ����ӵ��ĳʵ��
	 * @note ����ӵ��ʵ���ͬʱ��Ҳ������ӵ�е�ʵ���OwnerΪthis
	*/
	void AddToOwnEntityList( Entity* pEntity );

	/**
	 * @brief ��ȡ������
	*/
	Entity* GetOwner() { return m_pOwner; }

	/**
	 * @brief ��������ֵ 
	*/
	void SetHP( int nHP ) { m_nHP = nHP; }

	/**
	 * @brief ��ȡ����ֵ 
	*/
	int GetHP() const { return m_nHP; }


	/**
	 * @brief ��ȡӵ�е�ʵ�����
	*/
	int GetOwnEntityCount() const { return m_OwnEntityList.size(); }


	/**
	 * @brief ���ù�����
	*/
	void SetOwner( Entity* pOwner ) { m_pOwner = pOwner; }


protected:
	

	POINT m_Pos;				///< λ��
	PosDir m_Dir;				///< ����
	EntityType m_enType;		///< ʵ������
	int m_nWidth;				///< ʵ���
	int m_nHeight;				///< ʵ���
	int m_nSpeed;				///< ʵ���˶��ٶ�
	int m_nHP;					///< ʵ������ֵ
	bool m_bInWorld;			///< have enter world?
	BattleWorld* m_pWorld;		///< ��������
	AiObject* m_pAi;			///< ai
	

	EntityArray m_OwnEntityList; ///< ӵ��ʵ���б�
	Entity* m_pOwner;
	std::vector<IEntityEvent*> m_EventObservers;	///< �۲���
};
