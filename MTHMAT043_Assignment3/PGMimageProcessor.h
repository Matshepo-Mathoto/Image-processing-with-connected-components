#ifndef __PGMIMAGEPROCESSOR_H
#define __PGMIMAGEPROCESSOR_H
#include "ConnectedComponent.h"

namespace MTHMAT043
{
  class PGMimageProcessor
    {
        private:
        std::shared_ptr<std::vector<std::shared_ptr<ConnectedComponent>>> array;
        unsigned char **image;
        int height,width;
        std::vector<std::string> filedata;
        //constructors
        public:
      
        PGMimageProcessor();
        PGMimageProcessor(unsigned char **img, int hgt, int wdt, std::vector<std::string> &filedata);
        ~PGMimageProcessor();
        PGMimageProcessor(const PGMimageProcessor & rhs);
        PGMimageProcessor(PGMimageProcessor && rhs);
        PGMimageProcessor& operator=(const PGMimageProcessor & rhs);
        PGMimageProcessor& operator=(PGMimageProcessor && rhs);

        //methods
        //methods to prcess the input image and exclude ones with less validSize, return the 
        //final number that is stored.
        int extractComponents(unsigned char threshold, int minValidSize);
        //remove componets that do not obey  size criteria return the remaining ones
        int filterComponentsBySize(int minSize, int MaxSize);
        //write a pgm image which contains all current components to the valid 
        //return a sucesss operator
        bool writeComoponents(const std::string &outFilename);
        //return number of componets
        int getComponentCount(void)const;
         //return number of pixles in larger componet
        int getLargestSize(void) const;
        //return number of pixles in smaller componet
        int getSmallestSize(void)const;
        //print out data for components components id and number of pixles
        void printComponentData(std::shared_ptr<ConnectedComponent> & theComponent)const;
        //method for floodfill method
        void floodFill(unsigned char ** image, int height, int width, int x, int y, unsigned char threshold, int newC, std::shared_ptr<MTHMAT043::ConnectedComponent> &comp);
        bool isValid(unsigned char ** image, int height, int width, int x, int y, unsigned char threshold, int newC);
        //method used as the driver.cpp for the testPgmImage.cpp to read the image 
        void TestPgmImageReader(PGMimageProcessor & rhs, std::string filename);
        
        //getter and setter methods
        int getHeight();
        int getWidth();
        unsigned char ** getImage();
        std::vector<std::string> getFiledata();
        void setHeight(int h);
        void setWidth(int w);
        void setImage(unsigned char ** img);
        void setFiledata(std::vector<std::string> src);
        std::shared_ptr<std::vector<std::shared_ptr<ConnectedComponent>>> getArray();
    };  
}
#endif