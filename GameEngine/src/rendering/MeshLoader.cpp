#include "MeshLoader.h"
#include "Mesh.h"
#include "Debug.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace GameEngine
{
	namespace Rendering
	{

		std::map<std::string, GLuint> Mesh::textures;
		std::map<std::string, std::weak_ptr<Mesh>> Mesh::loadedMeshes;

		//==============================================================================
		std::shared_ptr<Mesh> MeshLoader::LoadMesh(char* _fileName)
		{
			std::string meshPath;
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			std::string err;

			bool fileLoaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, _fileName, "\\");


			std::shared_ptr<Mesh> returnMesh = std::make_shared<Mesh>();
			//If file was not found in local directory, search default "Meshes" directory as well
			if (fileLoaded)
			{
				//meshPath.append(_fileName);
			}
			else
			{
				meshPath = "Meshes\\";
				std::string fullPath = meshPath;
				fullPath.append(_fileName);
				fileLoaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, fullPath.c_str(), meshPath.c_str());
			}
			if (!fileLoaded)
			{
				meshPath = "..\\Meshes\\";
				std::string fullPath = meshPath;
				fullPath.append(_fileName);
				fileLoaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, fullPath.c_str(), meshPath.c_str());
			}

			//If we now have a fully loaded file
			if (fileLoaded)
			{
				for (size_t i = 0; i < attrib.vertices.size() / 3; i += 1)
				{
					returnMesh->rawVertices.push_back(
						glm::vec4(attrib.vertices.at(i * 3),
							attrib.vertices.at(i * 3 + 1),
							attrib.vertices.at(i * 3 + 2),
							1.0f)
					);
				}

				for (int i = 0; i < attrib.normals.size() / 3; i++)
				{
					returnMesh->rawNormals.push_back(
						glm::vec3(attrib.vertices.at(i * 3),
							attrib.normals.at(i * 3 + 1),
							attrib.normals.at(i * 3 + 2))
					);
				}

				for (int i = 0; i < attrib.texcoords.size() / 2; i++)
				{
					returnMesh->rawTexCoords.push_back(
						glm::vec2(attrib.texcoords.at(i * 2),
							attrib.texcoords.at(i * 2 + 1))
					);
				}

				returnMesh->RecalcBounds();

				float longestAxis = 0;



				// Loop over shapes
				for (size_t s = 0; s < shapes.size(); s++)
				{
					Triangle triangle;
					// Loop over triangles
					for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
					{
						int faceVertices = shapes[s].mesh.num_face_vertices[f];
						if (faceVertices != 3)
						{
							Debug::Log("Error - Non-triangle face loaded, this program only supports triangle meshes");
						}

						triangle.posIndices = glm::ivec3(
							shapes[s].mesh.indices.at(f * 3).vertex_index,
							shapes[s].mesh.indices.at(f * 3 + 1).vertex_index,
							shapes[s].mesh.indices.at(f * 3 + 2).vertex_index);

						triangle.texIndices = glm::ivec3(
							shapes[s].mesh.indices.at(f * 3).texcoord_index,
							shapes[s].mesh.indices.at(f * 3 + 1).texcoord_index,
							shapes[s].mesh.indices.at(f * 3 + 2).texcoord_index);

						triangle.normalIndices = glm::ivec3(
							shapes[s].mesh.indices.at(f * 3).normal_index,
							shapes[s].mesh.indices.at(f * 3 + 1).normal_index,
							shapes[s].mesh.indices.at(f * 3 + 2).normal_index);

						returnMesh->posVertices.push_back(returnMesh->rawVertices.at(triangle.posIndices.x));
						returnMesh->posVertices.push_back(returnMesh->rawVertices.at(triangle.posIndices.y));
						returnMesh->posVertices.push_back(returnMesh->rawVertices.at(triangle.posIndices.z));

						returnMesh->texVertices.push_back(returnMesh->rawTexCoords.at(triangle.texIndices.x));
						returnMesh->texVertices.push_back(returnMesh->rawTexCoords.at(triangle.texIndices.y));
						returnMesh->texVertices.push_back(returnMesh->rawTexCoords.at(triangle.texIndices.z));

						returnMesh->normalVertices.push_back(returnMesh->rawNormals.at(triangle.normalIndices.x));
						returnMesh->normalVertices.push_back(returnMesh->rawNormals.at(triangle.normalIndices.y));
						returnMesh->normalVertices.push_back(returnMesh->rawNormals.at(triangle.normalIndices.z));

					}
					returnMesh->triangles.push_back(triangle);
				}

				glm::vec3 size = returnMesh->GetBounds().GetSize();

				longestAxis = size.x;
				if (size.y > longestAxis) longestAxis = size.y;
				if (size.z > longestAxis) longestAxis = size.z;

				if (longestAxis > 1)
				{
					for (int i = 0; i < returnMesh->posVertices.size(); i++)
					{
						glm::vec4 scaled = glm::vec4(returnMesh->posVertices.at(i).x / longestAxis, returnMesh->posVertices.at(i).y / longestAxis, returnMesh->posVertices.at(i).z / longestAxis, 1);

						returnMesh->scaledPosVertices.push_back(scaled);
					}
					returnMesh->RecalcBounds();
				}
				else
				{
					returnMesh->scaledPosVertices = returnMesh->posVertices;
				}

				shapes[0].mesh.material_ids;

				for (size_t m = 0; m < materials.size(); m++)
				{
					tinyobj::material_t* mp = &materials[m];

					if (mp->diffuse_texname.length() > 0)
					{
						// Only load the texture if it is not already loaded
						if (Mesh::textures.find(mp->diffuse_texname) == Mesh::textures.end())
						{
							Mesh::textures.insert(LoadTexture(mp->diffuse_texname, meshPath));
						}
					}
				}

				if (materials.size() <= 0)
				{
					materials.push_back(tinyobj::material_t());
					materials.at(0).diffuse_texname = "defmat.bmp";
					if (Mesh::textures.find(materials.at(0).diffuse_texname) == Mesh::textures.end())
					{
						Mesh::textures.insert(LoadTexture(materials.at(0).diffuse_texname, meshPath));
					}
				}

				returnMesh->materials = materials;

			}

			Mesh::loadedMeshes.insert(std::make_pair(_fileName, returnMesh));

			return returnMesh;
		}//MeshLoader::LoadMesh
		 //==============================================================================
		 //Modified code snippet from: https://github.com/syoyo/tinyobjloader/blob/master/examples/viewer/
		std::pair<std::string, GLuint> MeshLoader::LoadTexture(std::string _fileName, std::string _filePath)
		{
			GLuint texture_id;
			int w, h;
			int comp;

			std::string texture_filename = _fileName;
			if (!FileExists(texture_filename))
			{
				// Append base dir.
				texture_filename = _filePath + _fileName;
				if (!FileExists(texture_filename))
				{
					Debug::LogError("Unable to find file: ", _fileName);
					//  exit(1);
				}
			}

			unsigned char* image = stbi_load(texture_filename.c_str(), &w, &h, &comp, STBI_default);
			if (!image) {
				Debug::LogError("Unable to load texture: ", texture_filename);
				exit(1);
			}
			Debug::Log("Loaded texture: ", texture_filename, ", w = ", w, ", h = ", h, ", comp = ", comp);

			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (comp == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			}
			else if (comp == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else {
				assert(0);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(image);
			return std::make_pair(_fileName, texture_id);
		}//MeshLoader::LoadTexture

		//==============================================================================
		//METHOD COPIED FROM: https://github.com/syoyo/tinyobjloader/blob/master/examples/viewer/viewer.cc
		bool MeshLoader::FileExists(const std::string &abs_filename)
		{
			bool ret{};
			errno_t err{};
			FILE *fp{};
			err = fopen_s(&fp, abs_filename.c_str(), "rb");

			if (fp)
			{
				ret = true;
				fclose(fp);
			}
			else
			{
				ret = false;
			}

			return ret;
		}//MeshLoader::FileExists()

	}
}