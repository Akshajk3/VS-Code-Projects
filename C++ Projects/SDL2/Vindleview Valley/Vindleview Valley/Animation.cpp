#include "Animation.h"

Animation::Animation(std::vector<SDL_Texture*> textures, int img_dur, bool loop)
	: images(textures), image_duration(img_dur), loop(loop)
{

}

void Animation::update()
{
	if (loop)
		frame = (frame + 1) % (image_duration * images.size());
	else
	{
		if (frame >= image_duration * images.size() - 1) 
		{
			done = true;
		}
		else 
		{
			int image_size = static_cast<int>(images.size());
			frame = std::min(frame + 1, image_duration * image_size - 1);
		}
	}
}

SDL_Texture* Animation::img()
{
	return images[int(frame / image_duration)];
}
