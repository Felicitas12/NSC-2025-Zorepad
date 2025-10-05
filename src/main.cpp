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
    auto issUUID = UUID();
    iss->make_collision(issUUID, "assets/objects/SpaceItems/ISS_stationary.glb", false);

    Scene::createEntityWithUUID(issUUID, iss);

    // Earth Creation
    Entity* earth = new Entity("Earth", "assets/objects/SpaceItems/Earth_1_12756.glb");
    auto earthUUID = UUID();
    earth->set_scale(glm::vec3(EARTH_SIZE));
	earth->set_position(glm::vec3(500.0F, 0.0F, 500.0F));
    //earth.set_rotation(earthAxisTilted, glm::radians(360.0f));
	Scene::createEntityWithUUID(earthUUID, earth);
   
    // Cupula Creation
    Entity* cupola = new Entity("cupola", "assets/objects/SpaceItems/kupola_3.glb");
    cupola->set_scale(glm::vec3(ISS_SIZE));
    auto сupolaUUID = UUID();
    //iss->make_collision(issUUID, "assets/objects/SpaceItems/ISS_stationary.glb", false);

    Scene::createEntityWithUUID(сupolaUUID, cupola);
    

    // Time variables
    double elapsedTime = 0.0;
    float sunRotationAngle = 0.0f;
    float earthRotationAngle = 0.0f;
    float earthOrbitAngle = 0.0f;
    float issOrbitAngle = 0.0f;
	float cameraOrbitAngle = 0.0f;
	float cupolaOrbitAngle = 0.0f;

    glm::vec3 cupolaWorldPosition;
    glm::vec3 issWorldPosition;

    Render::getLightSources().add_point_light(glm::vec3(0), glm::vec3{ 6.0f });
    while (!Window::ShouldClose())
    {
        Input::TickTimer();
        Input::Tick(Engine::GetRender(), Engine::GetGuiHandler(), Window::GetWindow());
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

		// ISS orbit around the Earth --------------------------------------------------- Uncomment/Comments to see ISS
        //issOrbitAngle -= (deltaTime / ISS_ORBIT_PERIOD) * glm::two_pi<float>();
        //glm::vec3 issLocalPosition = glm::vec3(
        //    ISS_ALTITUDE_FROM_EARTH * glm::cos(issOrbitAngle),
        //    ISS_ALTITUDE_FROM_EARTH * glm::sin(issOrbitAngle), // Assuming the orbit is in the XZ plane
        //    0.0f
        //);
        //glm::vec3 issWorldPosition = earth->get_pos() + issLocalPosition;
        //iss->set_position(issWorldPosition);

        // Cupola orbit around the Earth
        cupolaOrbitAngle -= (deltaTime / ISS_ORBIT_PERIOD) * glm::two_pi<float>();
        glm::vec3 cupolaLocalPosition = glm::vec3(
            ISS_ALTITUDE_FROM_EARTH * glm::cos(cupolaOrbitAngle),
            ISS_ALTITUDE_FROM_EARTH * glm::sin(cupolaOrbitAngle), // Assuming the orbit is in the XZ plane
            0.0f
        );
        glm::vec3 cupolaWorldPosition = earth->get_pos() + cupolaLocalPosition;
        cupola->set_position(cupolaWorldPosition);

		// Calculation of camera position in cupola around the Earth --------------------------------------------------- Uncomment/Comments to see Cupola
        cameraOrbitAngle -= (deltaTime / ISS_ORBIT_PERIOD) * glm::two_pi<float>();
        glm::vec3 cameraLocalPosition = glm::vec3(
            CAMERA_ATTIDUE_TO_CUPOLA * glm::cos(cameraOrbitAngle),
            CAMERA_ATTIDUE_TO_CUPOLA * glm::sin(cameraOrbitAngle), // Assuming the orbit is in the XZ plane
            0.0f
        );
        glm::vec3 cameraWorldPosition = earth->get_pos() + cameraLocalPosition;

		// Define directionToEarth before using it
		glm::vec3 directionToEarth = glm::vec3(0.0f); // Default initialization

		// Set ISS rotation to always face the Earth
        if (cupolaOrbitAngle != 0) {
            directionToEarth = glm::normalize(earth->get_pos() - cupolaWorldPosition);
            glm::quat lookQuat = glm::rotation(glm::vec3(axisY), directionToEarth);
            cupola->set_rotation(lookQuat);
        }
        else if (issOrbitAngle != 0) {
            directionToEarth = glm::normalize(earth->get_pos() - issWorldPosition);
            glm::quat lookQuat = glm::rotation(glm::vec3(axisY), directionToEarth);
            cupola->set_rotation(lookQuat);
        }
        
        // Update lighting
        Render::getLightSources().set_directional_light(0, glm::normalize(cameraWorldPosition), glm::vec3{ 6.0f });
        Render::getLightSources().set_point_light(0, iss->get_pos(), glm::vec3{6.0f});
        Render::getLightSources().send_changes();
        // Engine tick and buffer swap

        // Camera logic
        glm::vec3 cupolaPosition = cupola->get_pos();
        glm::quat cupolaRotation = cupola->get_rot();

        // Define the offset to align the camera with the cupola's window
        glm::quat windowOffset = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Adjust as needed
        glm::quat windowOffset2 = glm::angleAxis(glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Adjust as needed
        // Combine the cupola's rotation with the offset
        glm::quat finalCameraRotation = cupolaRotation * windowOffset * windowOffset2;

        // Set the camera's rotation
		Scene::GetCamera()->SetRotation(finalCameraRotation); // Uncoment to make a camera movable

        auto cameraBody = Scene::GetCamera()->GetPhysicsBody();
        btVector3 newCameraPos(cameraWorldPosition.x, cameraWorldPosition.y, cameraWorldPosition.z); // нужная позиция

        btTransform transform;
		cameraBody->getMotionState()->getWorldTransform(transform); // getting current transform
        transform.setOrigin(newCameraPos);

        cameraBody->setWorldTransform(transform);
        cameraBody->getMotionState()->setWorldTransform(transform);

        Engine::Tick();
        Window::SwapBuffers();
    }
    Engine::Clear();

    return 0;
}
