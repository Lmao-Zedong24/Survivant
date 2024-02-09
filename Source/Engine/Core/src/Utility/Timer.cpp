#include "SurvivantCore/Utility/Timer.h"

#include <chrono>

namespace SvCore::Utility
{
    Timer::Timer(const float timeScale)
        : m_timeScale(timeScale)
    {
    }

    void Timer::tick()
    {
        if (m_isFirstUpdate)
        {
            m_currentTime = clock::now();
            m_lastUpdate  = m_currentTime;
            m_deltaTime   = 0;

            m_isFirstUpdate = false;
        }
        else
        {
            m_lastUpdate  = m_currentTime;
            m_currentTime = clock::now();
            m_deltaTime   = std::chrono::duration<float>(m_currentTime - m_lastUpdate).count();
            m_unscaledTime += m_deltaTime;
            m_time += m_deltaTime * m_timeScale;
        }

        m_frameCount++;
    }

    float Timer::getTime() const
    {
        return m_time;
    }

    float Timer::getDeltaTime() const
    {
        return m_deltaTime * m_timeScale;
    }

    float Timer::getUnscaledTime() const
    {
        return m_unscaledTime;
    }

    float Timer::getUnscaledDeltaTime() const
    {
        return m_deltaTime;
    }

    float Timer::getTimeScale() const
    {
        return m_timeScale;
    }

    void Timer::setTimeScale(const float timeScale)
    {
        m_timeScale = timeScale;
    }

    uint64_t Timer::getFrameCount() const
    {
        return m_frameCount;
    }
}
