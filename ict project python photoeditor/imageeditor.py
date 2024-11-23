from PIL import Image, ImageEnhance, ImageFilter
import os

def edit_images(input_path, output_path):
    os.makedirs(output_path, exist_ok=True)

    for filename in os.listdir(input_path):
        file_path = os.path.join(input_path, filename)

        if filename.lower().endswith(('.jpg', '.jpeg', '.png', '.bmp', '.tiff')):
            try:
                img = Image.open(file_path)
                edit = img.filter(ImageFilter.SHARPEN)
                edit = edit.convert('L')
                # edit = edit.rotate(-90, expand=True)
                # edit = edit.resize((800, 800))
                factor = 1.5
                enhancer = ImageEnhance.Sharpness(edit)
                edit = enhancer.enhance(factor)
                clean_name = os.path.splitext(filename)[0]
                save_path = os.path.join(output_path, f"{clean_name}_edited.jpg")
                edit.save(save_path)
                print(f"Processed and saved: {save_path}")

            except Exception as e:
                print(f"Error processing file {filename}: {e}")

    print("Batch processing complete!")

input_path = r"C:\Users\Saahil\Desktop\ict project\imgs"
output_path = r"C:\Users\Saahil\Desktop\ict project\edited_imgs"

if not os.path.exists(input_path):
    print(f"Input path does not exist: {input_path}")
else:
    edit_images(input_path, output_path)
