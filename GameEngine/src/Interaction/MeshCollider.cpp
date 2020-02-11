#include "MeshCollider.h"

#include "CollisionControl3D.h"
#include "Rendering/MeshRenderer.h"
#include "GameObject.h"

namespace GameEngine
{
	//==============================================================================
	void MeshCollider::UpdateBounds()
	{
		bounds = BoundBox3D();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired())
		{
			return; //If no meshrenderer, just return with empty bound box
		}

		std::weak_ptr<Rendering::Mesh> rmesh = gameObject.lock()->GetComponent<MeshRenderer>().lock()->GetMesh();

		if (rmesh.expired())
		{
			return;//If no mesh, just return with empty bound box
		}
		mesh = rmesh;
		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();

	}//MeshCollider::UpdateBounds
	//==============================================================================
	void MeshCollider::CheckCollision(std::shared_ptr<Collider3D> _col)
	{
		_col->TestMeshCollider(shared_from_base<MeshCollider>());
	}//BoxCollider::CheckCollision
	//==============================================================================
	void MeshCollider::TestBoxCollider(std::shared_ptr<BoxCollider3D> _col)
	{
		CollisionControl3D::BoxMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestBoxCollider
	//==============================================================================
	void MeshCollider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl3D::MeshMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestMeshCollider
	//==============================================================================
	void MeshCollider::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl3D::SphereMeshCollision(_col, shared_from_base<MeshCollider>());
	}//BoxCollider::TestMeshCollider
	//==============================================================================
}