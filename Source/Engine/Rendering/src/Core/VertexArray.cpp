#include "SurvivantRendering/Core/VertexArray.h"

#include <glad/gl.h>

#include <Vector/Vector3.h>

using namespace LibMath;
using namespace SvRendering::Core::Buffers;
using namespace SvRendering::Geometry;

namespace SvRendering::Core
{
    VertexArray::VertexArray(const VertexBuffer& p_vbo, const IndexBuffer& p_ebo)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        p_vbo.Bind();
        p_ebo.Bind();

        constexpr GLsizei stride = sizeof(Vertex);

        // position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, m_position)));

        // normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, m_normal)));

        // texture coordinates attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, m_textureUV)));

        // tangent attribute
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, m_tangent)));

        // bitangent attribute
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, m_bitangent)));

        Unbind();
    }

    VertexArray::VertexArray(VertexArray&& p_other) noexcept
        : m_vao(p_other.m_vao)
    {
        p_other.m_vao = 0;
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    VertexArray& VertexArray::operator=(VertexArray&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteVertexArrays(1, &m_vao);

        m_vao = p_other.m_vao;

        p_other.m_vao = 0;

        return *this;
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_vao);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
