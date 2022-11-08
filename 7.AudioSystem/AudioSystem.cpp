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
    //初始化调试日志
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR,//只输出错误
        FMOD_DEBUG_MODE_TTY);//输出到stdout
    //创建FMOD studio system的对象
    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&mSystem);
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // 初始化 FMOD studio system
    result = mSystem->initialize(
        512, // 同时存在的最多声音数量
        FMOD_STUDIO_INIT_NORMAL, // 使用默认设置
        FMOD_INIT_NORMAL, // 使用默认设置
        nullptr 
    );
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // 取得并保存FMOD低阶系统指针
    mSystem->getLowLevelSystem(&mLowLevelSystem);


    // 加载默认bank
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
    // 防止重复加载
    if (mBanks.find(name) != mBanks.end())
    {
        return;
    }

    // 尝试加载bank库
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(
        name.c_str(), // 库的文件名
        FMOD_STUDIO_LOAD_BANK_NORMAL, // 正常加载
        &bank // 保存库指针
    );

    const int maxPathLength = 512;
    if (result == FMOD_OK)
    {
        // 添加bank到map中
        mBanks.emplace(name, bank);
        // 加载所有的非流式的案例数据
        bank->loadSampleData();
        // 获得bank中的event数量
        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if (numEvents > 0)
        {
            // 获得bank中的Event Description列表
            std::vector<FMOD::Studio::EventDescription*> events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            char eventName[maxPathLength];
            for (int i = 0; i < numEvents; i++)
            {
                FMOD::Studio::EventDescription* e = events[i];
                // 得到事件路径
                e->getPath(eventName, maxPathLength, nullptr);
                // 添加到事件map
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

    // 首先移除bank中的所有事件
    FMOD::Studio::Bank* bank = iter->second;
    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0)
    {
        // 获得bank中的event description
        std::vector<FMOD::Studio::EventDescription*> events(numEvents);
        // Get list of events
        bank->getEventList(events.data(), numEvents, &numEvents);
        char eventName[512];
        for (int i = 0; i < numEvents; i++)
        {
            FMOD::Studio::EventDescription* e = events[i];
            // 获得事件路径
            e->getPath(eventName, 512, nullptr);
            // 移除事件
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
        // 卸载案例数据，然后是bank本身
        iter.second->unloadSampleData();
        iter.second->unload();
    }
    mBanks.clear();
    // 没有banks意味着没有events
    mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
    unsigned int retID = 0;
    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        // 创建event实例
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
    // 寻找所有停止的event实例
    std::vector<unsigned int> done;
    for (auto& iter : mEventInstances)
    {
        FMOD::Studio::EventInstance* e = iter.second;
        // 获得event实例的状态
        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
        {
            // Release the event and add id to done
            e->release();
            done.emplace_back(iter.first);
        }
    }

    // 从map中移除实例
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

