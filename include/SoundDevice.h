#pragma once
#include <stdexcept>
#include <AL/alc.h>
#include <AL/al.h>
#include <vector>

#include "Export.h"

/// <summary>
/// Singleton-�����, ������� �������������� OpenAL ���������� � ��������� ����������.
/// </summary>
class SoundDevice
{
public:
	// ������ ������� ����� (�������� singleton-�)
	ENGINE_API static void Init();
	// ��������� �������� ���������� (����� Init)
	ENGINE_API static SoundDevice* Get();
	// ������������ �������� (�������� ��� �������� ������/����)
	ENGINE_API static void Shutdown();

	ENGINE_API void GetLocation(float& x, float& y, float& z);
	ENGINE_API void GetOrientation(float* ori6); // ������ �� 6 float: {atx, aty, atz, upx, upy, upz}
	ENGINE_API float GetGain();

	ENGINE_API void SetAttunation(int key);
	ENGINE_API void SetLocation(float x, float y, float z);
	ENGINE_API void SetOrientation(
		float atx, float aty, float atz,
		float upx, float upy, float upz);
	ENGINE_API void SetGain(float val);

private:
	SoundDevice();
	~SoundDevice();

	static SoundDevice* _instance;

	ALCdevice* p_ALCDevice = nullptr;
	ALCcontext* p_ALCContext = nullptr;
};
