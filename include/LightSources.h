#ifndef LIGHTSOURCES_H
#define LIGHTSOURCES_H

#include <vector>
#include <glm\glm.hpp>

#include "Export.h"

struct PointLight {
	glm::vec3 pos;
	float n1;
	glm::vec3 color;
	float n2;
};

struct DirectionalLight {
	glm::vec3 direction;
	float n1;
	glm::vec3 color;
	float n2;
};

struct SpotLight {
	glm::vec3 pos;
	float n1;
	glm::vec3 direction;
	float cutoff;
	glm::vec3 color;
	float outerCutoff;
};

struct LightBlock {
	int numPointLights;
	int numDirLights;
	int numSpotLights;
	int padding;  // Паддинг для выравнивания до 16 байт

	// Массивы света будут добавлены отдельно при копировании
};


class LightSources {
public:
	const size_t max_p_size = 15;
	const size_t max_d_size = 2;
	const size_t max_s_size = 2;

	size_t point_light_size = 0;
	size_t directional_light_size = 0;
	size_t spot_light_size = 0;

	LightSources(size_t max_p_light_size, size_t max_d_light_size, size_t max_s_light_size)
		: max_p_size(max_p_light_size), max_d_size(max_d_light_size), max_s_size(max_s_light_size) {}

	std::vector<PointLight> pointLights;
	std::vector<DirectionalLight> directionalLights;
	std::vector<SpotLight> spotLights;

	unsigned int ubo_id;

	void init();

	ENGINE_API void add_point_light(glm::vec3 pos, glm::vec3 color);

	ENGINE_API void add_directional_light(glm::vec3 direction, glm::vec3 color);

	ENGINE_API void add_spot_light(const glm::vec3 &pos, const glm::vec3 &dir, const float &cutoff, const float &outerCutoff, const glm::vec3 &color);

	ENGINE_API void set_point_light(size_t h_first, glm::vec3 pos, glm::vec3 color);

	ENGINE_API void set_directional_light(size_t h_first, glm::vec3 direction, glm::vec3 color);

	ENGINE_API void set_spot_light(size_t h_first, const glm::vec3& pos, const glm::vec3& dir, const float& cutoff, const float& outerCutoff, const glm::vec3& color);

	ENGINE_API DirectionalLight get_directional_light(size_t h);

	ENGINE_API PointLight get_point_light(size_t h);

	ENGINE_API SpotLight get_spot_light(size_t h);

	ENGINE_API void clear_point_light();

	ENGINE_API void clear_directional_light();

	ENGINE_API void clear_spot_light();

	ENGINE_API void send_changes();

private:
	unsigned int id_point_light;
	unsigned int id_directional_light;
	unsigned int id_spotlight_light;
};

#endif