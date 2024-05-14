#define CATCH_CONFIG_MAIN// This tells catch to provide a main() function. Only do this in one cpp file
#include "catch.hpp"
#include "PGMimageProcessor.h"

TEST_CASE( "PGMimageProcessor Class Unit Tests") {
    SECTION( "Default Constructor" ) {
        
        MTHMAT043::PGMimageProcessor pgmImageProcessor;
        REQUIRE(pgmImageProcessor.getHeight()== 0);
        REQUIRE(pgmImageProcessor.getWidth() == 0);
        REQUIRE(pgmImageProcessor.getImage() == nullptr);
        REQUIRE(pgmImageProcessor.getFiledata().empty()==true);
    }
    
    SECTION( "Copy Constructor with variables" ) {
        unsigned char ** image; //empty
        std::vector<std::string> filedata; //filedata
         MTHMAT043::PGMimageProcessor pgmImageProcessor(image,10,20,filedata);
         MTHMAT043::PGMimageProcessor copyPgmImageProcessor(pgmImageProcessor);
        REQUIRE(pgmImageProcessor.getFiledata() == pgmImageProcessor.getFiledata());
        REQUIRE(pgmImageProcessor.getHeight() == copyPgmImageProcessor.getHeight());
        REQUIRE(pgmImageProcessor.getWidth() == pgmImageProcessor.getWidth());

    }
    SECTION( "Copy Assignment Constructor with variables" ) {
        unsigned char ** image; //empty
        std::vector<std::string> filedata; //filedata
         MTHMAT043::PGMimageProcessor pgmImageProcessor(image,10,20,filedata);
         MTHMAT043::PGMimageProcessor pgmImageProcessor2(image,40,60,filedata);
         pgmImageProcessor2 = pgmImageProcessor;
        REQUIRE(pgmImageProcessor2.getFiledata() == filedata);
        REQUIRE(pgmImageProcessor2.getHeight() == 10);
        REQUIRE(pgmImageProcessor2.getWidth() == 20);

    }
    SECTION( "Move Constructor with variables" ) {
        unsigned char ** image; //empty
        std::vector<std::string> filedata; //filedata
         MTHMAT043::PGMimageProcessor pgmImageProcessor(image,10,20,filedata);
         MTHMAT043::PGMimageProcessor movePgmImageProcessor(std::move(pgmImageProcessor));
        REQUIRE(pgmImageProcessor.getFiledata() == filedata);
        REQUIRE(movePgmImageProcessor.getHeight() == 10);
        REQUIRE(movePgmImageProcessor.getWidth() == 20);

    }
    SECTION( "Move Assignmsignment Constructor with variables" ) {
        unsigned char ** image; //empty
        std::vector<std::string> filedata; //filedata
         MTHMAT043::PGMimageProcessor pgmImageProcessor(image,10,20,filedata);
         MTHMAT043::PGMimageProcessor pgmImageProcessor2(image,40,60,filedata);
         MTHMAT043::PGMimageProcessor movePgmImageProcessor2=std::move(pgmImageProcessor);
        REQUIRE(pgmImageProcessor2.getFiledata() == filedata);
        REQUIRE(movePgmImageProcessor2.getHeight() == 10);
        REQUIRE(movePgmImageProcessor2.getWidth() == 20);

    }
    SECTION( "A 10*10 image of all pixle 119 with 1 component" )
    {
        MTHMAT043::PGMimageProcessor pgmImageProcessor;
        pgmImageProcessor.TestPgmImageReader(pgmImageProcessor,"testImage4"); //same as the main method
        REQUIRE( pgmImageProcessor.extractComponents(100,3)== 1); 
        REQUIRE( pgmImageProcessor.filterComponentsBySize(3,200) ==1);
        REQUIRE(pgmImageProcessor.getComponentCount() ==1);
        REQUIRE( pgmImageProcessor.writeComoponents("output2")== true);
        REQUIRE(pgmImageProcessor.getSmallestSize() ==100);
        REQUIRE(pgmImageProcessor.getLargestSize() ==100);
    }
    SECTION( "10*10 image with no components" )
    {
        MTHMAT043::PGMimageProcessor pgmImageProcessor;
        pgmImageProcessor.TestPgmImageReader(pgmImageProcessor,"testImage3"); //same as the main method
        REQUIRE( pgmImageProcessor.extractComponents(82,1)== 0); 
        REQUIRE( pgmImageProcessor.filterComponentsBySize(3,200) ==0);
        REQUIRE(pgmImageProcessor.getComponentCount() ==0);
        REQUIRE( pgmImageProcessor.writeComoponents("output1")== true);
        REQUIRE(pgmImageProcessor.getSmallestSize() ==0);
        REQUIRE(pgmImageProcessor.getLargestSize() ==0);
    }
    SECTION( "10*10 image with a component of size 6*7" )
    {
        MTHMAT043::PGMimageProcessor pgmImageProcessor;
        pgmImageProcessor.TestPgmImageReader(pgmImageProcessor,"testImage1"); //same as the main method
        REQUIRE( pgmImageProcessor.extractComponents(100,3)== 1); 
        REQUIRE( pgmImageProcessor.filterComponentsBySize(3,200) ==1);
        REQUIRE(pgmImageProcessor.getComponentCount() ==1);
        REQUIRE( pgmImageProcessor.writeComoponents("output1")== true);
        REQUIRE(pgmImageProcessor.getSmallestSize() ==42);
        REQUIRE(pgmImageProcessor.getLargestSize() ==42);
    }

    SECTION( "Image with 4 components of different sizes" )
    {
        MTHMAT043::PGMimageProcessor pgmImageProcessor;
        pgmImageProcessor.TestPgmImageReader(pgmImageProcessor,"testImage5"); //same as the main method
        REQUIRE( pgmImageProcessor.extractComponents(82,1)== 4); 
        REQUIRE( pgmImageProcessor.filterComponentsBySize(3,200) ==3);
        REQUIRE(pgmImageProcessor.getComponentCount() ==3);
        REQUIRE( pgmImageProcessor.writeComoponents("output1")== true);
        REQUIRE(pgmImageProcessor.getSmallestSize() ==4);
        REQUIRE(pgmImageProcessor.getLargestSize() ==24);
    }
}