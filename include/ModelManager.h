#pragma once

#include <string>

class ModelManager
{
public:
    static ENGINE_API ModelManager& getInstance();

    ENGINE_API std::shared_ptr<Model> loadModel(const std::string& path, bool gamma = false);
    ENGINE_API std::unordered_map<std::string, std::shared_ptr<Model>>& getModelCache();
private:
    std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;

    ModelManager() = default;
    ~ModelManager() = default;

    ModelManager(const ModelManager&) = delete;
    ModelManager& operator=(const ModelManager&) = delete;
};
