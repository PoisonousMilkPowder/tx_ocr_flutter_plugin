//
//  recdetect.h
//  recdetect
//
//  Created by fujikoli(李鑫) on 2017/9/15.
//  Copyright © 2017年 fujikoli(李鑫). All rights reserved.
//

#ifndef IMAGE_REFINE_H
#define IMAGE_REFINE_H

#include <string>
#ifdef YT_TINY_CV
#define custom_cv tiny_cv
#include <tiny_opencv2/opencv.hpp>
#else
#define custom_cv cv
#include <opencv2/opencv.hpp>
#endif

namespace YTCV_PUB {
    enum FILTER_TYPE {
        FILTER_BRIGHT = 1,
        FILTER_SHARP,
        FILTER_GRAY,
        FILTER_BINARY,
    };

    enum DETECT_TYPE {
        DETECT_GENERAL = 1,
        DETECT_HORIZONTAL_SCREEN,
        DETECT_VERTICAL_SCREEN,
        DETECT_VIN,  // VIN
        DETECT_PLATE, // 车牌
        DETECT_IDCARD,
        DETECT_BANK,
        DETECT_JSD_CARD,
        DETECT_XSD_CARD
    };

    class YtImageRefiner {
    public:
        static int GlobalInit(const std::string& model_path);
        static int GlobalDeinit();

        int BlurDetect(const custom_cv::Mat& src, double &result);
        int RectangleDetect(const custom_cv::Mat& src, std::vector<custom_cv::Point>& squares, double threshold1 = 1.5, double threshold2 = 2.0, int DETECT_TYPE = DETECT_GENERAL, int* out_detect_type = nullptr);
        int RectangleDetect(const custom_cv::Mat& src, std::vector<custom_cv::Point>& squares, custom_cv::Rect& roi_rect, double threshold1 = 1.5, double threshold2 = 2.0, int DETECT_TYPE = DETECT_GENERAL, int* out_detect_type = nullptr);
        int CropImage(const custom_cv::Mat& src, std::vector<custom_cv::Point>& squares, custom_cv::Mat &dst);
        int ImageFilter(const custom_cv::Mat& src, custom_cv::Mat& dst, int FILTER_TYPE);
    private:
        static bool _global_init_;
    };
}

#endif /* IMAGE_REFINE_H */