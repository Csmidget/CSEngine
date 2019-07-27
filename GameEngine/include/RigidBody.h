#ifndef GAME_ENGINE_RIGIDBODY_H
#define GAME_ENGINE_RIGIDBODY_H

#include <Component.h>
#include <glm/glm.hpp>

namespace GameEngine {


	//!Stores physics information for a RigidBody
	struct RBState {
		glm::vec3 position = glm::vec3();
		glm::vec3 rotation = glm::vec3();
		glm::vec3 linearMomentum = glm::vec3();
		glm::vec3 angularMomentum = glm::vec3();
	};



	class Collider;

	//!Component for physics simulation. Interacts with Collider's.
	class RigidBody : public Component {

		friend class Application;

		//!List of all RigidBody's currently active in the application
		static std::vector<std::weak_ptr<RigidBody>> rbList;

	private:


		glm::mat3 invInertiaTensor;

		//!The interval in milliseconds between RigidBody updates. Default 20ms
		static int rbInterval;
		//!The mass of the object, used in physics calculations.
		float mass;
		//!Drag applied to object, lowers momentum over time. Used in physics calculations.
		float drag;
		//!Elasticity of the object. higher elasticity results in higher impulse from collisions.
		float elasticity;
		//!Pointer to collider attached to the same object. Will attempt to reacquire if collider falls out of scope.
		std::weak_ptr<Collider> collider;
		//!The current physics state of the object.
		RBState currState;
		//!The state of the physics object after the previous update.
		RBState prevState;

		//!The number of milliseconds since the last rigidbody update;
		static float rdtLastUpdate;

		//!Updates every rigidbody in the scene. Will update until rdtLastUpdate is lower than rbInterval.
		static void UpdateRigidBodies();

		float CalculateImpulse(Collision _col, std::shared_ptr<RigidBody> colRB);
		glm::mat3x3 InertiaTensor();
		void OnAwake();
		void OnUpdate();

		//!Called by UpdateRigidBodies(), updates the physics state of the RigidBody
		void RbUpdate();
		void OnCollision(Collision _col);

	public:

		//!Defines whether a rigidbody updates it's physics.
		bool isKinematic;
		bool lockRotation;

		//!Modifies the current value for velocity. 
		void AddVelocity(glm::vec3 _velocity);
		//!Apply's force to the object, changing it's linear momentum.
		void ApplyForce(glm::vec3 _force);
		//!Returns the current state of the RigidBody physics
		RBState GetCurrState() { return currState; }
		//!Returns the previous state of the RigidBody physics
		RBState GetPrevState() { return prevState; }

		glm::vec3 GetVelocity() { return currState.linearMomentum / mass; }
		glm::vec3 GetAngularVelocity() { return currState.angularMomentum / mass; }
		float GetMass() { return mass; }
		void SetMass(float _mass) { mass = _mass; }
		void SetDrag(float _drag) { drag = _drag; }
		void SetElasticity(float _elasticity) { elasticity = _elasticity; }
		void SetVelocity(glm::vec3 _velocity);
		void SetAngularVelocity(glm::vec3 _velocity) { currState.angularMomentum = mass * _velocity; }

		//!Set the interval between physics updates. Should only be modified during initialization.
		static void SetRbInterval(int _rbInterval) { rbInterval = +rbInterval; }

	};

}//namespace GameEngine

#endif
