#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\..\Tank2017\MapGrid.h"
#include "Entity\OpposingTank.h"
#include "Entity\Bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tst_MapGrid
{		
	TEST_CLASS(TestMapGrid)
	{
	public:
		
		TEST_METHOD(TestIsVaildPos)
		{
			// TODO: 在此输入测试代码
			MapGrid mMapGrid;
			Assert::IsFalse( mMapGrid.IsVaildPos( 0, 0 ) );

			Assert::IsTrue( mMapGrid.Initialize( 2, 2 ));
			Assert::IsTrue( mMapGrid.IsVaildPos( 0, 0 ) );
			Assert::IsTrue( mMapGrid.IsVaildPos( 1, 1 ) );
			Assert::IsFalse( mMapGrid.IsVaildPos( 2, 2 ) );
			Assert::IsFalse( mMapGrid.IsVaildPos( 0, 2 ) );
			
		}

		TEST_METHOD(TestGetEntity)
		{
			MapGrid mMapGrid;
			mMapGrid.Initialize( 8, 8 );
			
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 1, 1 ) );
// 
// 			Entity mEntity;
// 			mEntity.Initialize( 2, 2 );
// 			Assert::IsTrue( mMapGrid.MoveEntity( &mEntity, 2, 1 ) );

// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 2, 1 ) );
// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 2, 2 ) );
// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 3, 1 ) );
// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 3, 2 ) );
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 3, 3 ) );
// 
// 
// 			Assert::IsTrue( mMapGrid.MoveEntity( &mEntity, 3, 1 ) );
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 2, 1 ) );
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 2, 2 ) );
// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 4, 1 ) );
// 			Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 4, 2 ) );



		}

		TEST_METHOD(TestCanMove)
		{
			MapGrid mMapGrid;
			mMapGrid.Initialize( 4, 4 );

			Entity mEntity;
			mEntity.Initialize( 2, 2 );

			Assert::IsTrue( mMapGrid.CanMove( &mEntity, 0, 0 ) );
			Assert::IsTrue( mMapGrid.CanMove( &mEntity, 2, 0 ) );
			Assert::IsFalse( mMapGrid.CanMove( &mEntity, 3, 0 ) );
		}

		TEST_METHOD(TestMoveEntity)
		{
			{
				MapGrid mMapGrid;
				Assert::IsTrue( mMapGrid.Initialize( 4, 4 ) );

				Entity mEntity;
				Assert::IsTrue(  mEntity.Initialize( 2, 2 ) );

				Assert::IsTrue( mMapGrid.MoveEntity( &mEntity, 1, 1 ) );
				Assert::IsTrue( mMapGrid.MoveEntity( &mEntity, 2, 1 ) );

				Entity mEntity2;
				mEntity2.Initialize( 1, 1 );
				Assert::IsFalse( mMapGrid.MoveEntity( &mEntity2, 2, 1 ) );
				Assert::IsTrue( mMapGrid.MoveEntity( &mEntity2, 0, 1 ) );
			}

			{
				MapGrid mMapGrid;
				mMapGrid.Initialize( 4, 4 );

				Entity mEntity;
				mEntity.Initialize( 2, 2 );
				mMapGrid.MoveEntity( &mEntity, 0, 0 );

				Entity mEntity2;
				mEntity2.Initialize( 1, 1 );
				mMapGrid.MoveEntity( &mEntity2, 3, 3 );

				//Assert::IsTrue( &mEntity == mMapGrid.GetEntity( 0, 0 ) );
			}
			
		}

		TEST_METHOD(TestRemoveEntity)
		{
			MapGrid mMapGrid;
			Assert::IsTrue( mMapGrid.Initialize( 8, 8 ) );

			Entity mEntity;
			mEntity.Initialize( 2, 3 );
			mMapGrid.MoveEntity( &mEntity, 1, 1 );

			mMapGrid.RemoveEntity( &mEntity );

// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 1, 1) );
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 2, 3 ) );
		}

// 		TEST_METHOD(TestCheckCollision)
// 		{
// 			MapGrid mMapGrid;
// 			mMapGrid.Initialize( 8, 8 );
// 
// 			OpposingTank mTank1;
// 			mTank1.Initialize( 2, 2 );
// 			mMapGrid.MoveEntity( &mTank1, 0, 0 );
// 
// 
// 			PlayerTank mPlayerTank;
// 
// 			Bullet mBullet;
// 			mBullet.Initialize( 1, 1 );
// 			mBullet.SetDir( enDirLeft );
// 			mBullet.SetOwner( &mPlayerTank );
// 			mMapGrid.MoveEntity( &mBullet, 2, 0 );
// 
// 			mMapGrid.CheckCollision( &mTank1 );
// 
// 			Assert::IsTrue( nullptr == mMapGrid.GetEntity( 1, 0 ) );
// 
// 
// 			mMapGrid.isBulletHit( nullptr, nullptr );
// 		}
	};
}