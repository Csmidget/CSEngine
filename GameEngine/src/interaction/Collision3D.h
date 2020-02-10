#ifndef GAME_ENGINE_COLLISION_H
#define GAME_ENGINE_COLLISION_H

#include <glm/glm.hpp>
#include <string>

namespace GameEngine {

	class Collider3D;

	//!Stores information on a collision. Passed into Component OnCollision() functions.
	struct Collision3D {
	public:
		glm::vec3 colPos; /*!<The position of the collision relative to the position of the object*/
		glm::vec3 colNormal; /*!<The normal vector of the collision*/
		std::shared_ptr<Collider3D> colCollider; /*!<The Collider that has been hit*/
		glm::vec3 colColliderPos;/*!<The position of the collision relative to the position of the collider that has been hit*/
		std::vector<std::string> tags;
	};

}//namespace GameEngine
#endif
