#pragma once

#include <map>
#include <string>
#include "Mesh.h"

class ModelCache {
public:
	Mesh getModel(std::string modelPath);

private:
	std::map<std::string, Mesh> m_modelMap;
};

