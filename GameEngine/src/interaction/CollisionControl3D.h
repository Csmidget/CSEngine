#ifndef GAME_ENGINE_COLLISIONCONTROL_H
#define GAME_ENGINE_COLLISIONCONTROL_H

#include <vector>
#include <memory>

namespace GameEngine {

	class Collider3D;
	class BoxCollider3D;
	class SphereCollider;
	class MeshCollider;
	class RigidBody3D;

	//! Class in control of collision related functions. Also stores a list of all active Collider's in the application.
	class CollisionControl3D {

		friend class Application;
		friend class RigidBody3D;

	private:
		//!Stores every active Collider in the scene. Used for RigidBody3D collision tests
		static std::vector<std::weak_ptr<Collider3D>> colliders;

		//!Takes a list of rigidbodies and tests them against all colliders in the scene.
		static void TestCollisions(std::vector<std::weak_ptr<RigidBody3D>>& _rbList);

	public:
		//!Adds a Collider to the Collider list
		static void AddCollider(std::weak_ptr<Collider3D> _col);

		//!Tests for collision between two BoxCollider's. Calls the OnCollision function for both GameObject's if Collision found.
		static void BoxBoxCollision(std::shared_ptr<BoxCollider3D> _col1, std::shared_ptr<BoxCollider3D> _col2);
		//!Tests for collision between two SphereCollider's. Calls the OnCollision function for both GameObject's if Collision found.
		static void SphereSphereCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<SphereCollider> _col2);

		//! #!UNFINISHED!# Tests for collision between two MeshCollider's. Calls the OnCollision function for both GameObject's if Collision found. Not currently implemented.
		static void MeshMeshCollision(std::shared_ptr<MeshCollider> _col1, std::shared_ptr<MeshCollider> _col2);

		//!Tests for collision between a SphereCollider and BoxCollider. Calls the OnCollision function for both GameObject's if Collision found. 
		static void SphereBoxCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<BoxCollider3D> _col2);

		//!#!UNFINSHED!# Tests for collision between a SphereCollider and MeshCollider. Calls the OnCollision function for both GameObject's if Collision found. Not currently implemented.
		static void SphereMeshCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<MeshCollider> _col2);

		//!#!UNFINISHED!# Tests for collision between a BoxCollider and MeshCollider. Calls the OnCollision function for both GameObject's if Collision found. Not currently implemented.
		static void BoxMeshCollision(std::shared_ptr<BoxCollider3D> _col1, std::shared_ptr<MeshCollider> _col2);

	};

}//namespace GameEngine

#endif
