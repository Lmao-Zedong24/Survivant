#include "SurvivantRendering/RHI/OpenGL/OpenGLVertexArray.h"

#include <glad/gl.h>

using namespace LibMath;
using namespace SvRendering::Geometry;

namespace SvRendering::RHI
{
    OpenGLVertexArray::OpenGLVertexArray(const IVertexBuffer& p_vbo, const IIndexBuffer& p_ebo)
    {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);

        p_vbo.Bind();
        p_ebo.Bind();

        constexpr auto stride = sizeof(Vertex);

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

    OpenGLVertexArray::OpenGLVertexArray(OpenGLVertexArray&& p_other) noexcept
        : IVertexArray(std::forward<IVertexArray&&>(p_other)), m_id(p_other.m_id)
    {
        p_other.m_id = 0;
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    OpenGLVertexArray& OpenGLVertexArray::operator=(OpenGLVertexArray&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        glDeleteVertexArrays(1, &m_id);

        m_id       = p_other.m_id;
        p_other.m_id = 0;

        IVertexArray::operator=(std::move(p_other));

        return *this;
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_id);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
