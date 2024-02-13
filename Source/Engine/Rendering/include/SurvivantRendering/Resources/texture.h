#pragma once
#include <string>
#include <vector>
#include "TextureMinfilter.h"
#include "TextureWrapMode.h"

//Texture class should heritate from IRessource class

class Texture 
{
public:

	/**
	 * @brief Default constructor
	 */
	Texture();

	/**
 * @brief Release any allocated resources in the destructor
 */
	~Texture();

	/**
 * @brief Copy constructor
 * @param other The Texture object to copy
 */
	Texture(const Texture& other);

	/**
 * @brief Load the image data texture from a file and set up the texture
 * @param path The path to the image file
 * @return True if loading and initialization succeed, false otherwise
 */
	bool									Load(const std::string& path);

	/**
 * @brief Load the image data texture from a file and set up the texture
 * @return True if initialization succeed, false otherwise
 */
	bool									Init();

	/**
 * @brief Bind the texture before rendering to use it
 */
	void									Bind() const;

	/**
 * @brief Unbind the texture after rendering is done
 */
	void									Unbind() const;

	/**
 * @brief Set textures parameters, filtering and Wrapping
 * @param p_minFilter The filtering method for minification
 * @param p_magFilter The filtering method for magnification
 */
	void									SetFiltering(ETextureFilter p_minFilter, ETextureFilter p_magFilter);

	/**
 * @brief Set texture wrapping mode
 * @param p_wrapS The wrapping mode for the S (horizontal) texture coordinate
 * @param p_wrapT The wrapping mode for the T (vertical) texture coordinate
 */
	void									SetWrapping(ETextureWrapMode p_wrapS, ETextureWrapMode p_wrapT);

	/**
 * @brief Generate mipmaps for the texture for better rendering quality
 */
	void									GenerateMipmaps();

	/**
 * @brief Get width of the texture
 * @return The width of the texture in pixels
 */
	int										GetWidth() const;

	/**
 * @brief Get height of the texture
 * @return The height of the texture in pixels
 */
	int										GetHeight() const;

	/**
 * @brief Get the number of channels of the texture
 * @return The number of channels (e.g., 3 for RGB)
 */
	uint32_t								GetNumberOfChannels() const;

	/**
 * @brief Set the active texture unit
 * @param p_TextureUnit The texture unit to activate
 */
	static void								SetActiveTextureUnit(uint8_t p_TextureUnit);

	/**
 * @brief Load image data from a file
 * @param p_filepath The path to the image file
 * @param p_width Reference to store the width of the image
 * @param p_height Reference to store the height of the image
 * @param p_channels Reference to store the number of color channels of the image
 * @return Pointer to the loaded image data
 */
	static unsigned char*					LoadFile(const char* p_filepath, int& p_width, int& p_height, uint8_t& p_channels);

	/**
 * @brief Check for OpenGL errors
 * @param p_location A string indicating the location where the error check is being performed
 */
	void									CheckGLErrors(const std::string& p_location);

	/**
 * @brief Free memory allocated for image data
 * @param p_data Pointer to the image data to be freed
 */
	static void								FreeImageData(unsigned char* p_data);

	/**
 * @brief Compare two textures for equality
 * @param p_other The Texture object to compare with
 * @return True if the textures are equal, false otherwise
 */
	bool									operator==(const Texture& p_other) const;

	/**
 * @brief Compare two textures for inequality
 * @param p_other The Texture object to compare with
 * @return True if the textures are not equal, false otherwise
 */
	bool									operator!=(const Texture& p_other) const;

	/**
 * @brief Resize the texture
 * @param p_newWidth The new width of the texture
 * @param p_newHeight The new height of the texture
 */
	void									Resize(int p_newWidth, int p_newHeight);

	/**
 * @brief Load a cubemap texture from a set of six images representing the faces of the cube
 * @param p_faceFilepaths Vector containing file paths to the images representing the faces of the cube
 */
	void									LoadCubeMap(const std::vector<std::string>& p_faceFilepaths);
private:
	uint32_t								m_textureID;
	int										m_width;
	int										m_height;
	uint8_t									m_numChannels;
	unsigned char*							m_pixels;
	ETextureFilter							m_minFilter;
	ETextureFilter							m_magFilter;
	ETextureWrapMode						m_wrapS;
	ETextureWrapMode						m_wrapT;
	bool									m_generateMipmaps;
};