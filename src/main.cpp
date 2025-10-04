// Engine imports
#include <Engine.h>
#include <iostream>
#include <Window.h>
#include <Entity.h>
#include <UUID.h>
#include <Scene.h>

// Other stuff
#include <string>
#include <glm/ext/quaternion_trigonometric.hpp>
#include "constants.h"
#include "Input.h"
#include "SpacePlayerController.h"

int main() {

    auto custom_camera = std::make_unique<SpacePlayerController>(50.0f, 0.5f, 0.0f, 0.0f, 0.0f);
    Scene::SetCamera(std::move(custom_camera));

    // Constants and variables zone
    constexpr float fullPi = glm::pi<float>();

    float earthAxis = glm::radians(earthDefaultAxis);
    glm::vec3 axisFull(0.0f, 0.0f, 1.0f);
    glm::vec3 earthAxisTilted = glm::normalize(glm::vec3(0.0f, glm::sin(glm::radians(earthDefaultAxis)), glm::cos(glm::radians(earthDefaultAxis))));
    glm::quat earthAngle = glm::angleAxis(earthAxis, earthAxisTilted);
    glm::vec3 sunPosition = glm::vec3(0.0F, 0.0F, 0.0F);
    Engine::Initialize();

	/*SceneSerializer ss; // Loads scence from a file, but now is not existing
     ss.Deserialize("scene.yaml");*/

    Engine::GetRender().init_buffers(Window::GetWindowWidth(), Window::GetWindowHeight());

    Engine::InputInitialize();

    // Sun creation
	Entity* sun = new Entity("Sun", "assets/objects/SpaceItems/sun.glb");
    sun->set_scale(glm::vec3(SUN_SIZE));
	sun->set_position(sunPosition);
    auto sunUUID = UUID();
    Scene::createEntityWithUUID(sunUUID, sun);

    // ISS creation
    Entity* iss = new Entity("ISS", "assets/objects/SpaceItems/ISS_stationary.glb");
    iss->set_scale(glm::vec3(ISS_SIZE));
    iss->set_position(glm::vec3(-700.0F, 0.0F, -700.0F));
    iss->set_rotation(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f));
    auto issUUID = UUID();
    Scene::createEntityWithUUID(issUUID, iss);

    // Earth Creation
    Entity* earth = new Entity("Earth", "assets/objects/SpaceItems/Earth_1_12756.glb");
    auto earthUUID = UUID();
    earth->set_scale(glm::vec3(EARTH_SIZE));
	earth->set_position(glm::vec3(500.0F, 0.0F, 500.0F));
    //earth.set_rotation(earthAxisTilted, glm::radians(360.0f));
	Scene::createEntityWithUUID(earthUUID, earth);
   
    // Cupula Creation
    Entity* cupola = new Entity("Cupola", "assets/objects/SpaceItems/kupola.glb");
    auto cupolaUUID = UUID();
    cupola->set_scale(glm::vec3());
    cupola->set_position(glm::vec3(-500.0F, 0.0F, -500.0F));
    //earth.set_rotation(earthAxisTilted, glm::radians(360.0f));
    Scene::createEntityWithUUID(cupolaUUID, cupola);


    // Time variables
    double elapsedTime = 0.0;
    while (!Window::ShouldClose())
    {
        Input::TickTimer();
        Input::Tick(Engine::GetRender(), Engine::GetGuiHandler(), Window::GetWindow());
        //std::cout << "Earth pos: " << earth.get_pos() << "\n";
        //earth.set_rotation(earthAxisTilted, earthAxis);
        elapsedTime += Input::GetDeltaTime();

        
        // Sun rotation
        float sunRotationAngle = static_cast<float>((elapsedTime / SUN_ROTATION_PERIOD) * glm::two_pi<double>());
        sun->set_rotation(glm::vec3(0.0f, 1.0f, 0.0f), sunRotationAngle);

        // Earth rotation (on its axis)
        float earthRotationAngle = static_cast<float>((elapsedTime / EARTH_ROTATION_PERIOD) * glm::two_pi<double>());
        earth->set_rotation(glm::vec3(0.0f, 1.0f, 0.0f), earthRotationAngle);

        // Earth orbit around the Sun
        float earthOrbitAngle = static_cast<float>((elapsedTime / EARTH_ORBIT_PERIOD) * glm::two_pi<double>());
        glm::mat4 earthOrbitRotation = glm::rotate(glm::mat4(1.0f), earthOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 earthPosition = glm::vec3(
            EARTH_ORBIT_RADIUS * glm::cos(earthOrbitAngle),
            0.0f,
            EARTH_ORBIT_RADIUS * glm::sin(earthOrbitAngle)
        );
        earth->set_position(earthPosition);

        // ISS orbit around the Earth
        float issOrbitAngle = static_cast<float>((elapsedTime / ISS_ORBIT_PERIOD) * glm::two_pi<double>());
        glm::mat4 issOrbitRotation = glm::rotate(glm::mat4(1.0f), issOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 issLocalPosition = glm::vec3(
            ISS_ALTITUDE * glm::cos(issOrbitAngle),
            0.0f,
            ISS_ALTITUDE * glm::sin(issOrbitAngle)
        );
        iss->set_position(earth->get_pos() + issLocalPosition);
        /*earth.set_rotation(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(1.0f));*/
        // Render::getLightSources().set_directional_light(0, glm::normalize(-earth_pos), glm::vec3{ 6.0f });
		// take the existing light and change its direction

		// Render::getLightSources().send_changes(); all changes with lighting to shaders
        Engine::Tick();
		Window::SwapBuffers();
    }
    Engine::Clear();

    return 0;
}
