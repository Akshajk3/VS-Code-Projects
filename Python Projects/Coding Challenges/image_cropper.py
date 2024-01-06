from PIL import Image
import os

def crop_image(input_path, output_path, width, height):

    imgs = []

    imgs = load_images(input_path)

    cropped_imgs = []

    for img in imgs:
        cropped_imgs.append(img.crop((0, 0, width, height)))

    i = 0
    for crop in cropped_imgs:
        crop.save(output_path + str(i) + ".jpeg")
        i += 1

def load_images(input_path):
    images = []
    for img_path in sorted(os.listdir(input_path)):
        images.append(Image.open(input_path + img_path))
        print(img_path)

    return images


input_img_path = "photos/"
output_img_path = "output/"

resolution = (150, 171)

crop_image(input_img_path, output_img_path, *resolution)