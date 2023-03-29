import os
import tkinter as tk
from tkinter import filedialog
from ctypes import cdll, c_int, POINTER
import numpy as np

class ImageProcessingApp:
    def __init__(self, master):
        self.master = master
        master.title("Image Processing App")

        # Create a menu bar
        menu = tk.Menu(master)
        master.config(menu=menu)

        # Create a file menu with "Open File" and "Open Directory" options
        file_menu = tk.Menu(menu)
        menu.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Open File", command=self.open_file)
        file_menu.add_command(label="Open Directory", command=self.open_directory)

        # Create a button to start image processing
        self.process_button = tk.Button(master, text="Process Images", command=self.process_images)
        self.process_button.pack()

        # Initialize the image list
        self.images = []

        # Load the C++ shared library
        self.lib = cdll.LoadLibrary('./image_processing.so')

    def open_file(self):
        # Open a file dialog to select a single image file
        image_path = filedialog.askopenfilename()
        if image_path:
            self.images = [image_path]

    def open_directory(self):
        # Open a file dialog to select a directory containing images
        directory_path = filedialog.askdirectory()
        if directory_path:
            self.images = [os.path.join(directory_path, filename) for filename in os.listdir(directory_path)]

    def process_images(self):
        if not self.images:
            return

        # Image processing algorithm in C++
        kernel = np.ones((5,5),np.float32)/25
        process_image = self.lib.process_image
        process_image.restype = POINTER(c_int)

        for image_path in self.images:
            # Load the image
            image = self.lib.load_image(image_path.encode('utf-8'))

            # Process the image
            image_processed = process_image(image.ctypes.data_as(POINTER(c_int)), image.shape[0], image.shape[1], kernel.ctypes.data_as(POINTER(c_int)))

            # Save the processed image with a new name
            filename, extension = os.path.splitext(image_path)
            output_path = filename + '_processed' + extension
            self.lib.save_image(image_processed.ctypes.data_as(POINTER(c_int)), image_processed.shape[0], image_processed.shape[1], output_path.encode('utf-8'))

if __name__ == '__main__':
    root = tk.Tk()
    app = ImageProcessingApp(root)
    root.mainloop()