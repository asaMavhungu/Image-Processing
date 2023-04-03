from PIL import Image, ImageColor, ImageDraw

def save_pgm(image, filename):
    with open(filename, 'wb') as f:
        # write the PGM header
        width, height = image.size
        max_value = 255
        header = f"P5\n{width} {height}\n{max_value}\n"
        f.write(header.encode())

        # write the pixel data
        data = image.tobytes()
        f.write(data)
    
def save_inverted_pgm(image, filename):
    with open(filename, 'wb') as f:
        # write the PGM header
        width, height = image.size
        max_value = 255
        header = f'P5\n{width} {height}\n{max_value}\n'
        f.write(header.encode())

        # invert and write the pixel data
        data = bytearray(image.tobytes())
        for i in range(len(data)):
            data[i] = max_value - data[i]
        f.write(data)

# size of the image
width, height = 500, 500

# create a new image
img = Image.new('L', (width, height), color='black')

# create a drawing context
draw = ImageDraw.Draw(img)

# define the sizes of the squares
sizes = [50, 75, 100, 125, 150]

# define the positions of the squares
positions = [(50, 50), (250, 50), (50, 250), (350, 150), (200, 350)]

# define the fill colors of the squares
fill_colors = ['red', 'green', 'blue', 'yellow', 'purple']

# draw the squares
for size, position, fill_color in zip(sizes, positions, fill_colors):
    x, y = position
    draw.rectangle((x, y, x+size, y+size), fill=fill_color)

    # convert the color to its RGB values
    rgb_color = ImageColor.getrgb(fill_color)

    # compute the grayscale value using the formula
    gray_value = int(0.2989 * rgb_color[0] + 0.5870 * rgb_color[1] + 0.1140 * rgb_color[2])
    print(gray_value)

# save the image as a PGM file
save_pgm(img, 'squares.pgm')