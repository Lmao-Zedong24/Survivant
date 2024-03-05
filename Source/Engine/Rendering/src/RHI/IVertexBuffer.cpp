#include "SurvivantRendering/RHI/IVertexBuffer.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLVertexBuffer.h"

using namespace SvRendering::Geometry;

namespace SvRendering::RHI
{
    std::unique_ptr<IVertexBuffer> IVertexBuffer::Create(const Vertex* p_vertices, const uint32_t p_count)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLVertexBuffer>(p_vertices, p_count);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create vertex buffer - Unsupported graphics api");
            return {};
        }
    }

    std::unique_ptr<IVertexBuffer> IVertexBuffer::Create(const std::vector<Vertex>& p_vertices)
    {
        return Create(p_vertices.data(), static_cast<uint32_t>(p_vertices.size()));
    }
}
