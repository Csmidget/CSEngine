#ifndef GAME_ENGINE_RigidBody3D_H
#define GAME_ENGINE_RigidBody3D_H

namespace CSEngine {


	//!Stores physics information for a RigidBody3D
	struct RBState {
		glm::vec3 position = glm::vec3();
		glm::vec3 rotation = glm::vec3();
		glm::vec3 linearMomentum = glm::vec3();
		glm::vec3 angularMomentum = glm::vec3();
	};



	class Collider3D;

	//!Component for physics simulation. Interacts with Collider's.
	class RigidBody3D : public Component {

		friend class Application;
		friend class CollisionControl3D;

		//!List of all RigidBody3D's currently active in the application
		static std::vector<std::weak_ptr<RigidBody3D>> rbList;

	private:


		glm::mat3 invInertiaTensor;

		//!The interval in milliseconds between RigidBody3D updates. Default 20ms
		static int rbInterval;
		//!The mass of the object, used in physics calculations.
		float mass;
		//!Drag applied to object, lowers momentum over time. Used in physics calculations.
		float drag;
		//!Elasticity of the object. higher elasticity results in higher impulse from collisions.
		float elasticity;
		//!Pointer to collider attached to the same object. Will attempt to reacquire if collider falls out of scope.
		std::weak_ptr<Collider3D> collider;
		//!The current physics state of the object.
		RBState currState;
		//!The state of the physics object after the previous update.
		RBState prevState;

		//!The number of milliseconds since the last RigidBody3D update;
		static float rdtLastUpdate;

		//!Updates every RigidBody3D in the scene. Will update until rdtLastUpdate is lower than rbInterval.
		static void UpdateRigidBodies();

		float CalculateImpulse(Collision3D _col, std::shared_ptr<RigidBody3D> colRB);
		glm::mat3x3 InertiaTensor() const;
		void OnAwake();
		void OnUpdate();

		//!Called by UpdateRigidBodies(), updates the physics state of the RigidBody3D
		void RbUpdate();
		void OnCollision3D(Collision3D _col);

	public:

		//!Defines whether a RigidBody3D updates it's physics.
		bool isKinematic;
		bool lockRotation;

		//!Modifies the current value for velocity. 
		void AddVelocity(glm::vec3 _velocity);
		//!Apply's force to the object, changing it's linear momentum.
		void ApplyForce(glm::vec3 _force);
		//!Returns the current state of the RigidBody3D physics
		RBState GetCurrState() const { return currState; }
		//!Returns the previous state of the RigidBody3D physics
		RBState GetPrevState() const { return prevState; }

		glm::vec3 GetVelocity() const { return currState.linearMomentum / mass; }
		glm::vec3 GetAngularVelocity() const { return currState.angularMomentum / mass; }
		float GetMass() const { return mass; }
		void SetMass(float _mass) { mass = _mass; }
		void SetDrag(float _drag) { drag = _drag; }
		void SetElasticity(float _elasticity) { elasticity = _elasticity; }
		void SetVelocity(glm::vec3 _velocity);
		void SetAngularVelocity(glm::vec3 _velocity) { currState.angularMomentum = mass * _velocity; }

		//!Set the interval between physics updates. Should only be modified during initialization.
		static void SetRbInterval(int _rbInterval) { rbInterval = +rbInterval; }

	};

}//namespace CSEngine

#endif
