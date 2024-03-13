#include "TextureManager.h"


TextureManager::TextureManager()
{
    
}

SDL_Texture* TextureManager::loadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    
    if (texture == nullptr)
    {
        std::cout << "Failed to Load texture. SDL_Error: " << SDL_GetError() << std::endl;
    }
    
    return texture;
}

std::vector<SDL_Texture*> TextureManager::loadTextures(std::string& directoryPath, SDL_Renderer *renderer)
{
    std::vector<SDL_Texture*> textures;
    
    std::vector<std::string> filePaths;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        filePaths.push_back(entry.path().string());
    }
    std::sort(filePaths.begin(), filePaths.end());
    
    for (const std::string& filePath : filePaths)
    {
        std::cout << filePath << std::endl;
        
    }
    
    return textures;
}
