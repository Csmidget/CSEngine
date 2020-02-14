#include "CSEngine_Common.h"

#include "mathutil.h"

#include "Transform.h"

#include "BoundBox3D.h"
#include "Collision3D.h"
#include "Collider3D.h"
#include "BoxCollider3D.h"
#include "SphereCollider.h"
#include "MeshCollider.h"

#include "RigidBody3D.h"

#include "CollisionControl3D.h"

namespace CSEngine
{

	std::vector<std::weak_ptr<Collider3D>> CollisionControl3D::colliders;

	//==============================================================================
	void CollisionControl3D::AddCollider(std::weak_ptr<Collider3D> _col)
	{
		colliders.push_back(_col);
	}//CollisionControl3D::AddCollider
	//==============================================================================
	void CollisionControl3D::TestCollisions(std::vector<std::weak_ptr<RigidBody3D>>& _rbList )
	{
		auto activeColliders = colliders;

		for (auto rbWeak : _rbList)
		{
			if (!rbWeak.lock()->isKinematic)
				continue;

			for (int i = activeColliders.size() - 1; i >= 0; i--)
			{
				auto rbCol = rbWeak.lock()->collider.lock();
				auto targetCol = activeColliders[i].lock();

				if (!rbCol || !targetCol)
					continue;

				if (rbCol == targetCol)
				{
					activeColliders.erase(activeColliders.begin() + i);
					continue;
				}

				rbCol->CheckCollision(targetCol);
			}
		}

	}//CollisionControl3D::TestColliders
	//==============================================================================
	void CollisionControl3D::BoxBoxCollision(std::shared_ptr<BoxCollider3D> _col1, std::shared_ptr<BoxCollider3D> _col2)
	{

		BoundBox3D c1Bounds = _col1->GetBounds();
		BoundBox3D c2Bounds = _col2->GetBounds();

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
		Collision3D col;
		col.colNormal = glm::vec3();

		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * c1Extents;
		col.colColliderPos = (-col.colNormal) * c2Extents;
		col.colCollider = _col2;
		col.tags = _col2->tags;

		_col1->gameObject.lock()->OnCollision3D(col);

		col.colNormal = -col.colNormal;
		col.colPos = col.colColliderPos;
		col.colColliderPos = (-col.colNormal) * c1Extents;
		col.colCollider = _col1;
		col.tags = _col1->tags;
		_col2->gameObject.lock()->OnCollision3D(col);

	}//CollisionControl3D::BoxBoxCollision
	//==============================================================================
	void CollisionControl3D::SphereSphereCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<SphereCollider> _col2)
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

		Collision3D col;
		col.colCollider = _col2;
		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * _col1->GetRadius();
		col.colColliderPos = (-col.colNormal) * _col2->GetRadius();
		_col1->gameObject.lock()->OnCollision3D(col);
		col.tags = _col2->tags;

		col.colNormal = -col.colNormal;
		col.colCollider = _col1;
		col.colPos = col.colNormal * _col2->GetRadius();
		col.colColliderPos = (-col.colNormal) * _col1->GetRadius();
		_col2->gameObject.lock()->OnCollision3D(col);
		col.tags = _col1->tags;

	}//CollisionControl3D::SphereSphereCollision
	//==============================================================================
	void CollisionControl3D::SphereBoxCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<BoxCollider3D> _col2)
	{

		BoundBox3D c2Bounds = _col2->GetBounds();

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

		Collision3D col;
		col.colCollider = _col2;
		col.colNormal = glm::normalize((c1Pos + _col1->bounds.GetCentre()) - (c2Pos + _col2->bounds.GetCentre()));
		col.colPos = col.colNormal * _col1->GetRadius();
		col.colColliderPos = (-col.colNormal) * c2Extents;
		_col1->gameObject.lock()->OnCollision3D(col);
		col.tags = _col2->tags;

		col.colNormal = -col.colNormal;
		col.colCollider = _col1;
		col.colPos = col.colColliderPos;
		col.colColliderPos = col.colNormal * _col1->GetRadius();
		_col2->gameObject.lock()->OnCollision3D(col);
		col.tags = _col1->tags;
	}//CollisionControl3D::SphereBoxCollision
	//==============================================================================
	void CollisionControl3D::MeshMeshCollision(std::shared_ptr<MeshCollider> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox3D c1Bounds = _col1->GetBounds();
		BoundBox3D c2Bounds = _col2->GetBounds();

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


	}//CollisionControl3D::MeshMeshCollision
	//==============================================================================
	void CollisionControl3D::SphereMeshCollision(std::shared_ptr<SphereCollider> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox3D c2Bounds = _col2->GetBounds();

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


	}//CollisionControl3D::SphereMeshCollision
	//==============================================================================
	void CollisionControl3D::BoxMeshCollision(std::shared_ptr<BoxCollider3D> _col1, std::shared_ptr<MeshCollider> _col2)
	{

		BoundBox3D c1Bounds = _col1->GetBounds();
		BoundBox3D c2Bounds = _col2->GetBounds();

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

	}//CollisionControl3D::BoxMeshCollision
	 //==============================================================================
}