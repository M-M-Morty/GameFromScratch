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
	// ׷����һ��eventʵ��
	static unsigned int sNextID;

	class Game* mGame;

	// ��¼�Ѿ����صĿ�
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	// Event�����ֵ���ӦEventDescription��ӳ��
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	// Event��ID�����ã���eventʵ����ӳ��
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;

	//FMOD Studiosϵͳ
	FMOD::Studio::System* mSystem;
	//FMOD�ͽ�ϵͳ
	FMOD::System* mLowLevelSystem;

public:
	AudioSystem(class Game* game);
	~AudioSystem();

	bool Initialize();
	void Shutdown();

	// ����/ж�� banks
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	class SoundEvent PlayEvent(const std::string& name);


	void Update(float deltaTime);

protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
};