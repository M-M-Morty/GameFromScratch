#pragma once

#include <vector>
#include <unordered_map>

#include "Math.h"

namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};

class AudioSystem
{
private:
	// 追踪下一个event实例
	static unsigned int sNextID;

	class Game* mGame;

	// 记录已经加载的库
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	// Event的名字到对应EventDescription的映射
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	// Event的ID（引用）到event实例的映射
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
	// 总线（一组相同类型的声音）映射
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
	//FMOD Studios系统
	FMOD::Studio::System* mSystem;
	//FMOD低阶系统
	FMOD::System* mLowLevelSystem;

public:
	AudioSystem(class Game* game);
	~AudioSystem();

	bool Initialize();
	void Shutdown();

	// 加载/卸载 banks
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	class SoundEvent PlayEvent(const std::string& name);

	void Update(float deltaTime);
	
	void SetListener(const Matrix4& viewMatrix);
	// 控制总线
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
};