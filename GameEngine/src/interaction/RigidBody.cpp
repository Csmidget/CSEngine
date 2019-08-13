#include "Application.h"
#include "RigidBody.h"
#include "CollisionControl.h"
#include "GameObject.h"
#include "Transform.h"
#include "components/Collider.h"
#include "components/BoxCollider.h"
#include "components/SphereCollider.h"
#include "Collision.h"

#include <glm/gtx/transform.hpp>

namespace GameEngine
{

	float RigidBody::rdtLastUpdate;
	int RigidBody::rbInterval;
	std::vector<std::weak_ptr<RigidBody>> RigidBody::rbList;

	//==============================================================================
	void RigidBody::OnAwake()
	{
		collider = gameObject.lock()->GetComponent<Collider>();

		rbList.push_back(shared_from_base<RigidBody>());
		mass = 10;
		drag = 10;
		elasticity = 0.2;

		isKinematic = true;
		lockRotation = false;

		std::weak_ptr<BoxCollider> bCol = gameObject.lock()->GetComponent<BoxCollider>();

		if (!bCol.expired())
		{
			glm::mat3 inertiaTensor = glm::mat3(0.0f);
			glm::vec3 bSize = bCol.lock()->GetBounds().GetSize();

			float i = 0.0833333333 * mass * (pow(bSize.y, 2) + pow(bSize.z, 2));
			float j = 0.0833333333 * mass * (pow(bSize.x, 2) + pow(bSize.z, 2));
			float k = 0.0833333333 * mass * (pow(bSize.x, 2) + pow(bSize.y, 2));
			inertiaTensor[0].x = i;
			inertiaTensor[1].y = j;
			inertiaTensor[2].z = k;
			invInertiaTensor = glm::inverse(inertiaTensor);
			return;
		}

		std::weak_ptr<SphereCollider> sCol = gameObject.lock()->GetComponent<SphereCollider>();

		if (!sCol.expired())
		{
			glm::mat3 inertiaTensor = glm::mat3(0.0f);
			float i = 0.4 * mass * pow(sCol.lock()->GetRadius(), 2);
			inertiaTensor[0].x = i;
			inertiaTensor[1].y = i;
			inertiaTensor[2].z = i;
			invInertiaTensor = glm::inverse(inertiaTensor);
			return;
		}

		invInertiaTensor = glm::mat3x3(1.0f);



	}// RigidBody::OnAwake
	//==============================================================================
	void RigidBody::OnUpdate() {

	}//RigidBody::OnUpdate
	//==============================================================================
	void RigidBody::OnCollision(Collision _col)
	{
		std::weak_ptr<RigidBody> colliderRB = _col.colCollider->GetGameObject().lock()->GetComponent<RigidBody>();
		float angularModifier = 200000000.0f; //Brings the angular momentum up to a usable figure. 
		//If the thing being collided with is a rigidbody and this is kinematic.
		if (!colliderRB.expired() && isKinematic)
		{
			float colMass = colliderRB.lock()->mass;
			glm::vec3 colMomentum = colliderRB.lock()->GetPrevState().linearMomentum;

			float impulse = CalculateImpulse(_col, colliderRB.lock());//linearImpulse + angularImpulse;

			currState.linearMomentum += (impulse * _col.colNormal);

			currState.angularMomentum += ((glm::cross(_col.colPos, _col.colNormal * impulse) * InertiaTensor()) *angularModifier);

			std::shared_ptr<Transform> t = GetTransform().lock();
			t->Translate((_col.colNormal * t->GetScale() * glm::length(prevState.linearMomentum)) * ((float)rbInterval / 1000.0f) / mass);
		}
	}//RigidyBody::OnCollision
	//==============================================================================
	float RigidBody::CalculateImpulse(Collision _col, std::shared_ptr<RigidBody> colRB)
	{
		glm::vec3 relativeVelocity = GetVelocity() - colRB->GetVelocity();

		float linearImpulse = -(1 + elasticity)* glm::dot(relativeVelocity, _col.colNormal) / ((1 / mass) + (1 / colRB->GetMass()));

		float angular1 = glm::dot(_col.colNormal, glm::cross(glm::cross(_col.colPos, _col.colNormal) * InertiaTensor(), _col.colPos));
		float angular2 = glm::dot(_col.colNormal, glm::cross(glm::cross(_col.colColliderPos, _col.colNormal) * colRB->InertiaTensor(), _col.colColliderPos));

		float angularImpulse = -(1 + elasticity) * glm::dot(relativeVelocity, _col.colNormal) * (angular1 + angular2);

		return linearImpulse + angularImpulse;
	}//RigidBody::CalculateImpulse
	//==============================================================================
	glm::mat3x3 RigidBody::InertiaTensor() const
	{
		glm::mat3x3 rotMat = GetTransform().lock()->RotationMatrix();
		glm::mat3x3 transposeRot = glm::transpose(rotMat);

		glm::mat3 m = rotMat * invInertiaTensor * transposeRot;
		return rotMat * invInertiaTensor * transposeRot;
	}//RigidBody::IntertiaTensor
	//==============================================================================
	void RigidBody::RbUpdate()
	{
		float rdts = rbInterval / 1000.0f;

		std::shared_ptr<GameObject> go = gameObject.lock();
		std::shared_ptr<Transform> trans = go->GetTransform().lock();
		currState.position = trans->GetPosition();
		currState.rotation = trans->GetLocalRotation();

		if (!gameObject.lock()->GetTransform().lock()->GetParent().expired())
		{
			currState.position = trans->GetPosition();
		}

		if (isKinematic)
		{
			currState.position += currState.linearMomentum / mass * rdts;
			currState.rotation += currState.angularMomentum / mass * rdts;

			if (drag != 0)
			{
				currState.linearMomentum -= ((currState.linearMomentum) * (sqrt(drag / 100)  * rdts));
				currState.angularMomentum -= ((currState.angularMomentum) * (sqrt(drag / 100)  * rdts));
			}
			if (collider.expired())
			{
				collider = gameObject.lock()->GetComponent<Collider>();
			}

			if (prevState.position != currState.position)
			{
				//if (!collider.expired()) CollisionControl::TestColliders(collider.lock());
			
				trans->SetPosition(currState.position);
				if (!lockRotation)
				{
					trans->SetLocalRotation(currState.rotation);
				}
			}
		}
		prevState = currState;

	}//RigidBody::RbUpdate
	//==============================================================================
	void RigidBody::SetVelocity(glm::vec3 _velocity)
	{
		currState.linearMomentum = _velocity * mass;
	}//RigidBody::SetVelocity
	//==============================================================================
	void RigidBody::AddVelocity(glm::vec3 _velocity)
	{
		glm::vec3 velocity = (currState.linearMomentum / mass) + velocity;
		currState.linearMomentum = velocity * mass;
	}//RigidBody::SetVelocity
	//==============================================================================
	void RigidBody::ApplyForce(glm::vec3 _force)
	{
		currState.linearMomentum += _force * (Application::Rdts());
	}//RigidBody::SetVelocity
	//==============================================================================
	void RigidBody::UpdateRigidBodies()
	{
		rdtLastUpdate += Application::Rdt();

		//Interval for updating 
		for (rdtLastUpdate; rdtLastUpdate >= rbInterval; rdtLastUpdate -= rbInterval)
		{
			for (int i = rbList.size() - 1; i >= 0; i--)
			{
				std::weak_ptr<RigidBody> rb = rbList.at(i);

				if (!rb.expired())
				{
					rb.lock()->RbUpdate();
				}
				else
				{
					rbList.erase(rbList.begin() + i);
				}
			}

			CollisionControl::TestCollisions(rbList);

		}
	}//RigidBody::UpdateRigidBodies
	//==============================================================================
}