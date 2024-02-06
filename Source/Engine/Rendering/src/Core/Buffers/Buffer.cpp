#include "SurvivantRendering/Core/Buffers/Buffer.h"

#include <glad/gl.h>

namespace SvRendering::Core::Buffers
{
	Buffer::Buffer(Buffer&& p_other) noexcept
		: m_bufferIndex(p_other.m_bufferIndex)
	{
		p_other.m_bufferIndex = 0;
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_bufferIndex);
	}

	Buffer& Buffer::operator=(Buffer&& p_other) noexcept
	{
		if (&p_other == this)
			return *this;

		glDeleteBuffers(1, &m_bufferIndex);

		m_bufferIndex = p_other.m_bufferIndex;

		p_other.m_bufferIndex = 0;

		return *this;
	}
}
