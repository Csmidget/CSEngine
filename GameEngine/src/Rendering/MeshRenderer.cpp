#include "CSEngine_Common.h" 
#include "glm\gtc\type_ptr.hpp"
#include "tinyobjloader/tiny_obj_loader.h"

#include "Application.h"
#include "Renderer.h"

#include "Transform.h"
#include "Interaction/BoundBox3D.h"
#include "MeshLoader.h"
#include "Mesh.h"
#include "MeshRenderer.h"

namespace GameEngine
{
	//==============================================================================
	void MeshRenderer::Draw()
	{
		if (mesh->posVertices.size() != 0)
		{
			glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(GetTransform().lock()->ModelMatrix()));
			glBindVertexArray(vaoId);

			if (mesh->GetMaterials().size() > 0)
			{
				GLuint tid = Mesh::GetTexture(mesh->GetMaterials().at(0).diffuse_texname);
				glBindTexture(GL_TEXTURE_2D, tid);
			}

			if (autoScale)
				glDrawArrays(GL_TRIANGLES, 0, mesh->scaledPosVertices.size());
			else
				glDrawArrays(GL_TRIANGLES, 0, mesh->posVertices.size());
		}
	}//MeshRenderer::Draw
   //==============================================================================
	void MeshRenderer::OnAwake()
	{
		autoScale = true;
		SetMesh("cube.obj");
	}//MeshRenderer::OnAwake
   //==============================================================================
	void MeshRenderer::SetMesh(std::string _meshName)
	{

		if (Mesh::loadedMeshes.count(_meshName) != 0)
		{
			if (!Mesh::loadedMeshes.at(_meshName).expired())
			{
				mesh = Mesh::loadedMeshes.at(_meshName).lock();
				CreateVao();
				return;
			}
			else
			{
				Mesh::loadedMeshes.erase(_meshName);
			}
		}

		char* meshName = new char[_meshName.length() + 1];
		strcpy_s(meshName, _meshName.length() + 1, _meshName.c_str());

		mesh = MeshLoader::LoadMesh(meshName);
		CreateVao();

	}//MeshRenderer::SetMesh
	 //==============================================================================
	void MeshRenderer::CreateVao()
	{
		if (mesh->posVertices.size() != 0)
		{

			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);

			glGenBuffers(1, &positionVboId);
			glBindBuffer(GL_ARRAY_BUFFER, positionVboId);

			if (autoScale)
				glBufferData(GL_ARRAY_BUFFER, mesh->scaledPosVertices.size() * sizeof(glm::vec4), &mesh->scaledPosVertices.at(0), GL_STATIC_DRAW);
			else
				glBufferData(GL_ARRAY_BUFFER, mesh->posVertices.size() * sizeof(glm::vec4), &mesh->posVertices.at(0), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);


			glGenBuffers(1, &normalVboId);
			glBindBuffer(GL_ARRAY_BUFFER, normalVboId);
			glBufferData(GL_ARRAY_BUFFER, mesh->normalVertices.size() * sizeof(glm::vec3), &mesh->normalVertices.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glGenBuffers(1, &textureVboId);
			glBindBuffer(GL_ARRAY_BUFFER, textureVboId);
			glBufferData(GL_ARRAY_BUFFER, mesh->texVertices.size() * sizeof(glm::vec2), &mesh->texVertices.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(2);

			modelLoc = glGetUniformLocation(Application::Renderer().lock()->GetProgramId(), "modelMat");
		}
	}//MeshRenderer::CreateVao
	 //==============================================================================
	BoundBox3D MeshRenderer::GetMeshBounds() const
	{
		if (autoScale)
			return mesh->GetScaledBounds();
		else
			return mesh->GetBounds();
	}//MeshRenderer::GetMeshBounds
	//==============================================================================
	float MeshRenderer::GetMeshRadius() const
	{
		if (autoScale)
			return mesh->GetScaledRadius();
		else
			return mesh->GetRadius();
	}//MeshRenderer::GetMeshRadius
	//==============================================================================
	void MeshRenderer::SetAutoScale(bool _autoScale)
	{
		autoScale = _autoScale;
		CreateVao();
	}//MeshRenderer::SetAutoScaleW
}