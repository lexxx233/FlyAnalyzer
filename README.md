#Flynotyper 1.0#

##Introduction

Flynotyper is a software tool to quantify eye morphology phenotypes in Drosophila melanogaster.  
About two-thirds of the vital genes in the Drosophila genome are also involved in eye development, 
making the fly eye a tangible system to study basic biological processes.  Quantifying defects in 
eye morphology can be useful to understand gene control and classify genetic interactions.  
Flynotyper detects disruption of symmetry of ommatidial arrangements and calculates a phenotypic 
score as a measure of defect in eye morphology.  This software can be used for high throughput 
functional genetic screening and works with equal accuracy for eye images taken using both bright 
field and scanning electron microscopes.

##System Requirements

Flynotyper will require the [OpenCV library](http://sourceforge.net/projects/opencvlibrary/) for 
image processing. We recommend using version 2.4.10+. To install OpenCV, your system will also need 
GCC 4.4.x or later, and CMake 2.6 or higher. Please install OpenCV and its dependencies by following 
the instructions in the "Installation" section.

##Installation

###Install OpenCV
Make sure you have GCC and CMake installed on your system. 
Download the latest version of OpenCV:

$ cd ~/<my_working_directory>
$git clone https://github.com/Itseez/opencv.git

###Build OpenCV
$ cd ~/<my_working_directory>
$ mkdir build
$ cd build
$ cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
$ make 
$ sudo make install
The full instruction for the installation of OpenCV can be found at [this link](http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation)

###Build flynotyper
Download the source code: [flynotyper.tar.gz](http://sourceforge.net/projects/flynotyper/files/)
$ tar -vxf flynotyper.tar.gz
$ cd flynotyper
$ make
Copy flynotyper to a location you want (e.g. a directory in your $PATH). 

##Usage

Run the program by using the filename of the eye image as the input and different parameters:
$ flynotyper <filename> [-sem] [-n count]

parameters:
-sem: use this parameter if the image file was taken using SEM.
-h: on default, eyes were taken vertically (such as example/eye.tif). Therefore, if eyes were taken horizontally (such as example/sem.tif), use this parameter.
-n count: the number of most stable ommatidia taken into consideration when calculating the phenotypic score (see Iyer, Wang, Le, et al, for more information). The default number is 200.

For example, to get the phenotypic score for the image eye.tif in the "example" folder, run:
$ flynotyper eye.tif

If the image was taken using the SEM, use parameter -sem after the file name.

For eample, to obtain the phenotypic score for the image sem.tif in the "example" folder, run:
$ flynotyper sem.tif -sem -h

##Output

The output includes 5 columns, as shown in the following example:

 |    ODId	  |    ODIa   |    ODI    |    Z    |     P   |  
 |---|---|---|---|---| 
 | 334.334 | 588.983 | 294.491 |   575   | 46.3446 |  

In which:
>ODId: Total distance ommatidial disorderliness index of all stable ommatidia;  
ODIa: Total angle ommatidial disorderliness index of all stable ommatidia;  
ODI: Total ommatidial disorderliness index of all stable ommatidia, ODI = log(ODId + ODIa);
Z: Fusion index, which is the number of detected ommatidia;  
P: Phenotypic score, calculated based on ODI and Z.   

More details on algorithm development, software implementation, and performance evaluation of Flynotyper can be found here.
