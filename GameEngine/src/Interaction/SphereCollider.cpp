#include "SphereCollider.h"
#include "CollisionControl3D.h"
#include "Rendering/MeshRenderer.h"
#include "GameObject.h"

namespace GameEngine
{
	//==============================================================================
	void SphereCollider::UpdateBounds()
	{

		//Could do Collider::UpdateBounds for part of this but would have to reacquire Mesh/Renderer

		bounds = BoundBox3D();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired())
		{
			return; //If no meshrenderer, just return with empty bound box
		}

		std::weak_ptr<Rendering::Mesh> mesh = gameObject.lock()->GetComponent<MeshRenderer>().lock()->GetMesh();

		if (mesh.expired())
		{
			return;//If no mesh, just return with empty bound box
		}

		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();
		radius = mr.lock()->GetMeshRadius();//mesh.lock()->GetRadius();

	}//SphereCollider::UpdateBounds
	 //==============================================================================
	void SphereCollider::CheckCollision(std::shared_ptr<Collider3D> _col)
	{
		_col->TestSphereCollider(shared_from_base<SphereCollider>());
	}//BoxCollider::CheckCollision
	 //==============================================================================
	void SphereCollider::TestBoxCollider3D(std::shared_ptr<BoxCollider3D> _col)
	{
		CollisionControl3D::SphereBoxCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestBoxCollider
	 //==============================================================================
	void SphereCollider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl3D::SphereMeshCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestMeshCollider
	 //==============================================================================
	void SphereCollider::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl3D::SphereSphereCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestSphereCollider
}