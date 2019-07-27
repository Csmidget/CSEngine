#include <SphereCollider.h>
#include <CollisionControl.h>
#include <MeshRenderer.h>
#include <GameObject.h>

namespace GameEngine
{
	//==============================================================================
	void SphereCollider::UpdateBounds()
	{

		//Could do Collider::UpdateBounds for part of this but would have to reacquire Mesh/Renderer

		bounds = BoundBox();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired())
		{
			return; //If no meshrenderer, just return with empty bound box
		}

		std::weak_ptr<Mesh> mesh = gameObject.lock()->GetComponent<MeshRenderer>().lock()->GetMesh();

		if (mesh.expired())
		{
			return;//If no mesh, just return with empty bound box
		}

		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();
		radius = mr.lock()->GetMeshRadius();//mesh.lock()->GetRadius();

	}//SphereCollider::UpdateBounds
	 //==============================================================================
	void SphereCollider::CheckCollision(std::shared_ptr<Collider> _col)
	{
		_col->TestSphereCollider(shared_from_base<SphereCollider>());
	}//BoxCollider::CheckCollision
	 //==============================================================================
	void SphereCollider::TestBoxCollider(std::shared_ptr<BoxCollider> _col)
	{
		CollisionControl::SphereBoxCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestBoxCollider
	 //==============================================================================
	void SphereCollider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl::SphereMeshCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestMeshCollider
	 //==============================================================================
	void SphereCollider::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl::SphereSphereCollision(shared_from_base<SphereCollider>(), _col);
	}//BoxCollider::TestSphereCollider
}