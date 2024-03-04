#include "SurvivantRendering/RHI/IRenderAPI.h"

#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include <SurvivantCore/Debug/Assertion.h>

namespace SvRendering::RHI
{
    std::unique_ptr<IRenderAPI> IRenderAPI::s_instance{};

    IRenderAPI& IRenderAPI::SetCurrent(const EGraphicsAPI p_backend)
    {
        if (s_instance && p_backend == s_instance->GetBackend())
            return *s_instance;

        switch (p_backend)
        {
        case EGraphicsAPI::OPENGL:
            s_instance = std::make_unique<OpenGLAPI>();
            break;
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create render API - Unsupported backend");
            s_instance.reset();
        }

        return *s_instance;
    }
}
