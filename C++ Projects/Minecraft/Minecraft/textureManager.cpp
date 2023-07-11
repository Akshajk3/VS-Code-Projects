#include "textureManager.h"

TextureManager::TextureManager(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{

	type = texType;

	int widthImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(false);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);


	glGenTextures(1, &ID);

	glActiveTexture(slot);
	glBindTexture(texType, ID);


	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void TextureManager::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void TextureManager::addTexture(const std::string& texture_path)
{
	
}

void TextureManager::Bind()
{
	glBindTexture(type, ID);
}

void TextureManager::Unbind()
{
	glBindTexture(type, 0);
}

void TextureManager::Delete()
{
	glDeleteTextures(1, &ID);
}