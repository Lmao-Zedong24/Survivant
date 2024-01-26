#ifndef __LIBMATH__TRANSFORM_NOTIFIER_INL__
#define __LIBMATH__TRANSFORM_NOTIFIER_INL__

#include <ranges>

#include "Transform.h"
#include "TransformNotifier.h"

namespace LibMath
{
    inline TransformNotifier::ListenerId TransformNotifier::subscribe(const Action& action)
    {
        m_actions[m_currentId] = action;
        return m_currentId++;
    }

    inline void TransformNotifier::broadcast(const ENotificationType notificationType, Transform* newOwner)
    {
        if (!m_actions.empty())
            for (const auto& handler : m_actions | std::views::values)
                handler(notificationType, newOwner);
    }

    inline bool TransformNotifier::unsubscribe(const ListenerId& listener)
    {
        return m_actions.erase(listener) != 0;
    }
}

#endif // !__LIBMATH__TRANSFORM_NOTIFIER_INL__
