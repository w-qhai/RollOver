from PIL import Image
from PIL import ImageSequence

import os
import sys
import glob


def split_gif(image_name):
    folder = image_name[: -4]
    if not os.path.exists(folder):
        os.mkdir(folder)

    gif = Image.open(image_name)
    counter = 0
    max_width = 0
    max_heigth = 0
    for frame in ImageSequence.Iterator(gif):
        real_img = frame.crop(frame.getbbox())
        width, height = real_img.size
        max_width = max(max_width, width)
        max_heigth = max(max_heigth, height)
        transparent = real_img.getcolors().pop()[1]
        # 图片优化
        l_u_x, l_u_y = 0, 0
        # 左上角
        for l_u_y in range(height):
            for l_u_x in range(width):
                dot = (l_u_x, l_u_y)
                if real_img.getpixel(dot) == transparent:
                    break
            else:
                continue
            break
        # 右下角
        r_d_x, r_d_y = 0, 0
        for r_d_y in range(height - 1, -1, -1):
            for r_d_x in range(width - 1, -1, -1):
                dot = (r_d_x, r_d_y)
                if real_img.getpixel(dot) == transparent:
                    break
            else:
                continue
            break
        t = real_img.crop((l_u_x, l_u_y, r_d_x, r_d_y));
        t.save("{}/{:0>3d}.{}".format(folder, counter, "png"))
        counter += 1
    return max_width, max_heigth, counter


def gif_to_png_list(image_name):
    width, heigth, counter = split_gif(image_name)
    folder = image_name[: -4]
    if not os.path.exists(folder):
        return

    img_list = os.listdir(folder)

    target = Image.new("RGBA", (width * counter, heigth))
    left = 1
    for img_name in img_list:
        img = Image.open(folder + '/' + img_name)
        target.paste(img, (left * width - img.width, heigth - img.height))
        left += 1
        # os.remove(folder + '/' + img_name)
    target.save("../Bin/game/data/images/" + folder + ".png")
    # os.rmdir(folder)


if __name__ == "__main__":
    # 转换当前目录下的gif
    for root, dirs, files in os.walk("./"):
        for file in files:
            if file.endswith(".gif"):
                gif_to_png_list(file)
                print("{}已转换完成".format(file))

    # for argv in sys.argv[1:]:
    #     for img_name in glob.glob(argv):
    #         gif_to_png_list(img_name)
    #         print("{}已转换完成".format(img_name))
