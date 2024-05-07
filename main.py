from PIL import Image
import os
os.makedirs("shadow_folder", exist_ok=True)

picNameArray = []
for i in range(1, 21):
    picNameArray.append("Picture" + str(i) + ".png")

picOutArray = []
for i in range(1, 21):
    picOutArray.append("OutputShadow" + str(i) + ".png")

for i in range(1, 21):
    image = Image.open(picNameArray[i-1])
    image = image.convert('RGBA')
    shadow_image = Image.new('RGBA', image.size, (0, 0, 0, 0))
    shadow_offset = (5, 5)
    shadow_image.paste((0, 0, 0, 255), shadow_offset, mask=image)
    result_image = Image.alpha_composite(image, shadow_image)
    
    output_path = os.path.join("shadow_folder", picOutArray[i-1])
    result_image.save(output_path)