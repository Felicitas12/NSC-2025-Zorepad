// IPlayerController.h (в вашем движке)
#ifndef IPLAYERCONTROLLER_H
#define IPLAYERCONTROLLER_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BulletDynamics/Dynamics/btRigidBody.h"

enum Camera_Movement_State {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    LEFT_SHIFT,
    LEFT_CTRL
};

class IPlayerController {
public:
    virtual ~IPlayerController() = default;

    // Виртуальные методы для переопределения
    virtual void ProcessKeyboard(Camera_Movement_State direction, double deltaTime) = 0;
    virtual void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) = 0;
    virtual void ProcessMouseScroll(float yoffset) = 0;
    virtual void UpdateVectors() = 0;
    virtual void change_mode(bool save_pos) = 0;

    virtual void InitSound() = 0;


    virtual float GetFov() const = 0;
    virtual btRigidBody* GetPhysicsBody() const = 0;
    virtual float& GetSpectatorSpeed() = 0;

    virtual void SetFov(float fov) = 0;
    virtual void SetPhysicsBody(btRigidBody* rigid_body) = 0;
    virtual void SetSpectatorSpeed(float fov) = 0;

    virtual void SetRotation(glm::quat rotation) = 0;

    virtual glm::vec3 getPosition() const = 0;
    virtual glm::quat getRotation() const = 0;
    virtual glm::mat4 GetViewMatrix() = 0;


};

#endif