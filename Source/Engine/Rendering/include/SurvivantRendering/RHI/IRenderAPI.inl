#pragma once
#include "SurvivantRendering/RHI/IRenderAPI.h"

#include <SurvivantCore/Debug/Assertion.h>

namespace SvRendering::RHI
{
    inline IRenderAPI& IRenderAPI::getCurrent()
    {
        ASSERT(s_instance, "No loaded rendering API");
        return *s_instance;
    }
}