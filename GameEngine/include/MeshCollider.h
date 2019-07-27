#ifndef GAME_ENGINE_MESHCOLLIDER_H
#define GAME_ENGINE_MESHCOLLIDER_H

#include <Collider.h>


namespace GameEngine {

	class Mesh;
	//!UNFINISHED A Collider that uses the mesh for collision detection
	class MeshCollider : public Collider {

	private:
		std::weak_ptr<Mesh> mesh;
		void UpdateBounds();

	public:

		void CheckCollision(std::shared_ptr<Collider> _col);
		void TestBoxCollider(std::shared_ptr<BoxCollider> _col);
		void TestMeshCollider(std::shared_ptr<MeshCollider> _col);
		void TestSphereCollider(std::shared_ptr<SphereCollider> _col);

	};

}//namespace GameEngine

#endif
