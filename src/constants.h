#ifndef CONSTANTS_H
#define CONSTANTS_H

// Earth's rotation and orbit
extern const double EARTH_ROTATION_PERIOD;  // Seconds for one full rotation
extern const double EARTH_ORBIT_RADIUS;    // Distance from the Sun (meters)
extern const double EARTH_ORBIT_PERIOD;    // Seconds for one full orbit
extern const double EARTH_TILT_DEG;        // Earth's axial tilt (degrees)

// Sun's rotation
extern const double SUN_ROTATION_PERIOD;   // Seconds for one full rotation

// ISS orbit
extern const double ISS_ALTITUDE;          // Altitude above Earth's surface (meters)
extern const double ISS_ORBIT_PERIOD;      // Seconds for one full orbit

extern const float earthDefaultAxis;
extern const float sunDefaultAxis;
extern const float issDefaultAxis;

// Sizes for rendering
extern const float SUN_SIZE;
extern const float EARTH_SIZE;
extern const float ISS_SIZE;
extern const float CUPOLA_SIZE;
#endif