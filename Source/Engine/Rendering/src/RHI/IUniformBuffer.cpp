#include "SurvivantRendering/RHI/IUniformBuffer.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLUniformBuffer.h"

using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    IUniformBuffer::IUniformBuffer(IUniformBuffer&& p_other) noexcept
        : m_bindIndex(p_other.m_bindIndex), m_accessMode(p_other.m_accessMode)
    {
    }

    IUniformBuffer& IUniformBuffer::operator=(IUniformBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        m_bindIndex  = p_other.m_bindIndex;
        m_accessMode = p_other.m_accessMode;

        p_other.m_bindIndex = 0;

        return *this;
    }

    void IUniformBuffer::SetBindIndex(const uint32_t p_bindIndex)
    {
        m_bindIndex = p_bindIndex;
    }

    void IUniformBuffer::Bind(const uint32_t p_index)
    {
        Unbind();
        SetBindIndex(p_index);
        Bind();
    }

    std::unique_ptr<IUniformBuffer> IUniformBuffer::Create(const EAccessMode p_accessMode, const uint32_t p_bindIndex)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLUniformBuffer>(p_accessMode, p_bindIndex);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create uniform buffer - Unsupported graphics api");
            return {};
        }
    }

    IUniformBuffer::IUniformBuffer(const EAccessMode p_accessMode, const uint32_t p_bindIndex)
        : m_bindIndex(p_bindIndex), m_accessMode(p_accessMode)
    {
    }
}
