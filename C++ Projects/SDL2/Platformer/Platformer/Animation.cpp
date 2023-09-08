#include "Animation.h"

Animation::Animation(std::vector<SDL_Texture*> textures, int img_dur, bool loop)
    : images(textures), image_duration(img_dur), loop(loop)
{
    
}

void Animation::update()
{
    frame = (frame + 1) % (image_duration * images.size());
}

SDL_Texture* Animation::img()
{
    return images[int(frame / image_duration)];
}
