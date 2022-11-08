#include "AudioSystem.h"
#include <SDL/SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>
#include "SoundEvent.h"

unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
    :mGame(game)
    ,mSystem(nullptr)
    ,mLowLevelSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
    //��ʼ��������־
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR,//ֻ�������
        FMOD_DEBUG_MODE_TTY);//�����stdout
    //����FMOD studio system�Ķ���
    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&mSystem);
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // ��ʼ�� FMOD studio system
    result = mSystem->initialize(
        512, // ͬʱ���ڵ������������
        FMOD_STUDIO_INIT_NORMAL, // ʹ��Ĭ������
        FMOD_INIT_NORMAL, // ʹ��Ĭ������
        nullptr 
    );
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // ȡ�ò�����FMOD�ͽ�ϵͳָ��
    mSystem->getLowLevelSystem(&mLowLevelSystem);


    // ����Ĭ��bank
    LoadBank("Assets/Master Bank.strings.bank");
    LoadBank("Assets/Master Bank.bank");

    return true;
}

void AudioSystem::Shutdown()
{
    mSystem->release();
}

void AudioSystem::LoadBank(const std::string& name)
{
    // ��ֹ�ظ�����
    if (mBanks.find(name) != mBanks.end())
    {
        return;
    }

    // ���Լ���bank��
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(
        name.c_str(), // ����ļ���
        FMOD_STUDIO_LOAD_BANK_NORMAL, // ��������
        &bank // �����ָ��
    );

    const int maxPathLength = 512;
    if (result == FMOD_OK)
    {
        // ���bank��map��
        mBanks.emplace(name, bank);
        // �������еķ���ʽ�İ�������
        bank->loadSampleData();
        // ���bank�е�event����
        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if (numEvents > 0)
        {
            // ���bank�е�Event Description�б�
            std::vector<FMOD::Studio::EventDescription*> events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            char eventName[maxPathLength];
            for (int i = 0; i < numEvents; i++)
            {
                FMOD::Studio::EventDescription* e = events[i];
                // �õ��¼�·��
                e->getPath(eventName, maxPathLength, nullptr);
                // ��ӵ��¼�map
                mEvents.emplace(eventName, e);
            }
        }
    }
}

void AudioSystem::UnloadBank(const std::string& name)
{
    auto iter = mBanks.find(name);
    if (iter == mBanks.end())
    {
        return;
    }

    // �����Ƴ�bank�е������¼�
    FMOD::Studio::Bank* bank = iter->second;
    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0)
    {
        // ���bank�е�event description
        std::vector<FMOD::Studio::EventDescription*> events(numEvents);
        // Get list of events
        bank->getEventList(events.data(), numEvents, &numEvents);
        char eventName[512];
        for (int i = 0; i < numEvents; i++)
        {
            FMOD::Studio::EventDescription* e = events[i];
            // ����¼�·��
            e->getPath(eventName, 512, nullptr);
            // �Ƴ��¼�
            auto eventi = mEvents.find(eventName);
            if (eventi != mEvents.end())
            {
                mEvents.erase(eventi);
            }
        }
    }
}

void AudioSystem::UnloadAllBanks()
{
    for (auto& iter : mBanks)
    {
        // ж�ذ������ݣ�Ȼ����bank����
        iter.second->unloadSampleData();
        iter.second->unload();
    }
    mBanks.clear();
    // û��banks��ζ��û��events
    mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
    unsigned int retID = 0;
    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        // ����eventʵ��
        FMOD::Studio::EventInstance* event = nullptr;
        iter->second->createInstance(&event);
        if (event)
        {
            // Start the event instance
            event->start();
            // Get the next id, and add to map
            
            sNextID++;
            retID = sNextID;
            mEventInstances.emplace(retID, event);
        }
    }
    return SoundEvent(this, retID);
}


void AudioSystem::Update(float deltaTime)
{
    // Ѱ������ֹͣ��eventʵ��
    std::vector<unsigned int> done;
    for (auto& iter : mEventInstances)
    {
        FMOD::Studio::EventInstance* e = iter.second;
        // ���eventʵ����״̬
        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
        {
            // Release the event and add id to done
            e->release();
            done.emplace_back(iter.first);
        }
    }

    // ��map���Ƴ�ʵ��
    for (auto id : done)
    {
        mEventInstances.erase(id);
    }

    // Update FMOD
    mSystem->update();
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
    FMOD::Studio::EventInstance* event = nullptr;
    auto iter = mEventInstances.find(id);
    if (iter != mEventInstances.end())
    {
        event = iter->second;
    }
    return event;
}

