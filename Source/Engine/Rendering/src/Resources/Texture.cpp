#include "SurvivantRendering/Resources/texture.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace SvRendering::Enums;

namespace SvRendering::Resources
{
    GLint ToGLInt(const ETextureFilter p_filter)
    {
        switch (p_filter)
        {
        case ETextureFilter::NEAREST:
            return GL_NEAREST;
        case ETextureFilter::LINEAR:
            return GL_LINEAR;
        case ETextureFilter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case ETextureFilter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case ETextureFilter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case ETextureFilter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            ASSERT(false, "Invalid texture filter");
            return GL_INVALID_ENUM;
        }
    }

    GLint ToGLInt(const ETextureWrapMode p_wrapMode)
    {
        switch (p_wrapMode)
        {
        case ETextureWrapMode::REPEAT:
            return GL_REPEAT;
        case ETextureWrapMode::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case ETextureWrapMode::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case ETextureWrapMode::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        default:
            ASSERT(false, "Invalid wrap mode");
            return GL_INVALID_ENUM;
        }
    }

    GLenum GetGLFormat(const uint8_t p_channels)
    {
        switch (p_channels)
        {
        case 1:
            return GL_RED;
        case 2:
            return GL_RG;
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            ASSERT(false, "Invalid channels count. Expected 1-4 but received \"%d\".", p_channels);
            return GL_INVALID_ENUM;
        }
    }

    Texture::Texture(const Texture& p_other)
        : IResource(p_other)
    {
        Copy(p_other);
    }

    Texture::Texture(Texture&& p_other) noexcept
        : IResource(std::forward<IResource&&>(p_other)), m_id(p_other.m_id), m_pixels(p_other.m_pixels), m_width(p_other.m_width),
        m_height(p_other.m_height), m_channels(p_other.m_channels)
    {
        p_other.m_id     = 0;
        p_other.m_pixels = nullptr;
    }

    Texture::~Texture()
    {
        stbi_image_free(m_pixels);
        m_pixels = nullptr;
    }

    Texture& Texture::operator=(const Texture& p_other)
    {
        if (this == &p_other)
            return *this;

        if (m_id != 0)
            glDeleteTextures(1, &m_id);

        if (m_pixels != nullptr)
            stbi_image_free(m_pixels);

        Copy(p_other);

        return *this;
    }

    Texture& Texture::operator=(Texture&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        if (m_id != 0)
            glDeleteTextures(1, &m_id);

        if (m_pixels != nullptr)
            stbi_image_free(m_pixels);

        m_id       = p_other.m_id;
        m_width    = p_other.m_width;
        m_height   = p_other.m_height;
        m_channels = p_other.m_channels;
        m_pixels   = p_other.m_pixels;

        m_minFilter = p_other.m_minFilter;
        m_magFilter = p_other.m_magFilter;
        m_wrapModeS = p_other.m_wrapModeS;
        m_wrapModeT = p_other.m_wrapModeT;

        p_other.m_id     = 0;
        p_other.m_pixels = nullptr;

        return *this;
    }

    bool Texture::Load(const std::string& p_path)
    {
        stbi_set_flip_vertically_on_load(true);

        int channels;
        m_pixels = stbi_load(p_path.c_str(), &m_width, &m_height, &channels, 0);

        m_channels = static_cast<uint8_t>(channels);

        if (!m_pixels)
        {
            SV_LOG_ERROR("Failed to load texture: ");
            return false;
        }

        return true;
    }

    bool Texture::Init()
    {
        if (!CHECK(m_pixels != nullptr, "Unable to initialize opengl texture - no pixels"))
            return false;

        if (m_id == 0)
        {
            glGenTextures(1, &m_id);

            if (!CHECK(m_id != 0, "Unable to generate opengl texture id."))
                return false;
        }

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GetGLFormat(m_channels), GL_UNSIGNED_BYTE, m_pixels);

        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }

    void Texture::Bind(const uint8_t p_slot) const
    {
        glBindTextureUnit(p_slot, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLInt(m_wrapModeS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLInt(m_wrapModeT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ToGLInt(m_minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ToGLInt(m_magFilter));
    }

    void Texture::Unbind(const uint8_t p_slot) const
    {
        glBindTextureUnit(p_slot, 0);
    }

    void Texture::GenerateMipmap()
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    LibMath::Vector2I Texture::GetSize() const
    {
        return { m_width, m_height };
    }

    uint8_t Texture::GetChannelCount() const
    {
        return m_channels;
    }

    void Texture::SetFilters(const ETextureFilter p_minFilter, const ETextureFilter p_magFilter)
    {
        m_minFilter = p_minFilter;
        m_magFilter = p_magFilter;
    }

    void Texture::SetWrapModes(const ETextureWrapMode p_wrapModeS, const ETextureWrapMode p_wrapModeT)
    {
        m_wrapModeS = p_wrapModeS;
        m_wrapModeT = p_wrapModeT;
    }

    void Texture::Copy(const Texture& p_other)
    {
        m_id       = 0;
        m_width    = p_other.m_width;
        m_height   = p_other.m_height;
        m_channels = p_other.m_channels;

        m_minFilter = p_other.m_minFilter;
        m_magFilter = p_other.m_magFilter;
        m_wrapModeS = p_other.m_wrapModeS;
        m_wrapModeT = p_other.m_wrapModeT;

        if (p_other.m_pixels == nullptr)
        {
            m_pixels = nullptr;
            return;
        }

        m_pixels = stbi_load_from_memory(p_other.m_pixels, p_other.m_width * p_other.m_height * p_other.m_channels, &m_width,
            &m_height, reinterpret_cast<int*>(&m_channels), 0);

        if (p_other.m_id == 0)
            return;

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GetGLFormat(m_channels), GL_FLOAT, nullptr);

        glCopyImageSubData(p_other.m_id, GL_TEXTURE_2D, 0, 0, 0, 0,
            m_id, GL_TEXTURE_2D, 0, 0, 0, 0,
            m_width, m_height, 1
        );
    }
}
