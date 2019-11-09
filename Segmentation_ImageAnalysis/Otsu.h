//
//  Otsu.h
//  Segmentation_ImageAnalysis
//
//  Created by 宋題均 on 2017/10/20.
//  Copyright © 2017年 宋題均. All rights reserved.
//

#ifndef Otsu_h
#define Otsu_h
using namespace cv;
unsigned char Otsu(const Mat &hist){
    int totalpixel =0;
    unsigned int Esum = 0;           //the sum of i*p(i)
    unsigned int sumA = 0;           //the sum of i*p(i) of the frist group
    float pixelA = 0;                //the number of pixel of first group
    float pixelB = 0;                //the number of pixel of second group
    float meanB = 0;                 //the mean value of second group
    float max_var = 0;
    float inter_var = 0;
    unsigned char threshold = 0;
    //calculate Esum and the number of total pixel
    for(int i=0;i<256;i++){
        Esum += i * hist.at<float>(i);
        totalpixel += hist.at<float>(i);
    }
    //Find the biggest threshold
    for(int i=0;i<256;i++){
        //Depart in two gruop A and B
        pixelA += hist.at<float>(i);
        pixelB = totalpixel - pixelA;
        if(pixelA == 0 || pixelB == 0){
            continue;
        }
        //calculate the possibility and mean of A and B respectively
        sumA += i * hist.at<float>(i);
        meanB = (Esum - sumA) / pixelB;
        inter_var = pixelA * pixelB * ((sumA / pixelA) - meanB) * ((sumA/pixelA)-meanB);
        if(inter_var >= max_var){
            threshold = i;
            max_var = inter_var;
        }
    }
    return threshold;
    
}

#endif /* Otsu_h */
