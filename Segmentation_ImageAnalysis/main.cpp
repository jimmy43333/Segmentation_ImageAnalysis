//
//  main.cpp
//  Segmentation_ImageAnalysis
//
//  Created by 宋題均 on 2017/10/18.
//  Copyright © 2017年 宋題均. All rights reserved.
//

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Otsu.h"
using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    Mat input,output;
    unsigned char thre = 0;  //the threshold to segment the images
    //input = imread("/Users/TGsung/Desktop/Frogs.jpg",CV_LOAD_IMAGE_COLOR);
    
	//read the raw file
	FILE *fp = NULL;
	char *imagedata = NULL; 
	int imgwidth = 100;
	int imgheight = 100;
	int size = imgwidth * imgheight;
	//Open the raw iamges
	fp = fopen("/Users/TGsung/Desktop/ler.raw","rb");
    if(!fp){
        cout << "Open the file fail." << endl;
       return -1;
    }
	//Memory Allocation for image data buffer
	imagedata = (char*)malloc(sizeof(char) *size);
	//Read image and store in buffer
	fread(imagedata,sizeof(char),size,fp);
	//create opencv mat structure
	input.create(imgwidth,imgheight,CV_8U);
	memcpy(input.data,imagedata,size);
	free(imagedata);
	fclose(fp);

    
	//calculate the histogrim
	int histSize = 256;
	float range[] = {0, 255} ;
	const float* histRange = {range};
	Mat histImg;
	calcHist(&input, 1, 0, Mat(), histImg, 1, &histSize, &histRange);
	//use Otsu Binarization method
    thre = Otsu(histImg);
    //Use threshold to segmentation the images
    threshold(input, output, thre, 255, THRESH_BINARY);
    //printout the images
    imwrite("/Users/TGsung/Desktop/ler.jpg",output);
    imshow("window1",input);
    imshow("window2",output);
    waitKey(0);
    return 0;
}
