#include "CollisionControl.h"

#include <iostream>

#include "util/mathutil.h"

#include "components/Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundBox.h"
#include "components/BoxCollider.h"
#include "components/SphereCollider.h"
#include "components/MeshCollider.h"
#include "Collision.h"

namespace GameEngine
{

	std::vector<std::weak_ptr<Collider>> CollisionControl::colliders;

	//==============================================================================
	void CollisionControl::AddCollider(std::weak_ptr<Collider> _col)
	{
		colliders.push_back(_col);
	}//CollisionControl::AddCollider
	//==============================================================================
	void CollisionControl::TestColliders(std::shared_ptr<Collider> _col)
	{

		for (int i = colliders.size() - 1; i >= 0; i--)
		{
			std::weak_ptr<Collider> collider = colliders.at(i);

			if (!collider.expired())
			{
				std::shared_ptr<Collider> lockedCol = collider.lock();
				if (lockedCol == _col) continue;

				_col->CheckCollision(lockedCol);

			}
			else
			{
				colliders.erase(colliders.begin() + i);
			}
		}
	}//CollisionControl::TestColliders
	//==============================================================================
	void CollisionControl::BoxBoxCollision(std::shared_ptr<BoxCollider> _col1, std::shared_ptr<BoxCollider> _col2)
	{

		BoundBox c1Bounds = _col1->GetBounds();
		BoundBox c2Bounds = _col2->GetBounds();

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition() + c1Bounds.GetCentre();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition() + c2Bounds.GetCentre();

		glm::vec3 c1Extents = c1Bounds.GetExtents() * _col1->GetTransform().lock()->GetScale();
		glm::vec3 c2Extents = c2Bounds.GetExtents() * _col2->GetTransform().lock()->GetScale();

		glm::vec3 distance = abs(c1Pos - c2Pos);

		//collision will first be found from _col1's perspective.

		if (distance.x > c1Extents.x + c2Extents.x ||
			distance.y > c1Extents.y + c2Extents.y ||
			distance.z > c1Extents.z + c2Extents.z)
		{
			return;
		}

		glm::vec3 colSize = glm::vec3(c1Bounds.GetExtents() + c2Bounds.GetExtents() - distance);
		glm::vec3 absSize = abs(colSize);
		Collision col;
		col.colNormal = glm::vec3();

		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * c1Extents;
		col.colColliderPos = (-col.colNormal) * c2Extents;
		col.colCollider = _col2;
		col.tags = _col2->tags;

		_col1->gameObject.lock()->OnCollision(col);

		col.colNormal = -col.colNormal;
		col.colPos = col.colColliderPos;
		col.colColliderPos = (-col.colNormal) * c1Extents;
		col.colCollider = _col1;
		col.tags = _col1->tags;
		_col2->gameObject.lock()->OnCollision(col);

	}//CollisionControl::BoxBoxCollision
	//==============================================================================
	void CollisionControl::SphereSphereCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<SphereCollider> _col2)
	{

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition();

		float distance = glm::length(c1Pos - c2Pos);

		float c1Radius = _col1->GetRadius();
		float c2Radius = _col2->GetRadius();

		glm::vec3 c1Scale = _col1->GetTransform().lock()->GetScale();
		glm::vec3 c2Scale = _col2->GetTransform().lock()->GetScale();

		c1Radius = (c1Radius * c1Scale.x + c1Radius * c1Scale.y + c1Radius * c1Scale.z) / 3;
		c2Radius = (c2Radius * c2Scale.x + c2Radius * c2Scale.y + c2Radius * c2Scale.z) / 3;


		if (distance > c1Radius + c2Radius) return;

		Collision col;
		col.colCollider = _col2;
		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * _col1->GetRadius();
		col.colColliderPos = (-col.colNormal) * _col2->GetRadius();
		_col1->gameObject.lock()->OnCollision(col);
		col.tags = _col2->tags;

		col.colNormal = -col.colNormal;
		col.colCollider = _col1;
		col.colPos = col.colNormal * _col2->GetRadius();
		col.colColliderPos = (-col.colNormal) * _col1->GetRadius();
		_col2->gameObject.lock()->OnCollision(col);
		col.tags = _col1->tags;

	}//CollisionControl::SphereSphereCollision
	//==============================================================================
	void CollisionControl::SphereBoxCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<BoxCollider> _col2)
	{

		BoundBox c2Bounds = _col2->GetBounds();

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition() + c2Bounds.GetCentre();

		glm::vec3 c2Extents = c2Bounds.GetExtents() * _col2->GetTransform().lock()->GetScale();

		glm::vec3 distance = abs(c1Pos - c2Pos);
		glm::vec3 normalizedDistance = glm::normalize(distance);

		glm::vec3 c1Scale = _col1->GetTransform().lock()->GetScale();
		float c1Radius = _col1->GetRadius();
		c1Radius = (c1Radius * c1Scale.x + c1Radius * c1Scale.y + c1Radius * c1Scale.z) / 3;

		if (distance.x > c1Radius * normalizedDistance.x + c2Extents.x ||
			distance.y > c1Radius * normalizedDistance.y + c2Extents.y ||
			distance.z > c1Radius * normalizedDistance.z + c2Extents.z)
		{
			return;
		}

		Collision col;
		col.colCollider = _col2;
		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * _col1->GetRadius();
		col.colColliderPos = (-col.colNormal) * c2Extents;
		_col1->gameObject.lock()->OnCollision(col);
		col.tags = _col2->tags;

		col.colNormal = -col.colNormal;
		col.colCollider = _col1;
		col.colPos = col.colColliderPos;
		col.colColliderPos = col.colNormal * _col1->GetRadius();
		_col2->gameObject.lock()->OnCollision(col);
		col.tags = _col1->tags;
	}//CollisionControl::SphereBoxCollision
	//==============================================================================
	void CollisionControl::MeshMeshCollision(std::shared_ptr<MeshCollider> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox c1Bounds = _col1->GetBounds();
		BoundBox c2Bounds = _col2->GetBounds();

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition() + c1Bounds.GetCentre();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition() + c2Bounds.GetCentre();

		glm::vec3 distance = abs(c1Pos - c2Pos);

		//collision will first be found from _col1's perspective.

		if (distance.x > c1Bounds.GetExtents().x + c2Bounds.GetExtents().x ||
			distance.y > c1Bounds.GetExtents().y + c2Bounds.GetExtents().y ||
			distance.z > c1Bounds.GetExtents().z + c2Bounds.GetExtents().z)
		{
			return;
		}

		//The bounding boxes are colliding. Now we'll do further tests:


	}//CollisionControl::MeshMeshCollision
	//==============================================================================
	void CollisionControl::SphereMeshCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox c2Bounds = _col2->GetBounds();

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition() + c2Bounds.GetCentre();

		glm::vec3 distance = abs(c1Pos - c2Pos);
		glm::vec3 normalizedDistance = glm::normalize(distance);

		float c1Radius = _col1->GetRadius();

		if (distance.x > c1Radius * normalizedDistance.x + c2Bounds.GetExtents().x ||
			distance.y > c1Radius * normalizedDistance.y + c2Bounds.GetExtents().y ||
			distance.z > c1Radius * normalizedDistance.z + c2Bounds.GetExtents().z)
		{
			return;
		}

		//The bounding box and sphere are colliding. Now we'll do further tests:


	}//CollisionControl::SphereMeshCollision
	//==============================================================================
	void CollisionControl::BoxMeshCollision(std::shared_ptr<BoxCollider> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox c1Bounds = _col1->GetBounds();
		BoundBox c2Bounds = _col2->GetBounds();

		glm::vec3 c1Pos = _col1->GetTransform().lock()->GetPosition() + c1Bounds.GetCentre();
		glm::vec3 c2Pos = _col2->GetTransform().lock()->GetPosition() + c2Bounds.GetCentre();

		glm::vec3 distance = abs(c1Pos - c2Pos);

		//collision will first be found from _col1's perspective.

		if (distance.x > c1Bounds.GetExtents().x + c2Bounds.GetExtents().x ||
			distance.y > c1Bounds.GetExtents().y + c2Bounds.GetExtents().y ||
			distance.z > c1Bounds.GetExtents().z + c2Bounds.GetExtents().z)
		{
			return;
		}

		//The bounding boxes are colliding. Now we'll do further tests:

	}//CollisionControl::BoxMeshCollision
	 //==============================================================================
}