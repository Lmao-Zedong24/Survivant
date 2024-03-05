#include "SurvivantRendering/RHI/IVertexArray.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLVertexArray.h"

namespace SvRendering::RHI
{
    std::unique_ptr<IVertexArray> IVertexArray::Create(const IVertexBuffer& p_vbo, const IIndexBuffer& p_ebo)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLVertexArray>(p_vbo, p_ebo);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create vertex array - Unsupported graphics api");
            return {};
        }
    }
}
