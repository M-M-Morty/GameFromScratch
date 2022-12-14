#pragma once

#include <string>

class SoundEvent
{
public:
	SoundEvent();
	// 如果对应的event存在就返回真
	bool IsValid();
	// 重启
	void Restart();
	//停止event
	void Stop(bool allowFadeOut = true);
	// Setters
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	// Getters
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	//
	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem* mSystem;
	unsigned int mID;
};