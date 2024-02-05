#pragma once
#include <string>
#include <vector>

enum class TextureMinFilter
{
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	MipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
	MipmapLinear = GL_LINEAR_MIPMAP_LINEAR
};

enum class TextureMagFilter
{
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR
};

enum class TextureWrapMode
{
	Repeat = GL_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
	MirroredRepeat = GL_MIRRORED_REPEAT
};

class Texture
{
public:

	//Default constructor
	Texture();

	//Release any allocated resources in the destructor
	~Texture();

	//Copy constructor
	Texture(const Texture& other);

	//Load the image data texture from a file and set up the texture
	void									LoadTexture();

	//Bind the texture before rendering to use it 
	void									Bind() const;

	//Unbind when we done 
	void									Unbind() const;

	//Set textures parameters, filtering and Wrapping
	void									SetFiltering(TextureMinFilter p_minFilter, TextureMagFilter p_magFilter);
	void									SetWrapping(TextureWrapMode p_wrapS, TextureWrapMode p_wrapT);

	//Generate mipmaps for the texture for better rendering quality
	void									GenerateMipmaps();

	// Flag to control mipmaps generation
	void									EnableMipmaps(bool p_generateMipmaps);

	//Get width of the texture
	int										GetWidth() const;

	//Get height of the texture
	int										GetHeight() const;

	//Get the number of channels
	uint32_t								GetNumberOfChannels() const;

	//Set the active texture unit
	static void								SetActiveTextureUnit(GLenum p_TextureUnit);

	//Load image data from a file
	static unsigned char*					LoadFile(const char* p_filepath, int& p_width, int& p_height, GLenum& p_format);

	//Checking OpenGL errors
	void									CheckGLErrors(const std::string& p_location);

	//Free memory allocated for image data
	static void								FreeImageData(unsigned char* p_data);

	//Compare two textures for equality
	bool									operator==(const Texture& p_other) const;
	bool									operator!=(const Texture& p_other) const;

	//Resize the texture
	void									Resize(int p_newWidth, int p_newHeight);

	//Loads a cubemap texture from a set of six images representing the faces of the cube
	void									LoadCubeMap(const std::vector<std::string>& p_faceFilepaths);
private:
	GLuint									m_textureID;
	int										m_width;
	int										m_height;
	uint32_t								m_numchannels;
	std::string								m_path;
	unsigned char*							m_pixels;
	TextureMinFilter						m_minFilter;
	TextureMagFilter						m_magFilter;
	TextureWrapMode							m_wrapS;
	TextureWrapMode							m_wrapT;
	bool									m_generateMipmaps;
};