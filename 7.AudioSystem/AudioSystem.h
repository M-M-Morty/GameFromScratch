#pragma once

#include <vector>
#include <unordered_map>

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

protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
};