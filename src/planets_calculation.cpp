#include "planets_calculation.h"
#include "constants.h"

//void updateEarth(Entity& earth, float deltaTime, float& orbitAngle, float& selfRotationAngle) {
//    // Угол по орбите
//    orbitAngle += EARTH_ORBIT_SPEED * deltaTime;
//    if (orbitAngle > glm::two_pi<float>())
//        orbitAngle -= glm::two_pi<float>();
//
//    // Позиция Земли на орбите
//    float x = cos(orbitAngle) * EARTH_ORBIT_RADIUS;
//    float z = sin(orbitAngle) * EARTH_ORBIT_RADIUS;
//    earth.set_position(glm::vec3(x, 0.0f, z));
//
//    // Вращение Земли вокруг своей оси
//    selfRotationAngle += EARTH_ROTATION_SPEED * deltaTime;
//    if (selfRotationAngle > glm::two_pi<float>())
//        selfRotationAngle -= glm::two_pi<float>();
//
//    earth.set_rotation(EARTH_AXIS_TILT, selfRotationAngle);
//}