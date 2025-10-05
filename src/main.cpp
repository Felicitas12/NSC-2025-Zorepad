#define GLM_ENABLE_EXPERIMENTAL

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
#include <glm/gtx/quaternion.hpp>

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
    sun->set_draw_shadow(true);
    auto sunUUID = UUID();
    Scene::createEntityWithUUID(sunUUID, sun);

    // ISS creation
    Entity* iss = new Entity("ISS", "assets/objects/SpaceItems/ISS_stationary.glb");
	iss->set_scale(glm::vec3(ISS_SIZE));
    iss->set_position(glm::vec3(-700.0F, 0.0F, -700.0F));
    iss->set_rotation(glm::vec3(axisY), glm::radians(180.0f));
    //iss->set_rotation()
    auto issUUID = UUID();
    //iss->make_collision(issUUID, "assets/objects/SpaceItems/ISS_stationary.glb", false);

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
    cupola->set_scale(glm::vec3(3.0F));
    cupola->set_position(glm::vec3(500.0F, 0.0F, 500.0F));
    //earth.set_rotation(earthAxisTilted, glm::radians(360.0f));
    Scene::createEntityWithUUID(cupolaUUID, cupola);


    // Time variables
    double elapsedTime = 0.0;
    float sunRotationAngle = 0.0f;
    float earthRotationAngle = 0.0f;
    float earthOrbitAngle = 0.0f;
    float issOrbitAngle = 0.0f;

    while (!Window::ShouldClose())
    {
        Input::TickTimer();
        Input::Tick(Engine::GetRender(), Engine::GetGuiHandler(), Window::GetWindow());
		std::cout << "Earht pos: " << earth->get_pos().x << " " << earth->get_pos().y << " " << earth->get_pos().z << "\n";
        // Get the time difference between frames
        float deltaTime = static_cast<float>(Input::GetDeltaTime());

        // Incremental Sun rotation
        sunRotationAngle = sunDefaultAxis * deltaTime;
        sun->set_rotation(axisY, sunRotationAngle);

        // Incremental Earth rotation (on its axis)
        earthRotationAngle = earthDefaultAxis * deltaTime;
        earth->set_rotation(axisY, earthRotationAngle);

        // Incremental Earth orbit around the Sun
        earthOrbitAngle += (deltaTime / EARTH_ORBIT_PERIOD) * glm::two_pi<float>();
        glm::vec3 earthPosition = glm::vec3(
            EARTH_ORBIT_RADIUS * glm::cos(earthOrbitAngle),
            0.0f,
            EARTH_ORBIT_RADIUS * glm::sin(earthOrbitAngle)
        );
        earth->set_position(earthPosition);

        // Incremental ISS orbit around the Earth
        issOrbitAngle -= (deltaTime / ISS_ORBIT_PERIOD) * glm::two_pi<float>();
        glm::vec3 issLocalPosition = glm::vec3(
            ISS_ALTITUDE * glm::cos(issOrbitAngle),
            ISS_ALTITUDE * glm::sin(issOrbitAngle), // Assuming the orbit is in the XZ plane
            0.0f
        );
        glm::vec3 issWorldPosition = earth->get_pos() + issLocalPosition;
        iss->set_position(issWorldPosition);

        // Calculate the direction vector from ISS to Earth
        glm::vec3 directionToEarth = glm::normalize(earth->get_pos() - issWorldPosition);

        // Calculate the rotation to align the ISS's forward vector with the directionToEarth
        glm::quat lookQuat = glm::rotation(glm::vec3(0, -1, 0), directionToEarth);

        // Set the ISS's rotation
        iss->set_rotation(lookQuat);

        // Update lighting
        Render::getLightSources().set_directional_light(0, glm::normalize(earthPosition), glm::vec3{ 6.0f });
        Render::getLightSources().send_changes();
        // Engine tick and buffer swap
        Engine::Tick();
        Window::SwapBuffers();
    }
    Engine::Clear();

    return 0;
}
