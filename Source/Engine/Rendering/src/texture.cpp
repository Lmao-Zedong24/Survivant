#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "SurvivantRendering/Resources/texture.h"

Texture::Texture(const std::string& p_filepath) :
	m_path(p_filepath)
	, m_width(0)
	, m_height(0)
	, m_numchannels(0)
	, m_pixels(nullptr)
{
	// Load image using stb_image
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	m_pixels = stbi_load(p_filepath.c_str(), &width, &height, &channels, 0);

	if (m_pixels)
	{
		m_width = width;
		m_height = height;
		m_numchannels = (uint32_t)channels;
	}

	LoadTexture();
}

Texture::~Texture()
{
	stbi_image_free(m_pixels);
	m_pixels = nullptr;
}

void Texture::LoadTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	GLenum dataFormat = 0;
	if (m_numchannels == 4)
	{
		dataFormat = GL_RGBA;
	}
	else if (m_numchannels == 3)
	{
		dataFormat = GL_RGB;
	}

	if (m_pixels && dataFormat == 0)
	{
		std::cerr << "Texture format not supported - num channels: {}" << m_numchannels << std::endl;
	}

	if (m_pixels && dataFormat != 0)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, m_pixels);
		std::cerr << "Loaded {}-channel texture: {}" << m_numchannels << " " << m_path.c_str() << std::endl;
	}
	else
	{
		float pixels[] = {
			1.f, 0.f, 1.f,			1.f,1.f,1.f,         1.f,0.f,1.f,          1.f,1.f,1.f,
			1.f,1.f,1.f,			1.f,0.f,1.f			 ,1.f,1.f,1.f			,1.f,1.f,1.f,
			1.f, 0.f, 1.f,			1.f,1.f,1.f,         1.f,0.f,1.f,          1.f,1.f,1.f,
			1.f,1.f,1.f,			1.f,0.f,1.f			 ,1.f,1.f,1.f			,1.f,1.f,1.f
		};

		m_width = 4;
		m_height = 4;
		m_numchannels = 3;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, pixels);
		std::cerr << "Unable to load texture: {} " << m_path.c_str() << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFiltering(GLenum p_minFilter, GLenum p_magFilter)
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_magFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrapping(GLenum p_wrapS, GLenum p_wrapT)
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_wrapT);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateMipmaps()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetID() const
{
	return m_textureID;
}

int Texture::GetWidth() const
{
	return m_width;
}

int Texture::GetHeight() const
{
	return m_height;
}

uint32_t Texture::GetNumberOfChannels() const
{
	return m_numchannels;
}

std::string Texture::GetPath()
{
	return m_path;
}

void Texture::SetActiveTextureUnit(GLenum p_textureUnit)
{
	glActiveTexture(p_textureUnit);
}

unsigned char* Texture::LoadFile(const char* p_filepath, int& p_width, int& p_height, GLenum& p_format)
{
	int channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(p_filepath, &p_width, &p_height, &channels, 0);

	if (!data)
	{
		std::cerr << "Failed to load texture: " << p_filepath << std::endl;
		return nullptr;
	}

	// Determine the OpenGL format based on the number of channels
	if (channels == 1)
	{
		p_format = GL_RED;
	}
	else if (channels == 3)
	{
		p_format = GL_RGB;
	}
	else if (channels == 4)
	{
		p_format = GL_RGBA;
	}
	else
	{
		std::cerr << "Unsupported number of channels: " << channels << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	return data;
}

void Texture::FreeImageData(unsigned char* p_data)
{
	stbi_image_free(p_data);
}