#ifndef RENDER_H
#define RENDER_H

#include <glad/gl.h>
#include "Export.h"
#include <glm/mat4x4.hpp>
#include "LightSources.h"
class Model;
class GUIHandler;
class GUITexture;

class PlayerController;

class BulletDebugDrawer;
class BloomRenderer;
class Shader;
class IBLMapRenderer;

class Render
{

public:

	void init(PlayerController const& player);
	void ENGINE_API init_buffers(int width, int height);
	void init_quad_renderer();

	void draw(PlayerController& player, GUIHandler& gui_handler);
	void clear();
	static void render_cube();
	static void render_quad();
	void render_sphere();

	static void resize_viewport(int width, int height, GUIHandler& gui_handler);
	static void create_viewport(int width, int height);
	static GLuint create_pixel_texture(unsigned char color);
	static GLuint create_rgb_pixel_texture();

	static unsigned int dsa_load_texture(const char* path, bool srgb = false);
	static GUITexture dsa_load_texture_iwh(const char* path, bool srgb = false);
	static unsigned int get_viewport_texture_ID();
	static glm::mat4& get_proj();
	static void set_proj(const glm::mat4 &proj);
	static unsigned int get_viewport_renderbuffer_ID();


	ENGINE_API static LightSources& getLightSources();

};

#endif