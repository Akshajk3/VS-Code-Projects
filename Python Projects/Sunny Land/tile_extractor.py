from PIL import Image

def extract_non_transparent_tiles(tilemap_path, output_folder, tile_width, tile_height):
    tilemap = Image.open(tilemap_path)
    map_width, map_height = tilemap.size

    num_tiles_x = map_width // tile_width
    num_tiles_y = map_height // tile_height

    for y in range(num_tiles_y):
        for x in range(num_tiles_x):
            left = x * tile_width
            upper = y * tile_height
            right = left + tile_width
            lower = upper + tile_height

            tile = tilemap.crop((left, upper, right, lower))

            # Check if the tile has any non-transparent pixels
            if tile.getbbox():
                tile_filename = f"tile_{y * num_tiles_x + x:03d}.png"
                tile_path = output_folder + "/" + tile_filename

                tile.save(tile_path)
                print(f"Saved {tile_path}")

if __name__ == "__main__":
    tilemap_path = "tileset.png"
    output_folder = "OUTPUT"
    tile_width = 16  # Adjust according to your tilemap
    tile_height = 16  # Adjust according to your tilemap

    extract_non_transparent_tiles(tilemap_path, output_folder, tile_width, tile_height)
