#pragma once
#include <string>
#include <vector>

enum class ETextureFilter
{
	Nearest,
	Linear,
	MipmapNearest,
	MipmapLinear
};

enum class ETextureWrapMode
{
	Repeat,
	ClampToEdge,
	MirroredRepeat
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
	bool									Load(const std::string& path);

	//Load the image data texture from a file and set up the texture
	bool									Init();

	//Bind the texture before rendering to use it 
	void									Bind() const;

	//Unbind when we done 
	void									Unbind() const;

	//Set textures parameters, filtering and Wrapping
	void									SetFiltering(ETextureFilter p_minFilter, ETextureFilter p_magFilter);
	void									SetWrapping(ETextureWrapMode p_wrapS, ETextureWrapMode p_wrapT);

	//Generate mipmaps for the texture for better rendering quality
	void									GenerateMipmaps();

	//Get width of the texture
	int										GetWidth() const;

	//Get height of the texture
	int										GetHeight() const;

	//Get the number of channels
	uint32_t								GetNumberOfChannels() const;

	//Set the active texture unit
	static void								SetActiveTextureUnit(uint8_t p_TextureUnit);

	//Load image data from a file
	static unsigned char*					LoadFile(const char* p_filepath, int& p_width, int& p_height, uint8_t& p_channels);

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