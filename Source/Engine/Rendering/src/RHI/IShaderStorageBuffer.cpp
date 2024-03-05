#include "SurvivantRendering/RHI/IShaderStorageBuffer.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLShaderStorageBuffer.h"

using namespace SvRendering::Enums;

namespace SvRendering::RHI
{
    IShaderStorageBuffer::IShaderStorageBuffer(IShaderStorageBuffer&& p_other) noexcept
        : m_bindIndex(p_other.m_bindIndex), m_accessMode(p_other.m_accessMode)
    {
        p_other.m_bindIndex = 0;
    }

    IShaderStorageBuffer& IShaderStorageBuffer::operator=(IShaderStorageBuffer&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        m_bindIndex  = p_other.m_bindIndex;
        m_accessMode = p_other.m_accessMode;

        p_other.m_bindIndex = 0;

        return *this;
    }

    void IShaderStorageBuffer::SetBindIndex(const uint32_t p_bindIndex)
    {
        m_bindIndex = p_bindIndex;
    }

    void IShaderStorageBuffer::Bind(const uint32_t p_index)
    {
        Unbind();
        SetBindIndex(p_index);
        Bind();
    }

    std::unique_ptr<IShaderStorageBuffer> IShaderStorageBuffer::Create(const EAccessMode p_accessMode, const uint32_t p_bindIndex)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_unique<OpenGLShaderStorageBuffer>(p_accessMode, p_bindIndex);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create shader storage buffer - Unsupported graphics api");
            return {};
        }
    }

    IShaderStorageBuffer::IShaderStorageBuffer(const EAccessMode accessMode, const uint32_t bindIndex)
        : m_bindIndex(bindIndex), m_accessMode(accessMode)
    {
    }
}
