// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef NANODET_H
#define NANODET_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <net.h>

struct Object
{
    cv::Rect_<float> rect;
    cv::Mat mask;
    int label;
    float prob;
};

class NanoDet
{
public:
    NanoDet();

    int load(const char* modeltype, bool use_gpu = false);

    //int load(const char* modeltype, int target_size, const float* mean_vals, const float* norm_vals, bool use_gpu = false);

    //int detect(const cv::Mat& rgb, std::vector<Object>& objects, float prob_threshold = 0.4f, float nms_threshold = 0.5f);
    void seg(cv::Mat& rgb, cv::Mat& mask, cv::Rect& box);

    int draw(cv::Mat& rgb);

    /*
    * 保持宽高比的缩放
    * src:input
    * dst:output
    * scale:output,缩放比例
    * dstSize:input,目标尺寸
    */
    static bool resize_keepRatio(
        cv::Mat& src,
        cv::Mat& dst,
        float& scale,
        int dstSize
    );

private:
    //必选项=====================================================
    int target_size=288;
    float mean_vals[3] = { 123.675f, 116.28f,  103.53f };
    float norm_vals[3] = { 0.01712475f, 0.0175f, 0.01742919f };
    //===========================================================
    ncnn::Net hairseg;
    int colorFlag;
    float scale_input;//输入图像的缩放比例
    ncnn::UnlockedPoolAllocator blob_pool_allocator;
    ncnn::PoolAllocator workspace_pool_allocator;
};

#endif // NANODET_H
