from PIL import Image
import os
import sys

output_file_name = "Scripts/OutputShadow.png"

def add_shadow_to_image(image_path):
    try:
        # Remove input file if it exists
        if os.path.exists(output_file_name):
            os.remove(output_file_name)
            print(f"🗑️ Removed existing file: {output_file_name}")

        # Open and convert image
        image = Image.open(image_path).convert('RGBA')
        
        # Create shadow image
        shadow_image = Image.new('RGBA', image.size, (0, 0, 0, 0))
        shadow_offset = (5, 5)
        shadow_image.paste((0, 0, 0, 255), shadow_offset, mask=image)

        # Composite image and shadow
        result_image = Image.alpha_composite(image, shadow_image)

        # Create output file path
        filename = os.path.basename(image_path)

        # Save result
        result_image.save(output_file_name)
        print(f"✅ Shadow added. Saved to: {output_file_name}")
        
    except FileNotFoundError:
        print("❌ File not found.")
    except Exception as e:
        print(f"❌ Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python add_shadow.py <image_file>")
        sys.exit(1)

    input_image_path = sys.argv[1]
    add_shadow_to_image(input_image_path)
