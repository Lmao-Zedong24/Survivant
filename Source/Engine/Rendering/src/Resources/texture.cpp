#include "SurvivantRendering/Resources/texture.h"

#include <iostream>
#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLenum ToGLEnum(ETextureFilter p_filter)
{
	switch (p_filter)
	{
	case ETextureFilter::NEAREST:
		return GL_NEAREST;
	case ETextureFilter::LINEAR:
		return GL_LINEAR;
	case ETextureFilter::MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	case ETextureFilter::MIPMAP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		return GL_INVALID_ENUM;
	}
}

GLenum ToGLEnum(ETextureWrapMode p_wrap)
{
	switch (p_wrap)
	{
	case ETextureWrapMode::REPEAT:
		return GL_REPEAT;
	case ETextureWrapMode::CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;
	case ETextureWrapMode::MIRRORED_REPEAT:
		return GL_MIRRORED_REPEAT;
	default:
		return GL_INVALID_ENUM;
	}
}

GLint GetGLFormat(uint8_t channels)
{
	// Determine the OpenGL format based on the number of channels
	if (channels == 1)
	{
		return GL_RED;
	}
	else if (channels == 3)
	{
		return GL_RGB;
	}
	else if (channels == 4)
	{
		return GL_RGBA;
	}
	else
	{
		std::cerr << "Unsupported number of channels: " << channels << std::endl;
		return GL_INVALID_ENUM;
	}
}

Texture::Texture() :
	  m_width(0)
	, m_height(0)
	, m_numChannels(0)
	, m_pixels(nullptr),
	m_textureID(0),
	m_minFilter(ETextureFilter::NEAREST),
	m_magFilter(ETextureFilter::NEAREST),
	m_wrapS(ETextureWrapMode::REPEAT),
	m_wrapT(ETextureWrapMode::REPEAT) 
{

}

Texture::~Texture()
{
	stbi_image_free(m_pixels);
	m_pixels = nullptr;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Texture& other) : m_textureID(0), m_width(0), m_height(0), m_numChannels(0), m_pixels(nullptr),
m_minFilter(ETextureFilter::LINEAR), m_magFilter(ETextureFilter::LINEAR), m_wrapS(ETextureWrapMode::REPEAT),
m_wrapT(ETextureWrapMode::REPEAT), m_generateMipmaps(false)
{
	// Copy the data from the source texture
	if (other.m_textureID != 0) 
	{
		glGenTextures(1, &m_textureID);
		Bind();

		// Copy texture parameters
		SetFiltering(m_minFilter, m_magFilter);
		SetWrapping(m_wrapS, m_wrapT);

		// Copy texture data if necessary
		if (other.m_pixels != nullptr) {
			m_width = other.m_width;
			m_height = other.m_height;
			m_numChannels = other.m_numChannels;
			m_pixels = new unsigned char[m_width * m_height * m_numChannels];
			std::copy_n(other.m_pixels, other.m_pixels + m_width * m_height * m_numChannels, m_pixels);

			// Generate mipmaps if needed
			if (other.m_generateMipmaps) {
				GenerateMipmaps();
			}
		}
		Unbind();
	}
}

bool Texture::Load(const std::string& p_path)
{
	stbi_set_flip_vertically_on_load(true);

	int channels;
	m_pixels = stbi_load(p_path.c_str(), &m_width, &m_height, &channels, 0);

	m_numChannels = static_cast<uint8_t>(channels);

	if (!m_pixels)
	{
		std::cerr << "Failed to load texture: " << p_path << std::endl;
		return false;
	}

	return true;
}

//bool Texture::Load(const std::string& p_path)
//{
//	m_pixels = LoadFile(p_path.c_str(), m_width, m_height, m_numChannels);
//	return m_pixels != nullptr;
//}

bool Texture::Init()
{
	if (m_pixels == nullptr)
	{
		std::cerr << "No texture data";
		return false;
	}

	GLenum dataFormat = GetGLFormat(m_numChannels);

	if (dataFormat == GL_INVALID_ENUM)
	{
		std::cerr << "Texture format not supported - num channels: " << m_numChannels;
		return false;
	}

	if (m_textureID == 0)
	{
		glGenTextures(1, &m_textureID);

		if (m_textureID == 0)
		{
			std::cerr << "Failed to create texture id";
			return false;
		}
	}

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, m_pixels);

	Unbind();
	return true;
}

void Texture::SetFiltering(ETextureFilter p_minFilter, ETextureFilter p_magFilter)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ToGLEnum(p_minFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ToGLEnum(p_magFilter));
	Unbind();
}

void Texture::SetWrapping(ETextureWrapMode p_wrapS, ETextureWrapMode p_wrapT)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToGLEnum(p_wrapS));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToGLEnum(p_wrapT));
	Unbind();
}

void Texture::GenerateMipmaps()
{
	Bind();
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();
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
	return m_numChannels;
}

void Texture::SetActiveTextureUnit(uint8_t p_textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + static_cast<GLint>(p_textureUnit));
}

//unsigned char* Texture::LoadFile(const char* p_filepath, int& p_width, int& p_height, uint8_t& p_channels)
//{
//	stbi_set_flip_vertically_on_load(true);
//
//	int channels;
//	unsigned char* data = stbi_load(p_filepath, &p_width, &p_height, &channels, 0);
//
//	p_channels = static_cast<uint8_t>(channels);
//
//	if (!data)
//	{
//		std::cerr << "Failed to load texture: " << p_filepath << std::endl;
//		return nullptr;
//	}
//
//	return data;
//}

void Texture::CheckGLErrors(const std::string& p_location)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error at " << p_location << ":" << std::endl;
	}
}

bool Texture::operator==(const Texture& other) const
{
	return m_textureID == other.m_textureID;
}

bool Texture::operator!=(const Texture& other) const
{
	return !(*this == other);
}

void Texture::FreeImageData(unsigned char* p_data)
{
	stbi_image_free(p_data);
}