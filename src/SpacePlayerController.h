#pragma once
#include "IPlayerController.h"
#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "LinearMath/btDefaultMotionState.h"

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 25.0f;
constexpr float SENSITIVITY = 0.1f;
constexpr float FOV = 90.0f;

class SpacePlayerController : public IPlayerController
{
public:
	glm::vec3 spectator_camera_position = glm::vec3(0.0f);
	bool is_spectator = true;

	static float Yaw;
	static float Pitch;
	static float MouseSensitivity;
	static glm::quat Rotation;

	float MovementSpeed;
	float SpectatorMovementSpeed;

	float Fov;
	btVector3 direction_velocity;
	btRigidBody* playerRigidBody;
	float mSpeedDamping;
	bool on_ground = false;
	bool leftshift_pressed = false;
	bool leftctrl_pressed = false;

	btScalar mMaxLinearVelocity2 = pow(15 / 3.6, 2);
	SoundDevice* character_listener = nullptr;
	SoundEffectsPlayer player;

	SpacePlayerController(float mass, float stepHeight, float x, float y, float z, float yaw = YAW, float pitch = PITCH)
	: SpectatorMovementSpeed(SPEED), MovementSpeed(SPEED), Fov(FOV), player("player"), direction_velocity(0.0f, 0.0f, 0.0f), mSpeedDamping(0.1f)
	{
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
		MouseSensitivity = SENSITIVITY;
		btTransform btTransform;
		btTransform.setIdentity();
		btTransform.setOrigin(btVector3(x, y, z));
		btCapsuleShape* playerShape = new btCapsuleShape(0.25F, 0.45F);

		btVector3 inertia(0, 0, 0);
		if (mass != 0.0)
		{
			playerShape->calculateLocalInertia(mass, inertia);
		}
		btMotionState* motion = new btDefaultMotionState(btTransform);
		btRigidBody::btRigidBodyConstructionInfo info(mass, motion, playerShape, inertia);
		//info.m_restitution = 0.0F;

		playerRigidBody = new btRigidBody(info);
		playerRigidBody->setActivationState(DISABLE_DEACTIVATION);
		playerRigidBody->setAngularFactor(0.0F);
		//playerRigidBody->setSleepingThresholds(0.0, 0.0);

		//playerRigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

		//playerRigidBody->setFriction(0.1);
		//playerRigidBody->setCcdSweptSphereRadius(0.2f);

	}

	void InitSound() override;

	//void init(float mass, float stepHeight, float x, float y, float z, float yaw = YAW, float pitch = PITCH);

	void ProcessKeyboard(Camera_Movement_State direction, double deltaTime) override;

	void change_mode(bool save_pos) override;

	void UpdateVectors() override;

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) override;

	void ProcessMouseScroll(float yoffset) override;

	glm::vec3 getPosition() const override;

	glm::mat4 GetViewMatrix() override;

	void SetFov(float fov) override { Fov = fov; }
	void SetPhysicsBody(btRigidBody* rigid_body) override { playerRigidBody = rigid_body; }
	void SetSpectatorSpeed(float spectatorMovementSpeed) override { SpectatorMovementSpeed = spectatorMovementSpeed; }

	float GetFov() const override { return Fov; }
	btRigidBody* GetPhysicsBody() const override { return playerRigidBody; }
	float& GetSpectatorSpeed() override { return SpectatorMovementSpeed; }

private:
	// calculates the front vector from the Camera's (updated) Euler Angles
	static void updateCameraVectors()
	{


		glm::quat aroundY = glm::angleAxis(glm::radians(-Yaw), glm::vec3(0, 1, 0));

		// Pitch
		glm::quat aroundX = glm::angleAxis(glm::radians(Pitch), glm::vec3(1, 0, 0));

		Rotation = aroundY * aroundX;

	}



};
