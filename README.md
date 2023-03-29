# Image Processing Application

The Image Processing App is a Python GUI application that loads image files, processes them using a C++ image processing library, and saves the results to new image files. The C++ library performs a 2D convolution operation on the image using a specified kernel. The app is built using Python 3.9 and the Tkinter GUI toolkit.

The filter used is a 5x5 kernel that performs a blurring effect on the image. The filter implementation is done in C++ using the OpenCV library, while the Python code is responsible for loading and saving the image files, and handling the user interface through a simple GUI.

The C++ code provides three functions to handle the image processing:

* load_image: Loads an image file and returns its pixel data as a 1D array of integers. The pixel data is in RGB format, with each pixel represented by three integers between 0 and 255. The function returns nullptr if the image file cannot be loaded. 

* save_image: Saves an image to a file. The function takes as input a pointer to an array containing the image data, the number of rows and columns of the image, and the filename to save the image to.

* process_image: Applies the blurring filter to an image. The function takes as input a pointer to an array containing the image data, the number of rows and columns of the image, and a pointer to the kernel data used for the filtering. The function returns a pointer to an array containing the filtered image data.

The Python code uses the tkinter module to create a simple GUI for the application. The GUI consists of a menu bar with two options to load image files or directories, and a "Process Images" button that starts the image processing algorithm. The numpy and ctypes modules are used to pass the image data between the Python and C++ code.

# Usage Instructions
To use the app, follow these steps:

* Install OpenCV and CMake on your machine.
* Compile the C++ library by running cmake . && make in the directory containing the C++ code.
* Run the Python script image_processing.py.
* Use the "Open File" and "Open Directory" buttons to select the images you want to process.
* Click the "Process Images" button to apply the kernel filter to the images.


# Image Processing Algorithm
The image processing algorithm is implemented in C++ using the OpenCV library. The algorithm performs a 2D convolution operation on the input image using a specified kernel. The kernel is a 5x5 matrix of floating-point values that defines the weights of neighboring pixels in the convolution operation. The algorithm loads the input image into memory as a 3D array of integers, with each pixel represented as a 3-element vector of red, green, and blue color channel values. The convolution operation is performed using the filter2D function from the OpenCV library. The output image is also represented as a 3D array of integers, with each pixel again represented as a 3-element vector of red, green, and blue color channel values. The resulting image is then saved to a file using the OpenCV imwrite function.

# Dependencies
The app requires the following dependencies to be installed:

Python 3.9
NumPy
OpenCV
Tkinter
