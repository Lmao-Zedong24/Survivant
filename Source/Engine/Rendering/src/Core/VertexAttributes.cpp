#include "SurvivantRendering/Core/VertexAttributes.h"

#include <glad/gl.h>

#include <Vector/Vector3.h>

using namespace LibMath;

namespace SvRendering::Core
{
    VertexAttributes::VertexAttributes(const Buffers::VertexBuffer& p_vbo, const Buffers::IndexBuffer& p_ebo)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        p_vbo.Bind();
        p_ebo.Bind();

        constexpr auto stride = sizeof(Vertex);

        // position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);

        // normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(sizeof(Vector3)));

        // texture coordinates attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(2 * sizeof(Vector3)));
    }

    VertexAttributes::VertexAttributes(VertexAttributes&& p_other) noexcept
        : m_vao(p_other.m_vao)
    {
        p_other.m_vao = 0;
    }

    VertexAttributes::~VertexAttributes()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    VertexAttributes& VertexAttributes::operator=(
        VertexAttributes&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteVertexArrays(1, &m_vao);

        m_vao = p_other.m_vao;

        p_other.m_vao = 0;

        return *this;
    }

    void VertexAttributes::Bind() const
    {
        glBindVertexArray(m_vao);
    }

    void VertexAttributes::Unbind()
    {
        glBindVertexArray(0);
    }
}
