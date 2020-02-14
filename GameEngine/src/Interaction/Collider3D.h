#ifndef GAME_ENGINE_COLLIDER_H
#define GAME_ENGINE_COLLIDER_H


namespace GameEngine {

	class BoxCollider3D;
	class MeshCollider;
	class SphereCollider;

	//! The base Collider class. Stores shared functions and variables for all Collider's
	class Collider3D : public Component {

		friend class CollisionControl3D;

	protected:

		//!The axis-aligned bounding box for the Mesh attached to the same object as this Collider
		BoundBox3D bounds;
		std::vector<std::string> tags;
		//!Generates a new BoundBox based on the Mesh currently attached to the same object as this collider
		virtual void UpdateBounds();

		//!Checks collision between this Collider and another.
		/*!
		  This is called from CollisionControl and is used to find the type of collider this is.
		  For example, if this is a BoxCollider, it will call TestBoxCollider on _col. This allows the program
		  to store just the base class Collider, trusting it to resolve correctly when CheckCollision is run.
		\param _col The Collider to test against.
		*/
		virtual void CheckCollision(std::shared_ptr<Collider3D> _col);

		//!Adds this Collider to the global list of Collider's in CollisionControl
		void OnAwake();

	public:
		//!Returns the axis aligned BoundBox of this Collider
		BoundBox3D GetBounds() const { return bounds; }

		//!Tests collision between this Collider and a BoxCollider
		 /*!
		 \param _col The BoxCollider to test against.
		 */
		virtual void TestBoxCollider3D(std::shared_ptr<BoxCollider3D> _col);

		//!Tests collision between this Collider and a MeshCollider
		/*!
		\param _col The MeshCollider to test against.
		*/
		virtual void TestMeshCollider(std::shared_ptr<MeshCollider> _col);

		//!Tests collision between this Collider and a SphereCollider
		/*!
		\param _col The SphereCollider to test against.
		*/
		virtual void TestSphereCollider(std::shared_ptr<SphereCollider> _col);

	};

}//namespace GameEngine

#endif
