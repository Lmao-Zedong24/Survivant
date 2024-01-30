#pragma once
#include <string>
#include "glad/gl.h"

class Texture
{
public:

	//Initialise and allocate resources for your texture in the constructor
	Texture(const std::string& p_filepath);

	//Release any allocated resources in the destructor
	~Texture();

	//Load the image data texture from a file and set up the texture
	void									LoadTexture();

	//Bind the texture before rendering to use it 
	void									Bind() const;

	//Unbind when we done 
	void									Unbind() const;

	//Set textures parameters, filtering and Wrapping
	void									SetFiltering(GLenum p_minFilter, GLenum p_magFilter);
	void									SetWrapping(GLenum p_wrapS, GLenum p_wrapT);

	//Generate mipmaps for the texture for better rendering quality
	void									GenerateMipmaps();

	//Get the OpenGL ID associated with the texture
	GLuint									GetID() const;

	//Get width of the texture
	int										GetWidth() const;

	//Get height of the texture
	int										GetHeight() const;

	//Get the number of channels
	uint32_t								GetNumberOfChannels() const;

	//Get the path of our texture
	std::string								GetPath();


	//Set the active texture unit
	static void								SetActiveTextureUnit(GLenum p_TextureUnit);

	//Load image data from a file
	static unsigned char* LoadFile(const char* p_filepath, int& p_width, int& p_height, GLenum& p_format);

	//Free memory allocated for image data
	static void								FreeImageData(unsigned char* p_data);


private:
	GLuint									m_textureID;
	int										m_width;
	int										m_height;
	uint32_t								m_numchannels;
	std::string								m_path;
	unsigned char* m_pixels;
};