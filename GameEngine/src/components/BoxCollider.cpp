#include "BoxCollider.h"
#include "interaction/CollisionControl.h"

namespace GameEngine
{
	//==============================================================================
	void BoxCollider::CheckCollision(std::shared_ptr<Collider> _col)
	{
		_col->TestBoxCollider(shared_from_base<BoxCollider>());
	}//BoxCollider::CheckCollision
	 //==============================================================================
	void BoxCollider::TestBoxCollider(std::shared_ptr<BoxCollider> _col)
	{
		CollisionControl::BoxBoxCollision(shared_from_base<BoxCollider>(), _col);
	}//BoxCollider::TestBoxCollider
	 //==============================================================================
	void BoxCollider::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl::BoxMeshCollision(shared_from_base<BoxCollider>(), _col);
	}//BoxCollider::TestMeshCollider
	//==============================================================================
	void BoxCollider::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl::SphereBoxCollision(_col, shared_from_base<BoxCollider>());
	}//BoxCollider::TestSphereCollider


}