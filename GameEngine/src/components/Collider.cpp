#include "Collider.h"

#include "interaction/CollisionControl.h"
#include "MeshRenderer.h"
#include "GameObject.h"

namespace GameEngine
{
	//==============================================================================
	void Collider::UpdateBounds()
	{
		bounds = BoundBox();

		std::weak_ptr<MeshRenderer> mr = gameObject.lock()->GetComponent<MeshRenderer>();

		if (mr.expired()) return; //If no meshrenderer, just return with empty bound box

		bounds = mr.lock()->GetMeshBounds();//mesh.lock()->GetBounds();

	}//Collider::UpdateBounds
	//====================================================W==========================
	void Collider::CheckCollision(std::shared_ptr<Collider> _col)
	{

	}//Collider::CheckCollision
	//==============================================================================
	void Collider::TestBoxCollider(std::shared_ptr<BoxCollider> _col)
	{

	}//Collider::TestBoxCollider
	//==============================================================================
	void Collider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{

	}//Collider::TestMeshCollider
	//==============================================================================
	void Collider::TestSphereCollider(std::shared_ptr<SphereCollider> _col)
	{

	}//Collider::TestSphereCollider
	//==============================================================================
	void Collider::OnAwake() {
		CollisionControl::AddCollider(shared_from_base<Collider>());
		UpdateBounds();
	}//Collider::OnAwake
	//==============================================================================
}