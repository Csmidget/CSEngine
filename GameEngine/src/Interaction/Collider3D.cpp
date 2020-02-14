#include "CSEngine_Common.h"

#include "Rendering/MeshRenderer.h"

#include "CollisionControl3D.h"
#include "BoundBox3D.h"
#include "Collider3D.h"

namespace GameEngine
{
	//==============================================================================
	void Collider3D::UpdateBounds()
	{
		bounds = BoundBox3D();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired()) return; //If no meshrenderer, just return with empty bound box

		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();

	}//Collider3D::UpdateBounds
	//====================================================W==========================
	void Collider3D::CheckCollision(std::shared_ptr<Collider3D> _col)
	{

	}//Collider3D::CheckCollision
	//==============================================================================
	void Collider3D::TestBoxCollider3D(std::shared_ptr<BoxCollider3D> _col)
	{

	}//Collider3D::TestBoxCollider3D
	//==============================================================================
	void Collider3D::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{

	}//Collider3D::TestMeshCollider
	//==============================================================================
	void Collider3D::TestSphereCollider(std::shared_ptr<SphereCollider> _col)
	{

	}//Collider3D::TestSphereCollider
	//==============================================================================
	void Collider3D::OnAwake() {
		CollisionControl3D::AddCollider(shared_from_base<Collider3D>());

		UpdateBounds();
	}//Collider3D::OnAwake
	//==============================================================================
}