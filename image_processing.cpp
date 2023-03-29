#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

extern "C" {

int* load_image(const char* filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to load image " << filename << std::endl;
        return nullptr;
    }

    int* data = new int[image.rows * image.cols * 3];
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);
            int index = (row * image.cols + col) * 3;
            data[index] = pixel[0];
            data[index + 1] = pixel[1];
            data[index + 2] = pixel[2];
        }
    }

    return data;
}

void save_image(int* data, int rows, int cols, const char* filename) {
    cv::Mat image(rows, cols, CV_8UC3);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int index = (row * cols + col) * 3;
            cv::Vec3b pixel(data[index], data[index + 1], data[index + 2]);
            image.at<cv::Vec3b>(row, col) = pixel;
        }
    }

    cv::imwrite(filename, image);
}

int* process_image(int* data, int rows, int cols, int* kernel_data) {
    cv::Mat image(rows, cols, CV_8UC3);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int index = (row * cols + col) * 3;
            cv::Vec3b pixel(data[index], data[index + 1], data[index + 2]);
            image.at<cv::Vec3b>(row, col) = pixel;
        }
    }

    cv::Mat kernel(5, 5, CV_32F, kernel_data);

    cv::Mat image_processed;
    cv::filter2D(image, image_processed, -1, kernel);

    int* data_processed = new int[rows * cols * 3];
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cv::Vec3b pixel = image_processed.at<cv::Vec3b>(row, col);
            int index = (row * cols + col) * 3;
            data_processed[index] = pixel[0];
            data_processed[index + 1] = pixel[1];
            data_processed[index + 2] = pixel[2];
        }
    }

    return data_processed;
}

}