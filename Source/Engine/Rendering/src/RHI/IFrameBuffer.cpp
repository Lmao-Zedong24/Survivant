#include "SurvivantRendering/RHI/IFrameBuffer.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLFrameBuffer.h"

namespace SvRendering::RHI
{
    std::unique_ptr<IFrameBuffer> IFrameBuffer::Create()
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLFrameBuffer>();
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create frame buffer - Unsupported graphics api");
            return {};
        }
    }
}
