#pragma once

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "GLSLProgram.h"
#include "Errors.h"

struct Vertex3D
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex3D() {}

	Vertex3D(glm::vec3 Pos, glm::vec2 UV, glm::vec3 Normal) : pos(Pos), uv(UV), normal(Normal) {}
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void loadMesh(const std::string& Filename);
	void render(GLSLProgram& renderProgram);

private:
	void initFromScene(const aiScene* pScene, const std::string& filename);
	void initMesh(unsigned int Index, const aiMesh* paiMesh);
	void initMaterials(const aiScene* pScene, const std::string& filename);
	void clear();

	struct MeshEntry {
		MeshEntry();
		~MeshEntry();

		void init(const std::vector<Vertex3D>& vertices, const std::vector<unsigned int>& indices);
		
		GLuint vB;
		GLuint iB;
		unsigned int numIndices;
		unsigned int materialIndex;
	};

	std::vector<MeshEntry> m_entries;
	std::vector<aiColor3D> m_materials;
};

