#include "constants.h"

// Earth's rotation and orbit
const double EARTH_ROTATION_PERIOD = 86164.0;  // Sidereal day in seconds
const double EARTH_ORBIT_RADIUS = 1000;    // 149.6 million km
const double EARTH_ORBIT_PERIOD = 365.25 * 24 * 3600;  // One year in seconds
const double EARTH_TILT_DEG = 23.439281;       // Axial tilt in degrees

// Sun's rotation
const double SUN_ROTATION_PERIOD = 25.0 * 24 * 3600;  // 25 days in seconds

constexpr float earthDefaultAxis = 23.439281F * 0.01;
constexpr float sunDefaultAxis = 7.25F * 0.01;

// ISS orbit
const double ISS_ALTITUDE = -700.0;          // 408 km
const double ISS_ORBIT_PERIOD = 92.68 * 60;    // 92.68 minutes in seconds

// Sizes for rendering
const float SUN_SIZE = 12.0F;
const float EARTH_SIZE = 1.0F;
const float ISS_SIZE = 2.5F;
const float CUPOLA_SIZE = 1.0F;