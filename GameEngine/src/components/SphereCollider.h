#ifndef GAME_ENGINE_SPHERECOLLIDER_H
#define GAME_ENGINE_SPHERECOLLIDER_H

#include "components/Collider.h"


namespace GameEngine {


	//! A Collider that uses a meshes radius for collision detection
	class SphereCollider : public Collider {

	private:

		//!The radius of this collider.
		float radius;

		//!Modified Collider.UpdateBounds(), also sets radius.
		void UpdateBounds();

	public:

		//!Runs the TestSphereCollider function on collider _col, passing a pointer to this SphereCollider as a parameter.
		/*!
		\param _col The Collider to run TestSphereCollider() on.
		*/
		void CheckCollision(std::shared_ptr<Collider> _col);

		//!Tests this SphereCollider against a BoxCollider using CollisionControl::BoxBoxCollision
		/*!
		\param _col The SphereCollider to test against.
		*/
		void TestBoxCollider(std::shared_ptr<BoxCollider> _col);

		//!Tests this SphereCollider against a MeshCollider using CollisionControl::BoxMeshCollision
		/*!
		\param _col The MeshCollider to test against.
		*/
		void TestMeshCollider(std::shared_ptr<MeshCollider> _col);

		//!Tests this SphereCollider against another SphereCollider using CollisionControl::BoxSphereCollision
		/*!
		\param _col TheSphereCollider to test against.
		*/
		void TestSphereCollider(std::shared_ptr<SphereCollider> _col);

		float GetRadius() const { return radius; }
		void SetRadius(float _radius) { radius = _radius; }
	};

}//namespace GameEngine

#endif
