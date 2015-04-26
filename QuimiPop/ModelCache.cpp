#include "ModelCache.h"

Mesh ModelCache::getModel(std::string modelPath) {
	auto it = m_modelMap.find(modelPath);

	if (it == m_modelMap.end()) {
		Mesh newMesh;
		newMesh.loadMesh(modelPath);

		std::pair<std::string, Mesh> newPair(modelPath, newMesh);
		m_modelMap.insert(newPair);
		
		return newMesh;
	}

	// return the second element of the <string, GLTexture> pair
	return it->second;
}