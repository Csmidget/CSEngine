#include "CSEngine_Common.h"

#include "CollisionControl3D.h"
#include "BoundBox3D.h"
#include "Collider3D.h"
#include "BoxCollider3D.h"

namespace GameEngine
{
	//==============================================================================
	void BoxCollider3D::CheckCollision(std::shared_ptr<Collider3D> _col)
	{
		_col->TestBoxCollider3D(shared_from_base<BoxCollider3D>());
	}//BoxCollider3D::CheckCollision
	 //==============================================================================
	void BoxCollider3D::TestBoxCollider(std::shared_ptr<BoxCollider3D> _col)
	{
		CollisionControl3D::BoxBoxCollision(shared_from_base<BoxCollider3D>(), _col);
	}//BoxCollider3D::TestBoxCollider
	 //==============================================================================
	void BoxCollider3D::TestMeshCollider(std::shared_ptr<MeshCollider> _col)
	{
		CollisionControl3D::BoxMeshCollision(shared_from_base<BoxCollider3D>(), _col);
	}//BoxCollider3D::TestMeshCollider
	//==============================================================================
	void BoxCollider3D::TestSphereCollider(std::shared_ptr<SphereCollider>_col)
	{
		CollisionControl3D::SphereBoxCollision(_col, shared_from_base<BoxCollider3D>());
	}//BoxCollider3D::TestSphereCollider


}