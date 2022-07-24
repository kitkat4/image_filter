#pragma once

#include <opencv2/opencv.hpp>

#include <my_utils_kk4.hpp>

#include <string>

namespace image_filter{


class ImageFilter{
public:
    ImageFilter();
    ~ImageFilter();

    void init(const std::string& image_path);

    void enterMainLoop();

protected:

    static void callbackResetButton(int state, void * data);
    static void callbackOrbButton(int state, void * data);
    static void callbackThresholdButton(int state, void * data);
    static void drawKeyPoints(cv::Mat image, const std::vector<cv::KeyPoint>& keypoints);
    
    static ImageFilter * instance_;

    cv::Mat image_;
    cv::Mat image_org_;
    std::string window_name_;

    int nfeatures_;
    int threshold_;

    std::vector<cv::KeyPoint> keypoints_;
    cv::Mat descriptors_;
};

}
