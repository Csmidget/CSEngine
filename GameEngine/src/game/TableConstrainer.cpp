#include "CSEngine.h" 

#include "TableConstrainer.h"

using namespace GameEngine;

//==============================================================================
void TableConstrainer::OnUpdate()
{
	if (!gameObject.expired())
	{
		if (!gameObject.lock()->GetComponent<RigidBody3D>().expired())
		{
			std::shared_ptr<RigidBody3D> rb = gameObject.lock()->GetComponent<RigidBody3D>().lock();
			std::shared_ptr<Transform> trans = gameObject.lock()->GetTransform().lock();
			glm::vec3 pos = trans->GetPosition();

			glm::vec3 vel = rb->GetVelocity();

			//!Constrain within table boundaries. If outside, flip velocity and pull back in.
			if (pos.x > 11.8f)
			{
				vel.x = -vel.x;
				pos.x = 11.79f;
			}
			else if (pos.x < -11.8f)
			{
				vel.x = -vel.x;
				pos.x = -11.79f;
			}

			if (pos.y > 7.5f)
			{
				vel.y = -vel.y;
				pos.y = 7.49f;
			}
			else if (pos.y < -7.5f)
			{
				vel.y = -vel.y;
				pos.y = -7.49f;
			}

			if (pos.z < -19.6f)
			{
				vel.z = -vel.z;
				pos.z = -19.59f;
			}

			rb->SetVelocity(vel);
			trans->SetPosition(pos);
		}
	}
}//TableConstrainer::OnUpdate()
