#include "PGMimageProcessor.h"
int main(int argc, char *argv[])
{
    std::string filename;
    int minValidSize =3;
    int maxValidSize;
    int threshold = 128;
    bool write_flag = false;
    bool size_flag = false; //used to check if the max Valid size was set or not
    std::string outputFile;
    std::vector<std::string> filedata;
    bool printCompData = false;
    if(argc >2)
    {
        std::vector <std::string> inputs;
        for(int i=1; i< argc;i++)
        {
            inputs.push_back(argv[i]);
        }
        for(int i=0; i< inputs.size();i++)
        {
           if(inputs[i] == "-s")
            {
                minValidSize = std::stoi(inputs[i+1]);
                maxValidSize = std::stoi(inputs[i+2]);
                size_flag = true;
                i +=2;
            }
            if(inputs[i] == "-t")
            {
                threshold =std::stoi(inputs[i+1]);
                i +=1;
            }
            if(inputs[i] == "-p")
            {
                printCompData = true;
            }
            if(inputs[i] == "-w")
            {
                outputFile = inputs[i+1];
                write_flag = true;
            }
        }
        
    }
    filename = argv[argc-1];
    //read the inpot file
    std::ifstream myfile(filename+".pgm", std::ios::binary);
    //check if file exist
    if(!myfile)
    {
        std::cout << "File not found." << std::endl;
        return 1;
    }
    std::string line;
    int width;
    int height;
    while(!myfile.eof())
    {
        std::getline(myfile,line);
        //get all the file data and store them to a vector
        if(isdigit(line[0]))
        {
            filedata.push_back(line);
            std::istringstream iss(line);
            iss >> width;
            iss >> height;
            myfile >> line >> std::ws;
            filedata.push_back(line);
            //allocate space for the array to store the input image
            unsigned char ** array_2d = new unsigned char*[height];
            for(int i=0; i < height; i++)
            {
                array_2d[i] = new unsigned char[width];
            }
            //read all the the pixles into the input array
            for(int i=0; i< height; i++)
            {
                myfile.read(reinterpret_cast<char*> (array_2d[i]), width);
            }
            myfile.close();
            if(!size_flag) //check the flag to set the max valid size or not
            {
                maxValidSize = width*height;
            }
            //instantiate the object
            MTHMAT043::PGMimageProcessor pgmImageProcessor(array_2d,height, width, filedata);
            pgmImageProcessor.extractComponents(threshold,minValidSize);
            int size =pgmImageProcessor.filterComponentsBySize(minValidSize,maxValidSize);
            pgmImageProcessor.writeComoponents(outputFile+".pgm");
            int large = pgmImageProcessor.getLargestSize();
            int small = pgmImageProcessor.getSmallestSize();
            if(printCompData)
            {
                //looping through the components and print out their information
                std::shared_ptr<std::vector<std::shared_ptr<MTHMAT043::ConnectedComponent>>> array =pgmImageProcessor.getArray();
                for (auto i = array->begin(); i != array->end(); ++i)
                {
                    pgmImageProcessor.printComponentData((*i));
                    std::cout << "\n";
                }
                
                std::cout << "Total component number = " << size << std::endl;
                std::cout << "Largest component size = " << large << std::endl;
                std::cout << "Smallest component size = " << small << std::endl;

            }
            break;
        }
        filedata.push_back(line);
    }
}