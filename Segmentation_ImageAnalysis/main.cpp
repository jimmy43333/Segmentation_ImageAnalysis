//
//  main.cpp
//  Segmentation_ImageAnalysis
//
//  Created by 宋題均 on 2017/10/18.
//  Copyright © 2017年 宋題均. All rights reserved.
//

#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Otsu.h"
#include "Sobel.h"
#include "readRawfile.h"
using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    //Sobel method
    Mat input;
    vector<Mat> output(2);
    vector<string> name;
    string file;
    name.clear();
    name.push_back("lenna");
    name.push_back("tiffany");
    name.push_back("mandrill");
    name.push_back("koala512");
    for(int i =0;i< name.size();i++){
        file = "/Users/TGsung/Desktop/Dataset/" + name[i] + ".raw";
        const char* cstr = file.c_str();
        input = readRawfile(cstr, 512, 512);
        output = Sobel(input);
        file = "/Users/TGsung/Desktop/" + name[i] + ".jpg";
        imwrite(file,input);
        file = "/Users/TGsung/Desktop/" + name[i] + "dst1.jpg";
        imwrite(file,output[0]);
        file = "/Users/TGsung/Desktop/" + name[i] + "dst2.jpg";
        imwrite(file,output[1]);
    }
    
    /*
    //Othu method
    Mat input,output;
    unsigned char thre = 0;  //the threshold to segment the images
    //input = imread("/Users/TGsung/Desktop/Frogs.jpg",CV_LOAD_IMAGE_COLOR);
    input = readRawfile("/Users/TGsung/Desktop/Dataset/lenna.raw",512,512);
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
    imwrite("/Users/TGsung/Desktop/linsfT.jpg",output);
    imshow("window1",input);
    imshow("window2",output);
    waitKey(0);
    */
    return 0;
}
