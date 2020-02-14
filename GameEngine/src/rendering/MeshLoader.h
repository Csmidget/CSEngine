#ifndef GAME_ENGINE_MESHLOADER_H
#define GAME_ENGINE_MESHLOADER_H



namespace GameEngine {
	class Mesh;

	//!Class in control of loading Meshes into application from .obj files.
	class MeshLoader
	{

	public:
		//!Loads in an .obj file and converts it into a mesh. 
		static std::shared_ptr<Mesh> LoadMesh(char* _fileName);
		//!Tests that the file entered exists.
		static bool FileExists(const std::string& abs_filename);
		//!Attempts to load a texture and returns the name and texture value
		static std::pair<std::string, GLuint> LoadTexture(std::string _fileName, std::string _filePath);
	};
}

#endif