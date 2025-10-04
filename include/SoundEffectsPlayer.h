#pragma once
#include <array>
#include <string>
#include <AL\al.h>
#include <glm/vec3.hpp>

#include "Export.h"

class SoundEffectsPlayer
{
public:
	ENGINE_API explicit SoundEffectsPlayer(const std::string& name);

	ENGINE_API ~SoundEffectsPlayer();

	ENGINE_API void Play(const ALuint& buffer_to_play);
	ENGINE_API void Init();


	ENGINE_API void Stop();
	ENGINE_API void Pause();
	ENGINE_API void Resume();
	ENGINE_API void Remove();

	ENGINE_API void SetBufferToPlay(const ALuint& buffer_to_play);
	ENGINE_API void SetLooping(const bool& loop);
	ENGINE_API void SetPosition(const float& x, const float& y, const float& z);
	ENGINE_API glm::vec3 GetPosition();
	ENGINE_API void SetDirection(const float& x, const float& y, const float& z);

	ENGINE_API bool isPlaying();

	std::string tag;
	ALuint last_sound;
	bool loop = false;
	bool is_linked_to_rigidbody = false; //TODO ��������

private:

	ALuint p_Source = 0;
	ALuint p_Buffer = 0;


};
