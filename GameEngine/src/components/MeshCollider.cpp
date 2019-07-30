#include "MeshCollider.h"

#include "interaction/CollisionControl.h"
#include "components/MeshRenderer.h"
#include "GameObject.h"

namespace GameEngine
{
	//==============================================================================
	void MeshCollider::UpdateBounds()
	{
		bounds = BoundBox();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired())
		{
			return; //If no meshrenderer, just return with empty bound box
		}

		std::weak_ptr<Mesh> rmesh = gameObject.lock()->GetComponent<MeshRenderer>().lock()->GetMesh();

		if (rmesh.expired())
		{
			return;//If no mesh, just return with empty bound box
		}
		mesh = rmesh;
		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();

	}//MeshCollider::UpdateBounds
	//==============================================================================
	void MeshCollider::CheckCollision(std::shared_ptr<Collider> _col)
	{
		_col->TestMeshCollider(shared_from_base<MeshCollider>());
	}//BoxCollider::CheckCollision
	//==============================================================================
	void MeshCollider::TestBoxCollider(std::shared_ptr<BoxCollider> _col)
	{
		CollisionControl::BoxMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestBoxCollider
	//==============================================================================
	void MeshCollider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl::MeshMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestMeshCollider
	//==============================================================================
	void MeshCollider::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl::SphereMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestMeshCollider
	//==============================================================================
}