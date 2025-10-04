#pragma once


#include <string>

#include "Export.h"
#include "Scene.h"


class SceneSerializer
{
public:

	void ENGINE_API Serialize(const std::string& filepath);
	void ENGINE_API SerializeRuntime(const std::string& filepath);

	bool ENGINE_API Deserialize(const std::string& filepath);
	bool ENGINE_API DeserializeRuntime(const std::string& filepath);

};
