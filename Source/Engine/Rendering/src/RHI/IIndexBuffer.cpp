#include "SurvivantRendering/RHI/IIndexBuffer.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLIndexBuffer.h"

namespace SvRendering::RHI
{
    std::unique_ptr<IIndexBuffer> IIndexBuffer::Create(const uint32_t* p_indices, uint32_t p_count)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLIndexBuffer>(p_indices, p_count);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create index buffer - Unsupported graphics api");
            return {};
        }
    }

    std::unique_ptr<IIndexBuffer> IIndexBuffer::Create(const std::vector<uint32_t>& p_indices)
    {
        return Create(p_indices.data(), static_cast<uint32_t>(p_indices.size()));
    }
}
