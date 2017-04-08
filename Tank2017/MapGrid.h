#pragma once

#include "Entity/Entity.h"
#include "IBulletHitSink.h"

// namespace tst_MapGrid {
// 	class TestMapGrid;
// }


// ����Ԫ
class GridUnit
{
public:
	/**
	 * @brief ����ʵ�壬�����б��е��򲻼���
	*/
	bool Add( Entity* pEntity )
	{
		for( auto it = m_EntityList.begin(); it != m_EntityList.end(); ++it )
		{
			if ( *it == pEntity )
			{
				return false;
			}
		}

		m_EntityList.push_back( pEntity );
		return true;
	}

	/**
	 * @brief �Ƴ�ʵ��
	*/
	bool Remove( Entity* pEntity )
	{
		for( auto it = m_EntityList.begin(); it != m_EntityList.end(); ++it )
		{
			if ( *it == pEntity )
			{
				m_EntityList.erase( it );
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief ��ȡ����
	*/
	int Count() const { return (int)(m_EntityList.size()); }

	/**
	 * @brief �����б�
	*/
	Entity* Enum( int nIndex )
	{
		if ( nIndex < 0 || nIndex >= (int)(m_EntityList.size()) )
		{
			return nullptr;
		}

		return m_EntityList.at( nIndex );
	}

private:
	std::vector<Entity*> m_EntityList;	///< ʵ���б� 
};

// ��ͼ������
class MapGrid
{
	//friend class TestMapGrid;
public:
	//static const int s_nGridUnitSize = 12;	///< ����Ԫ��С(ʵ����С��Ԫ��

	MapGrid(void);
	virtual ~MapGrid(void);

	/**
	 * @brief ���û��лص�
	*/
	void SetBulletHitSink( IBulletHitSink* pSink ) { m_pBulletHitSink = pSink; }

	/**
	 * @brief ��ͼ��ʼ��
	 * @param nWidth �����е�Ԫ����
	 * @param nHeight �����е�Ԫ����
	*/
	bool Initialize( int nWidth, int nHeight );


	/**
	 * @brief �Ƿ�����ƶ���ĳλ��
	 * @param xPos Ŀ���x����
	 * @param yPos Ŀ���y����
	*/
	bool CanMove( Entity* pEntity, int xPos, int yPos );


	/**
	 * @brief ����ԭ�����ƶ�
	 * @param nStep �ƶ��ĸ�����
	*/
	//bool ContiuneMove( Entity* pEntity, int nStep );

	/**
	 * @brief ʵ���ƶ�
	 * @param xPos Ŀ���x����
	 * @param yPos Ŀ���y����
	*/
	bool MoveEntity( Entity* pEntity, int xPos, int yPos );

	/**
	 * @brief ��ȡʵ����ĳ�����ϵ�����ʵ��
	 * @return ������ʵ�巵��nullptr,���򷵻���Ӧʵ��
	*/
	//Entity* GetAdjacentEntity( Entity* pEntity, PosDir enDir );

	/**
	 * @brief ����ӵ��Ƿ����
	*/
	void CheckBullteHit( Bullet* pBullet );

	/**
	 * @brief ʵ����ײ���
	*/
	//void CheckCollision( Entity* pEntity );

	/**
	 * @brief �Ƴ�ʵ��
	*/
	void RemoveEntity( Entity* pEntity );

	/**
	 * @brief ��ȡʵ��
	 * @param xPos ����x
	 * @param yPos ����y
	 * @return ��ʵ�巵��nullptr, ���򷵻���Ӧʵ��
	*/
	//Entity* GetEntity( int xPos, int yPos );

	/**
	 * @brief �ж�������Ƿ���Ч
	*/
// 	bool IsVaildPos( int xPos, int yPos, int nEntityWidth = 0,
// 		int nEntityHeight = 0 );
	bool IsVaildPos( int xPos, int yPos );

	/**
	 * @brief �ж�������Ƿ������ʵ��
	*/
	bool CanRespawn( int xPos, int yPos, 
		int nEntityWidth, int nEntityHeight );

	/**
	 * @brief ��ͼ��
	*/
	int GetWidth() const { return m_nWidth;}

	/**
	 * @brief ��ͼ��
	*/
	int GetHeight() const { return m_nHeight; }

	/**
	 * @brief �Ƿ�ɴ�͸
	*/
	//bool CanCross()

private:
	/**
	 * @brief ����ʵ��
	 * @param xPos ����x
	 * @param yPos ����y
	*/
	void addEntity( Entity* pEntity, int xPos, int yPos );

	/**
	 * @brief ��ȡ��ͼʵ���б�����
	*/
	int getMapIndex( int xPos, int yPos );

	/**
	 * @brief �ӵ��Ƿ����
	*/
	//bool isBulletHit( Bullet* pBullet, Entity* pEntity );

	/**
	 * @brief ��ָ��λ�ã�ָ�������Ͻ����ӵ����м��
	 * @param pSrcEntity �������ʵ��
	 * @param mCheckPos ����λ�õ�
	 * @param enCheckDir ���ķ��� 
	*/
	//void checkBulletHitByPos( Entity* pSrcEntity, POINT mCheckPos, PosDir enCheckDir );


private:
	int m_nWidth;		///< ��ͼ��
	int m_nHeight;		///< ��ͼ��
	//Entity** m_pMap;		///< ��ͼ����ά��ͼ��
	GridUnit* m_pMap;	///< ��ͼ����ά��ͼ��
	IBulletHitSink* m_pBulletHitSink;	///< �ӵ����лص�
};

