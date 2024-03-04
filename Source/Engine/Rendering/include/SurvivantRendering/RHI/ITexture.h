#pragma once
#include "SurvivantRendering/Enums/EPixelDataFormat.h"
#include "SurvivantRendering/Enums/ETextureFilter.h"
#include "SurvivantRendering/Enums/ETextureWrapMode.h"

#include <SurvivantCore/Resources/IResource.h>

#include <Vector/Vector2.h>

#include <string>

namespace SvRendering::RHI
{
    class ITexture : public SvCore::Resources::IResource
    {
    public:
        /**
         * \brief Creates a copy of the given texture
         * \param p_other The texture to copy
         */
        ITexture(const ITexture& p_other);

        /**
         * \brief Creates a move copy of the given texture
         * \param p_other The texture to move
         */
        ITexture(ITexture&& p_other) noexcept;

        /**
         * \brief Releases resources allocated for the texture
         */
        ~ITexture() override;

        /**
         * \brief Assigns a copy of the given texture to this one
         * \param p_other The texture to copy
         * \return A reference to the modified texture
         */
        ITexture& operator=(const ITexture& p_other);

        /**
         * \brief Moves the given texture into this one
         * \param p_other The texture to move
         * \return A reference to the modified texture
         */
        ITexture& operator=(ITexture&& p_other) noexcept;

        /**
         * \brief Gets or creates a white 1x1 texture
         * \return A reference to the default texture
         */
        static ITexture& GetDefault();

        /**
         * \brief Loads a texture from the given file
         * \param p_path The texture's file path
         * \return True if the texture was successfully loaded. False otherwise.
         */
        bool Load(const std::string& p_path) override;

        /**
         * \brief Binds the texture to the current context
         * \param slot The slot the texture should be bound to
         */
        virtual void Bind(uint8_t slot) = 0;

        /**
         * \brief Unbinds the current texture from the current context
         * \param slot The slot the texture is bound to
         */
        virtual void Unbind(uint8_t slot) = 0;

        /**
         * \brief Generates mipmaps for the texture
         */
        virtual void GenerateMipmap() = 0;

        /**
         * \brief Gets the textures dimensions
         * \return The texture's dimensions
         */
        LibMath::Vector2I GetSize() const;

        /**
         * \brief Gets the texture's number of channels
         * \return The texture's channel count
         */
        uint8_t GetChannelCount() const;

        /**
         * \brief Sets the texture's minification and magnification filters
         * \param p_minFilter The texture's minification filter
         * \param p_magFilter The texture's magnification filter
         */
        void SetFilters(Enums::ETextureFilter p_minFilter, Enums::ETextureFilter p_magFilter);

        /**
         * \brief Sets the texture's horizontal and vertical wrapping modes
         * \param p_wrapModeU The texture's S (horizontal) wrapping mode
         * \param p_wrapModeV The texture's T (vertical) wrapping mode
         */
        void SetWrapModes(Enums::ETextureWrapMode p_wrapModeU, Enums::ETextureWrapMode p_wrapModeV);

        /**
         * \brief Gets the number of channels in the given pixel data format
         * \param p_format The target pixel data format
         * \return The number of channels in the given format
         */
        static uint8_t ToChannelCount(Enums::EPixelDataFormat p_format);

        /**
         * \brief Creates a texture for the current render API
         */
        static std::shared_ptr<ITexture> Create();

        /**
         * \brief Creates a texture with the given width, height and pixel format
         * \param p_width The texture's width
         * \param p_height The texture's height
         * \param p_format The texture's pixel format
         */
        static std::shared_ptr<ITexture> Create(int p_width, int p_height, Enums::EPixelDataFormat p_format);

    protected:
        unsigned char*          m_data      = nullptr;
        int                     m_width     = 0;
        int                     m_height    = 0;
        uint8_t                 m_channels  = 0;
        Enums::ETextureFilter   m_minFilter = Enums::ETextureFilter::LINEAR;
        Enums::ETextureFilter   m_magFilter = Enums::ETextureFilter::LINEAR;
        Enums::ETextureWrapMode m_wrapModeU = Enums::ETextureWrapMode::REPEAT;
        Enums::ETextureWrapMode m_wrapModeV = Enums::ETextureWrapMode::REPEAT;

        /**
         * \brief Creates a default texture
         */
        ITexture() = default;

        /**
         * \brief Creates a texture with the given width, height and pixel format
         * \param p_width The texture's width
         * \param p_height The texture's height
         * \param p_format The texture's pixel format
         */
        ITexture(int p_width, int p_height, Enums::EPixelDataFormat p_format);
    };
}
