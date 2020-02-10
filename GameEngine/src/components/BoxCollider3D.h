#ifndef GAME_ENGINE_BOXCOLLIDER_H
#define GAME_ENGINE_BOXCOLLIDER_H

#include "components/Collider3D.h"


namespace GameEngine {


	//! A Collider that uses an axis-aligned bounding box for collision detection
	class BoxCollider3D : public Collider3D {

	public:

		//!Runs the TestBoxCollider function on collider _col, passing a pointer to this BoxCollider as a parameter.
		/*!
		\param _col The Collider to run TestBoxCollider() on.
		*/
		void CheckCollision(std::shared_ptr<Collider3D> _col);

		//!Tests this BoxCollider against another BoxCollider using CollisionControl::SphereBoxCollision
		/*!
		\param _col The BoxCollider to test against.
		*/
		void TestBoxCollider(std::shared_ptr<BoxCollider3D> _col);

		//!Tests this BoxCollider against a MeshCollider using CollisionControl::SphereMeshCollision
		/*!
		\param _col The MeshCollider to test against.
		*/
		void TestMeshCollider(std::shared_ptr<MeshCollider> _col);

		//!Tests this BoxCollider against a SphereCollider using CollisionControl::BoxSphereCollision
		/*!
		\param _col TheMeshCollider to test against.
		*/
		void TestSphereCollider(std::shared_ptr<SphereCollider> _col);

	};

}//namespace GameEngine

#endif
