#include "SurvivantRendering/RHI/ITexture.h"

#include "SurvivantRendering/RHI/IRenderAPI.h"
#include "SurvivantRendering/RHI/OpenGL/OpenGLTexture.h"

#include <SurvivantCore/Debug/Assertion.h>
#include <SurvivantCore/Debug/Logger.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x) ASSERT(x)
#include <stb_image.h>

using namespace SvCore::Utility;
using namespace SvRendering::Enums;
using namespace SvRendering::RHI;

namespace SvRendering::RHI
{
    ITexture::ITexture(const int p_width, const int p_height, const EPixelDataFormat p_format)
        : m_width(p_width), m_height(p_height), m_channels(ToChannelCount(p_format))
    {
    }

    ITexture::ITexture(const ITexture& p_other)
        : IResource(p_other), m_width(p_other.m_width), m_height(p_other.m_height), m_channels(p_other.m_channels)
    {
        if (p_other.m_data == nullptr)
        {
            m_data = nullptr;
            return;
        }

        m_data = stbi_load_from_memory(p_other.m_data, p_other.m_width * p_other.m_height * p_other.m_channels, &m_width, &m_height,
            reinterpret_cast<int*>(&m_channels), 0);
    }

    ITexture::ITexture(ITexture&& p_other) noexcept
        : IResource(std::forward<IResource&&>(p_other)), m_data(p_other.m_data), m_width(p_other.m_width),
        m_height(p_other.m_height),
        m_channels(p_other.m_channels)
    {
        p_other.m_data = nullptr;
    }

    ITexture::~ITexture()
    {
        if (m_data != nullptr)
            stbi_image_free(m_data);
    }

    ITexture& ITexture::operator=(const ITexture& p_other)
    {
        if (&p_other == this)
            return *this;

        m_width    = p_other.m_width;
        m_height   = p_other.m_height;
        m_channels = p_other.m_channels;

        if (m_data != nullptr)
            stbi_image_free(m_data);

        if (p_other.m_data == nullptr)
        {
            m_data = nullptr;
            return *this;
        }

        m_data = stbi_load_from_memory(p_other.m_data, p_other.m_width * p_other.m_height * p_other.m_channels, &m_width, &m_height,
            reinterpret_cast<int*>(&m_channels), 0);

        return *this;
    }

    ITexture& ITexture::operator=(ITexture&& p_other) noexcept
    {
        if (&p_other == this)
            return *this;

        if (m_data != nullptr)
            stbi_image_free(m_data);

        m_width    = p_other.m_width;
        m_height   = p_other.m_height;
        m_channels = p_other.m_channels;
        m_data     = p_other.m_data;

        m_minFilter = p_other.m_minFilter;
        m_magFilter = p_other.m_magFilter;
        m_wrapModeU = p_other.m_wrapModeU;
        m_wrapModeV = p_other.m_wrapModeV;

        p_other.m_data = nullptr;

        return *this;
    }

    ITexture& ITexture::GetDefault()
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return OpenGLTexture::GetDefault();
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Unsupported render api");
            static OpenGLTexture unreachable;
            return unreachable;
        }
    }

    bool ITexture::Load(const std::string& p_path)
    {
        if (m_data != nullptr)
            stbi_image_free(m_data);

        stbi_set_flip_vertically_on_load(true);
        m_data = stbi_load(p_path.c_str(), &m_width, &m_height, reinterpret_cast<int*>(&m_channels), 0);

        if (m_data == nullptr)
        {
            SV_LOG_ERROR("Unable to load texture from path \"%s\"", p_path.c_str());
            return false;
        }

        return true;
    }

    LibMath::Vector2I ITexture::GetSize() const
    {
        return { m_width, m_height };
    }

    uint8_t ITexture::GetChannelCount() const
    {
        return m_channels;
    }

    void ITexture::SetFilters(const ETextureFilter p_minFilter, const ETextureFilter p_magFilter)
    {
        m_minFilter = p_minFilter;
        m_magFilter = p_magFilter;
    }

    void ITexture::SetWrapModes(const ETextureWrapMode p_wrapModeU, const ETextureWrapMode p_wrapModeV)
    {
        m_wrapModeU = p_wrapModeU;
        m_wrapModeV = p_wrapModeV;
    }

    uint8_t ITexture::ToChannelCount(const EPixelDataFormat p_format)
    {
        switch (p_format)
        {
        case EPixelDataFormat::RED:
        case EPixelDataFormat::GREEN:
        case EPixelDataFormat::BLUE:
        case EPixelDataFormat::ALPHA:
        case EPixelDataFormat::STENCIL_INDEX:
        case EPixelDataFormat::DEPTH_COMPONENT:
            return 1;
        case EPixelDataFormat::RG:
        case EPixelDataFormat::DEPTH_STENCIL:
            return 2;
        case EPixelDataFormat::RGB:
        case EPixelDataFormat::BGR:
            return 3;
        case EPixelDataFormat::RGBA:
        case EPixelDataFormat::BGRA:
            return 4;
        default:
            return 0;
        }
    }

    std::shared_ptr<ITexture> ITexture::Create()
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_shared<OpenGLTexture>();
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create texture - Unsupported graphics api");
            return {};
        }
    }

    std::shared_ptr<ITexture> ITexture::Create(const int p_width, const int p_height, const EPixelDataFormat p_format)
    {
        switch (IRenderAPI::GetCurrent().GetBackend())
        {
        case EGraphicsAPI::OPENGL:
            return std::make_shared<OpenGLTexture>(p_width, p_height, p_format);
        case EGraphicsAPI::NONE:
        default:
            ASSERT(false, "Failed to create texture - Unsupported graphics api");
            return {};
        }
    }
}
