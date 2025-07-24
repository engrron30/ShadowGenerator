import shutil
import sys
import os

def copy_file(source_path, destination_path):
    try:
        # Ensure destination directory exists
        os.makedirs(os.path.dirname(destination_path), exist_ok=True)
        
        shutil.copy2(source_path, destination_path)
        print(f"✅ File copied from '{source_path}' to '{destination_path}'")
    except FileNotFoundError:
        print("❌ Source file not found.")
    except PermissionError:
        print("❌ Permission denied.")
    except Exception as e:
        print(f"❌ Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python copy_file.py <source_file> <destination_file>")
        sys.exit(1)

    source = sys.argv[1]
    destination = sys.argv[2]
    copy_file(source, destination)
