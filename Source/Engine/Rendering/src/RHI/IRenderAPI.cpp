#include "SurvivantRendering/RHI/IRenderAPI.h"

#include "SurvivantRendering/RHI/OpenGL/OpenGLAPI.h"

#include <SurvivantCore/Debug/Assertion.h>

namespace SvRendering::RHI
{
    std::unique_ptr<IRenderAPI> IRenderAPI::s_instance{};

    IRenderAPI& IRenderAPI::setCurrent(const EGraphicsAPI backend)
    {
        if (s_instance && backend == s_instance->GetBackend())
            return *s_instance;

        switch (backend)
        {
        case EGraphicsAPI::OPENGL:
            s_instance = std::make_unique<OpenGLAPI>();
            break;
        default:
            ASSERT(false, "Failed to create render API - Unsupported backend");
            s_instance.reset();
        }

        return *s_instance;
    }
}
