/* 
 * File:   main.cpp
 * Author: Thanh Le &qingyuwang
 *
 * Created on September 18, 2014, 11:25 AM
 */

#include "image.h"
#include "ientropy.h"
#include <vector>
#include <string>

using namespace cv;
    
int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: Flynotyper <Image_Path> [-sem][-h][-n count]\n" << endl;
        return -1;
    }
    
    string param("");
    int param_int;
    Mat image;
    std::vector<Point> cpt; //vector of center point
    Point cpt_img; //center of the eye
    bool b_crop = false;  //if the image need to be cropped 
    bool b_imagej = false; //if the image is processed by ImageJ or not
    bool b_write = false;
    bool b_sem = false;
    bool b_horiz = false; //if the image is taken horizontal or not
    bool b_debug = false;
    int rankType = 3; //1: rank by entropy; 2: rank by the distance to the center; 3: rank by distance to the center first then choose the most stable ones
    int inc = 200;
    int z = 0;
    int r = 9;
    double de, ae, e, p; 
  
    for (int i = 2; i < argc; i ++) {
        param += argv[i];
        if (!strcmp(argv[i], "-n")) {
            if (i + 1 < argc) {
                inc = atoi(argv[i + 1]);
            } else {
                cout << "Usage: Flynotyper <Image_Path> [-sem][-h][-n count]\n" << endl;
                return -1;
            }
        }
    }
    
    if (param.find('j') != string::npos) b_imagej = true;
    if (param.find('w') != string::npos) b_write = true;
    if (param.find("-rs") != string::npos) rankType = 1;  //Rank the ommitidia by phenotypic scores (most stable ones)
    if (param.find("-rd") != string::npos) rankType = 2; //Rank the ommitidia by the distance to the center; default is both
    if (param.find("debug") != string::npos) b_debug = true;
    if (param.find("h") != string::npos) b_horiz = true;
    if (param.find("sem") != string::npos) {
        b_sem = true;
        r = 2;
    }
    if (b_sem) rankType = 1;
    
    image = imread(argv[1], 1);

    if ( !image.data ) {
        printf ("No image data \n");
        exit (-1);
    }
    
    cpt_img.x = image.cols/2;
    cpt_img.y = image.rows/2;
    
    cpt = detectOmmatidia(image, b_imagej, b_sem, b_horiz, b_debug, b_write); //used 3 before
    if (!b_imagej) {
        cpt_img = cpt[cpt.size() - 1];
        cpt.pop_back();
    }
    
    z = cpt.size();
    
    if (b_debug) {
        for (int i = 0; i < cpt.size(); i ++) {
            circle(image, cpt[i], r, Scalar(65, 110, 244), 3);
        }
        namedWindow("Final image", WINDOW_AUTOSIZE);
        imshow("Final image", image);
        waitKey();
    }
    
    if (b_write == true) {
        string title("Circled_");
        title += argv[1];
        cout << title << endl;
        imwrite(title, image);
    }
    
    if (b_write == false) {
        p = phynoScore(cpt_img, cpt, z, inc, de, ae, e, rankType);
        cout << de << "\t" << ae << "\t" << e << "\t" << z << "\t" << p << endl;
    }

    return 0;
}