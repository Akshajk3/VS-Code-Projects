#include "TextureManager.h"

#if __cplusplus == 201103L
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif

TextureManager::TextureManager() {}

SDL_Texture* TextureManager::loadTexture(const char* filename, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filename);
	
	if (texture == NULL)
	{
		std::cout << "Failed to Load Texture. SDL_Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

std::vector<SDL_Texture*> TextureManager::loadTextures(std::string& directoryPath, SDL_Renderer* renderer)
{
	std::vector<SDL_Texture*> textures;

	std::vector<std::string> filePaths;
	for(const auto& entry : fs::directory_iterator(directoryPath))
	{
		filePaths.push_back(entry.path().string());
	}
	std::sort(filePaths.begin(), filePaths.end());

	for (const std::string& filePath : filePaths)
	{
		std::cout << filePath << std::endl;
		SDL_Texture* texture = loadTexture(filePath.c_str(), renderer);
		if(texture)
		{
			textures.push_back(texture);
		}
	}

	return textures;
}
