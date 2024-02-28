#pragma once
#include "SurvivantCore/Resources/IResource.h"

#include "SurvivantRendering/Enums/ETextureFilter.h"
#include "SurvivantRendering/Enums/ETextureWrapMode.h"

#include "Vector/Vector2.h"

#include <string>

namespace SvRendering::Resources
{
    class Texture final : public SvCore::Resources::IResource
    {
    public:
        /**
         * \brief Creates a default texture
         */
        Texture() = default;

        /**
         * \brief Creates a copy of the given texture
         * \param p_other The texture to copy
         */
        Texture(const Texture& p_other);

        /**
         * \brief Creates a move copy of the given texture
         * \param p_other The texture to move
         */
        Texture(Texture&& p_other) noexcept;

        /**
         * \brief Releases resources allocated for the texture
         */
        ~Texture() override;

        /**
         * \brief Assigns a copy of the given texture to this one
         * \param p_other The texture to copy
         * \return A reference to the modified texture
         */
        Texture& operator=(const Texture& p_other);

        /**
         * \brief Moves the given texture into this one
         * \param p_other The texture to move
         * \return A reference to the modified texture
         */
        Texture& operator=(Texture&& p_other) noexcept;

        /**
         * \brief Loads a texture from the given file
         * \param p_path The texture's file path
         * \return True if the texture was successfully loaded. False otherwise.
         */
        bool Load(const std::string& p_path) override;

        /**
         * \brief Initializes the texture
         * \return True if the texture was successfully initialized. False otherwise.
         */
        bool Init() override;

        /**
         * \brief Binds the texture to the given slot
         * \param p_slot The slot the texture should be bound to
         */
        void Bind(uint8_t p_slot) const;

        /**
         * \brief Unbinds the current texture from the given slot
         * \param p_slot The slot the texture is bound to
         */
        void Unbind(uint8_t p_slot) const;

        /**
         * \brief Generates the texture's mipmap
         */
        void GenerateMipmap();

        /**
         * \brief Gets the texture's id
         * \return The texture's id
         */
        uint32_t GetId() const;

        /**
         * \brief Gets the texture's dimensions
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
         * \param p_wrapModeS The texture's S (horizontal) wrapping mode
         * \param p_wrapModeT The texture's T (vertical) wrapping mode
         */
        void SetWrapModes(Enums::ETextureWrapMode p_wrapModeS, Enums::ETextureWrapMode p_wrapModeT);

    private:
        uint32_t                m_id        = 0;
        unsigned char*          m_pixels    = nullptr;
        int                     m_width     = 0;
        int                     m_height    = 0;
        uint8_t                 m_channels  = 0;
        Enums::ETextureFilter   m_minFilter = Enums::ETextureFilter::LINEAR;
        Enums::ETextureFilter   m_magFilter = Enums::ETextureFilter::LINEAR;
        Enums::ETextureWrapMode m_wrapModeS = Enums::ETextureWrapMode::REPEAT;
        Enums::ETextureWrapMode m_wrapModeT = Enums::ETextureWrapMode::REPEAT;

        void Copy(const Texture& p_other);
    };
}
