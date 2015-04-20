#include "Mesh.h"

Mesh::MeshEntry::MeshEntry()
{
	vB = 0;
	iB = 0;
	numIndices = 0;
	materialIndex = 0;
}

Mesh::MeshEntry::~MeshEntry()
{
	if (vB != 0) {
		glDeleteBuffers(1, &vB);
	}

	if (iB != 0) {
		glDeleteBuffers(1, &iB);
	}
}

void Mesh::MeshEntry::init(const std::vector<Vertex3D>& vertices,
	const std::vector<unsigned int>& indices)
{
	numIndices = indices.size();

	glGenBuffers(1, &vB);
	glBindBuffer(GL_ARRAY_BUFFER, vB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &iB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::clear()
{
	m_entries.clear();
	m_textures.clear();
}

void Mesh::loadMesh(const std::string& filename)
{
	// Release the previously loaded mesh (if it exists)
	clear();

	bool ret = false;
	Assimp::Importer importer;
	
	const aiScene* pScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) {
		initFromScene(pScene, filename);
	}
	else {
		printf("Error parsing \'%s\': %s\n", filename.c_str(), importer.GetErrorString());
		fatalError("Failed to import mesh!");
	}
}

void Mesh::initFromScene(const aiScene* pScene, const std::string& filename)
{
	m_entries.resize(pScene->mNumMeshes);
	m_textures.resize(pScene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	initMaterials(pScene, filename);
}

void Mesh::initMesh(unsigned int index, const aiMesh* paiMesh)
{
	m_entries[index].materialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex3D> vertices;
	std::vector<unsigned int> indices;

	const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]) ? &(paiMesh->mNormals[i]) : &zero3D;
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

		Vertex3D v(glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z));

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	m_entries[index].init(vertices, indices);
}

void Mesh::initMaterials(const aiScene* pScene, const std::string& filename)
{
	// Extract the directory part from the file name
	std::string::size_type slashIndex = filename.find_last_of("/");
	std::string dir;

	if (slashIndex == std::string::npos) {
		dir = ".";
	}
	else if (slashIndex == 0) {
		dir = "/";
	}
	else {
		dir = filename.substr(0, slashIndex);
	}

	// Initialize the materials
	printf("Number of materials in mesh: %d\n", pScene->mNumMaterials);
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		m_textures[i] = 0;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			printf("Diffuse texture.\n");
			aiString path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullPath = dir + "/" + path.data;
				printf("Reading texture: %s\n", fullPath);
				m_textures[i] = ResourceManager::getTexture(fullPath).textureId;
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (m_textures[i] == 0) {
			m_textures[i] = ResourceManager::getTexture("Textures/solid_white.png").textureId;
		}
	}
}

void Mesh::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_entries.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, m_entries[i].vB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, pos));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, uv));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, normal));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_entries[i].iB);

		const unsigned int materialIndex = m_entries[i].materialIndex;

		glBindTexture(GL_TEXTURE_2D, m_textures[materialIndex]);
		
		glDrawElements(GL_TRIANGLES, m_entries[i].numIndices, GL_UNSIGNED_INT, 0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}