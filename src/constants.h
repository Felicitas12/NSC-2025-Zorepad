#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <glm/vec3.hpp>

// Earth's rotation and orbit
const double EARTH_ROTATION_PERIOD = 86164.0;  // Sidereal day in seconds
const double EARTH_ORBIT_RADIUS = 1000;       // 149.6 million km
const double EARTH_ORBIT_PERIOD = 365.25 * 24 * 3600;  // One year in seconds
const double EARTH_TILT_DEG = 23.439281;     // Axial tilt in degrees

// Sun's rotation
const double SUN_ROTATION_PERIOD = 25.0 * 24 * 3600;  // 25 days in seconds

// Axial tilts
const float earthDefaultAxis = 23.439281F * 0.01;
const float sunDefaultAxis = 7.25F * 0.01;

// ISS orbit
const double ISS_ALTITUDE_FROM_EARTH = -250.0;           // 408 km
const double CAMERA_ATTIDUE_TO_CUPOLA = ISS_ALTITUDE_FROM_EARTH - 1;
const double ISS_ORBIT_PERIOD = 92.68*2;   // 92.68 minutes in seconds

// Sizes for rendering
const float SUN_SIZE = 30.0F;
const float EARTH_SIZE = 0.4F;
const float ISS_SIZE = 0.75F;
const float CUPOLA_SIZE = 1.0F;

const glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 axisZ = glm::vec3(0.0f, 0.0f, 1.0f);
#endif