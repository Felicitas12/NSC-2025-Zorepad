#include "SpacePlayerController.h"

#include <algorithm>
#include <iostream>

#include "IPlayerController.h"
#include "../include/Engine.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

class Physics;

float SpacePlayerController::Yaw;
float SpacePlayerController::Pitch;
float SpacePlayerController::MouseSensitivity;
glm::quat SpacePlayerController::Rotation;



void SpacePlayerController::ProcessKeyboard(Camera_Movement_State direction, double deltaTime)
{

	const glm::quat qF = Rotation * glm::quat(0, 0, 0, -1) * glm::conjugate(Rotation);

	const glm::vec3 Front = { qF.x, qF.y, qF.z };
	const glm::vec3 Right = glm::normalize(glm::cross(glm::vec3(qF.x, qF.y, qF.z), glm::vec3(0.0f, 1.0f, 0.0f)));
	//btTransform t;
	//playerRigidBody->getMotionState()->getWorldTransform(t);
	//btVector3 origin = t.getOrigin();
	//glm::vec3 currentPos = { origin.getX(),0.0f, origin.getZ() };

	/*btVector3	bt_velocity;
	btVector3	v_new;
	bt_velocity = this->playerRigidBody->getLinearVelocity();*/


	if (is_spectator) {
		const float velocity = SpectatorMovementSpeed * deltaTime;

		if (direction == Camera_Movement_State::FORWARD)
			spectator_camera_position += Front * velocity;

		if (direction == Camera_Movement_State::BACKWARD)
			spectator_camera_position -= Front * velocity;

		if (direction == Camera_Movement_State::LEFT)
			spectator_camera_position -= Right * velocity;

		if (direction == Camera_Movement_State::RIGHT)
			spectator_camera_position += Right * velocity;

		/*
		if (Engine::client->m_client.IsConnected())
		{
			MoveMessage* message = (MoveMessage*)Engine::client->m_client.CreateMessage((int)GameMessageType::MOVE);
			message->x = spectator_camera_position.x;
			message->y = spectator_camera_position.y;
			message->z = spectator_camera_position.z;

			Engine::client->m_client.SendMessage((int)GameChannel::UNRELIABLE, message);
		}
		*/

		return;
	}


	glm::vec3 newfront = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));

	/*if(!on_ground)
	{
		MovementSpeed *= 0.5F;
	}*/
	const float velocity = MovementSpeed * 10 * deltaTime;

	if (direction == Camera_Movement_State::JUMP && on_ground)
		playerRigidBody->applyCentralImpulse(btVector3(0.0f, 250.0F, 0.0f));


	//playerRigidBody->setLinearVelocity(v_new);

//	t.setOrigin(btVector3(currentPos.x, origin.getY(), currentPos.z));
	//playerRigidBody->setWorldTransform(t);

}

void SpacePlayerController::change_mode(bool save_pos) {
	if (is_spectator) {
		is_spectator = false;
		if (save_pos && playerRigidBody) {
			btTransform t;
			playerRigidBody->getMotionState()->getWorldTransform(t);
			t.setOrigin(btVector3(spectator_camera_position.x, spectator_camera_position.y, spectator_camera_position.z));
			playerRigidBody->setWorldTransform(t);
		}
	}
	else {
		if (save_pos) {
			btTransform t;
			playerRigidBody->getMotionState()->getWorldTransform(t);
			btVector3 origin = t.getOrigin();
			spectator_camera_position = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
		}
		is_spectator = true;
	}
}

void SpacePlayerController::UpdateVectors()
{

	const glm::vec3 tempPos = getPosition();
	const glm::vec3 pos = glm::vec3(tempPos.x, tempPos.z, tempPos.y);

	character_listener->SetLocation(tempPos.x, tempPos.y, tempPos.z);
	player.SetPosition(tempPos.x, tempPos.y, tempPos.z);

	if (is_spectator)
		return;



	const btVector3 from(pos.x, pos.z, pos.y);
	const btVector3 to(pos.x, pos.z - 0.50, pos.y);
	btCollisionWorld::AllHitsRayResultCallback res(from, to);
	//Physics::GetWorld()->getDebugDrawer()->drawLine(from, to, btVector4(0, 0, 0, 1));




	direction_velocity.setY(playerRigidBody->getLinearVelocity().getY());
	if (leftshift_pressed)
	{
		direction_velocity.setX(direction_velocity.getX() * 0.5F);
		direction_velocity.setZ(direction_velocity.getZ() * 0.5F);
	}
	if (leftctrl_pressed)
	{
		direction_velocity.setX(direction_velocity.getX() * 1.5F);
		direction_velocity.setZ(direction_velocity.getZ() * 1.5F);
	}
	playerRigidBody->setLinearVelocity(direction_velocity);

	if (on_ground)
	{
		mSpeedDamping = 0.1F;
		playerRigidBody->setFriction(0.5F);
	}
	else
	{
		playerRigidBody->setFriction(0.0F);
		mSpeedDamping = 0.5F;
	}

	direction_velocity.setX(direction_velocity.getX() * mSpeedDamping);
	direction_velocity.setZ(direction_velocity.getZ() * mSpeedDamping);
}
glm::mat4 SpacePlayerController::GetViewMatrix()
{
	const glm::quat reverseOrient = glm::conjugate(Rotation);
	const glm::mat4 rot = glm::mat4_cast(reverseOrient);

	const glm::mat4 translation = glm::translate(glm::mat4(1.0), -getPosition());
	return rot * translation;

}

void SpacePlayerController::InitSound() {
	if (!character_listener) {
		character_listener = SoundDevice::Get();
		character_listener->SetAttunation(AL_INVERSE_DISTANCE_CLAMPED);
		character_listener->SetLocation(0.f, 0.f, 0.f);
		character_listener->SetOrientation(0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
	}
	player.Init();
}
void SpacePlayerController::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{

	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw = glm::mod(Yaw + xoffset, 360.0f);
	Pitch += yoffset;

	if (constrainPitch)
	{
		Pitch = std::clamp(Pitch, -89.f, 89.f);
	}

	/*if (Engine::client->m_client.IsConnected())
	{
		RotateMessage* message = (RotateMessage*)Engine::client->m_client.CreateMessage((int)GameMessageType::ROTATE);
		message->pitch = Pitch;
		message->yaw = Yaw;

		Engine::client->m_client.SendMessage((int)GameChannel::UNRELIABLE, message);
	}*/

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();

	const glm::mat4 view = GetViewMatrix();
	character_listener->SetOrientation(view[2].x, view[2].y, -view[2].z, view[1].x, view[1].y, -view[1].z);
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void SpacePlayerController::ProcessMouseScroll(float yoffset)
{
	SpectatorMovementSpeed += (float)yoffset * 4;
	if (SpectatorMovementSpeed < 1.0f)
		SpectatorMovementSpeed = 1.0f;
}

glm::vec3 SpacePlayerController::getPosition() const
{
	if (is_spectator)
		return spectator_camera_position;

	const btVector3 origin = playerRigidBody->getWorldTransform().getOrigin();
	return glm::vec3(origin.getX(), origin.getY(), origin.getZ());
}
glm::quat SpacePlayerController::getRotation() const {
	return SpacePlayerController::Rotation;
}

void SpacePlayerController::SetRotation(glm::quat rotation) {
	SpacePlayerController::Rotation = rotation;
}