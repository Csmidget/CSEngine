#include "CSEngine_Common.h" 

#include "tinyobjloader/tiny_obj_loader.h"

#include "BoundBox3D.h"

#include "Mesh.h"

namespace CSEngine
{
	//==============================================================================
	Mesh::Mesh()
	{
		radius = 0;
	}//Mesh::Mesh

	 //==============================================================================
	void Mesh::RecalcBounds()
	{
		radius = 0;

		if (rawVertices.size() < 1)
		{
			bounds = BoundBox3D(glm::vec3(), glm::vec3());
		}

		glm::vec3 min;
		glm::vec3 max;

		min.x = rawVertices.at(0).x;
		max.x = rawVertices.at(0).x;

		min.y = rawVertices.at(0).y;
		max.y = rawVertices.at(0).y;

		min.z = rawVertices.at(0).z;
		max.z = rawVertices.at(0).z;

		for (size_t i = 0; i < rawVertices.size(); i++)
		{
			glm::vec3 currVertex = rawVertices.at(i);

			if (currVertex.x < min.x) min.x = currVertex.x;
			if (currVertex.x > max.x) max.x = currVertex.x;

			if (currVertex.y < min.y) min.y = currVertex.y;
			if (currVertex.y > max.y) max.y = currVertex.y;

			if (currVertex.z < min.z) min.z = currVertex.z;
			if (currVertex.z > max.z) max.z = currVertex.z;

			float vertexLength = glm::length(currVertex);

			if (vertexLength > radius) radius = vertexLength;

		}
		glm::vec3 centre = (min + max) / 2.0f;
		glm::vec3 size = (max - centre) * 2.0f;
		bounds = BoundBox3D(centre, size);


		float longestAxis = size.x;
		if (size.y > longestAxis) longestAxis = size.y;
		if (size.z > longestAxis) longestAxis = size.z;

		if (longestAxis > 1)
		{
			scaledBounds = BoundBox3D(centre, size / longestAxis);
			scaledRadius = radius / longestAxis;
		}
		else
		{
			scaledBounds = bounds;
			scaledRadius = radius;
		}
	}//Mesh::RecalcBounds
	//==============================================================================
}