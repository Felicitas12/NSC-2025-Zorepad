#ifndef Entity_H
#define Entity_H


#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"
#include "FrustumCulling.h"
#include "ModelManager.h"


class Entity {
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    BoundingBox aabb;
    bool isModelMatrixDirty = true;

    btVector3 lastPosition;
    btQuaternion lastRotation;

    BoundingBox calculate_world_aabb(const BoundingBox &local_aabb) {
        BoundingBox aabb;
        aabb.min = glm::vec3(std::numeric_limits<float>::max());
        aabb.max = glm::vec3(std::numeric_limits<float>::lowest());

        const glm::vec3 corners[8] = {
            {local_aabb.min.x, local_aabb.min.y, local_aabb.min.z},
            {local_aabb.min.x, local_aabb.min.y, local_aabb.max.z},
            {local_aabb.min.x, local_aabb.max.y, local_aabb.min.z},
            {local_aabb.min.x, local_aabb.max.y, local_aabb.max.z},
            {local_aabb.max.x, local_aabb.min.y, local_aabb.min.z},
            {local_aabb.max.x, local_aabb.min.y, local_aabb.max.z},
            {local_aabb.max.x, local_aabb.max.y, local_aabb.min.z},
            {local_aabb.max.x, local_aabb.max.y, local_aabb.max.z},
        };

        const auto modelMatrix = getModelMatrix();

        for (int i = 0; i < 8; ++i) {
            glm::vec3 worldCorner = glm::vec3(modelMatrix * glm::vec4(corners[i], 1.0f));
            aabb.min = glm::min(aabb.min, worldCorner);
            aabb.max = glm::max(aabb.max, worldCorner);
        }
        return aabb;
    }

public:
    std::string Tag;
    std::shared_ptr<Model> model;
    btRigidBody *rigid_body = nullptr;

    ENGINE_API Entity(const std::string &name, const std::string &src) : Tag(name),
                                                                         model(ModelManager::getInstance().loadModel(src, true)) {
    }

    Entity() = default;

    ENGINE_API BoundingBox &get_aabb();

    ENGINE_API void set_aabb(const BoundingBox &aabb);

    ENGINE_API void checkIfMoved(float posEpsilon2 = 1e-6f, float rotEpsilon = 1e-4f);

    ENGINE_API glm::vec3 get_pos();

    ENGINE_API void set_position(const glm::vec3 &position);

    ENGINE_API glm::vec3 &get_scale();

    ENGINE_API void set_scale(const glm::vec3 &scale);

    ENGINE_API glm::quat get_rot();

    ENGINE_API void set_rotation(glm::quat rot);

    ENGINE_API void set_rotation(const glm::vec3 &axis, float angleRadians);

    ENGINE_API virtual void draw(const Shader &shader);

    ENGINE_API void draw_raw(const Shader &shader);

    ENGINE_API void draw_custom_mat(const Shader &shader, const glm::mat4 &mat);

    ENGINE_API void make_collision(uint64_t uuid, const std::string &path, bool disable_draw_collision = false);

    ENGINE_API glm::mat4 getModelMatrix();


};
#endif
