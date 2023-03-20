#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;

	int imgWidth, imgHeight, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(ID);
	glBindTexture(texType, ID);

	glTexParameteri();

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
}