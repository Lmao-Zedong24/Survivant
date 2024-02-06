#include "SurvivantRendering/Core/Buffers/IndexBuffer.h"

#include <glad/gl.h>

namespace SvRendering::Core::Buffers
{
    IndexBuffer::IndexBuffer(const uint32_t* p_indices, const intptr_t p_indexCount)
    {
        glGenBuffers(1, &m_bufferIndex);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndex);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indexCount * static_cast<GLsizeiptr>(sizeof(uint32_t)),
                     p_indices, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(const std::vector<uint32_t>& p_indices) :
        IndexBuffer(p_indices.data(), static_cast<intptr_t>(p_indices.size()))
    {
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndex);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
