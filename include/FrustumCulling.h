#pragma once

#include <array>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
#include <thread>
#include <mutex>
#include <smmintrin.h>
#include <vector>

struct FrustumPlane {
    glm::vec3 normal;
    float distance;

    inline bool isOutside(const glm::vec3& point, float radius) const {
        return glm::dot(normal, point) + distance + radius < 0.0f;
    }
};
struct BoundingBox { glm::vec3 min, max; };

struct Frustum {
    FrustumPlane planes[6];

    void toVec4Array(glm::vec4* outArray) const {
        for (int i = 0; i < 6; i++) {
            outArray[i] = glm::vec4(planes[i].normal, planes[i].distance);
        }
    }
};

class FrustumCulling {
public:
    static std::array<FrustumPlane, 6> ExtractFrustumPlanes(const glm::mat4& VP);

    static Frustum ExtractFrustum(const glm::mat4& viewProj);

    static void FrustumCullMultithreaded(
        const std::vector<glm::mat4>& allMatrices,
        std::vector<glm::mat4>& visibleMatrices,
        const std::array<FrustumPlane, 6>& frustumPlanes,
        float boundingRadius = 10.1f,
        int numThreads = 1
    );
 
    static bool IsBoxInsideFrustum_SIMD(const BoundingBox& box, const Frustum& frustum);
    static inline bool IsSphereInsideFrustum_SIMD(const glm::vec3& center, float radius, const Frustum& frustum);
};
