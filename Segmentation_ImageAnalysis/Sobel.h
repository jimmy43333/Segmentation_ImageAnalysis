//
//  Sobel.h
//  Segmentation_ImageAnalysis
//
//  Created by 宋題均 on 2017/12/6.
//  Copyright © 2017年 宋題均. All rights reserved.
//

#ifndef Sobel_h
#define Sobel_h
#include "Otsu.h"
using namespace std;
using namespace cv;

vector<Mat> Sobel(Mat &input){
    vector<Mat> result(2);
    Mat src = input;
    GaussianBlur(src, src, Size(3,3), 0, 0);
        
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);  //轉成CV_8U
    Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT );
    convertScaleAbs(grad_y, abs_grad_y);
        
    Mat dst1, dst2;
    unsigned char thre = 0;  //the threshold to segment the images
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst1);
    //calculate the histogrim
    int histSize = 256;
    float range[] = {0, 255} ;
    const float* histRange = {range};
    Mat histImg;
    calcHist(&dst1, 1, 0, Mat(), histImg, 1, &histSize, &histRange);
    //use Otsu Binarization method
    thre = Otsu(histImg);
    //Use threshold to segmentation the images
    threshold(dst1, dst2, thre, 255, THRESH_BINARY);
    //threshold(dst1, dst2, 80, 255, THRESH_BINARY|THRESH_OTSU);
    result[0] = dst1;
    result[1] = dst2;
    return result;
}

#endif /* Sobel_h */
