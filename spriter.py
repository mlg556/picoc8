import imageio.v3 as iio

im = iio.imread("sprite.png")

W, H = 120, 160

with open("sprite.h", "w+") as f:
    f.write("// clang-format off\n")
    f.write(f"uint8_t sprite0[{W*H}] = {{\n")
    for pix_row in im:
        for pix in pix_row:
            f.write(f"\t{pix},")
        f.write("\n")
    f.write("};")
    f.write("// clang-format on")
