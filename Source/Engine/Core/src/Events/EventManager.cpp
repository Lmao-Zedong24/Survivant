//EventMaanger.cpp

#include "SurvivantCore/Events/EventManager.h"

using namespace Core;

EventManager& Core::EventManager::GetInstance()
{
    static EventManager s_instance;

    return s_instance;
}
