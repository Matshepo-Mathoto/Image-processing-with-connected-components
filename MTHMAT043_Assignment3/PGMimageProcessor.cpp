#include "PGMimageProcessor.h"
// big 6 implementation
MTHMAT043::PGMimageProcessor::PGMimageProcessor()
{
     array = std::make_shared<std::vector<std::shared_ptr<ConnectedComponent>>>();
}
MTHMAT043::PGMimageProcessor::PGMimageProcessor(unsigned char **img, int hgt, int wdt, std::vector<std::string> &filedt) : image(img), height(hgt), width(wdt), filedata(filedt)
{
    array = std::make_shared<std::vector<std::shared_ptr<ConnectedComponent>>>();
}
MTHMAT043::PGMimageProcessor::~PGMimageProcessor()
{
}
// copy constructor
MTHMAT043::PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &rhs)
{
    height = rhs.height;
    width = rhs.width;
    //copy the filedata
    for(int i=0; i< rhs.filedata.size();i++)
    {
        filedata.at(i) = rhs.filedata.at(i);
    }
    if (this != &rhs)
    {
        for (auto i = rhs.array->begin(); i != rhs.array->end(); i++)
        {
            array->push_back(*i);
        }
    }
}
MTHMAT043::PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&rhs)
{
    filedata=std::move(rhs.filedata);
    height = rhs.height;
    width = rhs.width;
    rhs.height =0;
    rhs.width =0;
    if (this != &rhs)
    {
        for (std::vector<std::shared_ptr<ConnectedComponent>>::iterator i = rhs.array->begin(); i != rhs.array->end(); i++)
        {
            array->push_back(std::move(*i));
        }
    }
}
MTHMAT043::PGMimageProcessor &MTHMAT043::PGMimageProcessor::operator=(const PGMimageProcessor &rhs)
{
    height = rhs.height;
    width = rhs.width;
    //copy the filedata
    for(int i=0; i< rhs.filedata.size();i++)
    {
        filedata.at(i) = rhs.filedata.at(i);
    }
    if (this != &rhs)
    {
        for (std::vector<std::shared_ptr<ConnectedComponent>>::const_iterator i = rhs.array->begin(); i != rhs.array->end(); i++)
        {
            array->push_back(*i);
        }
    }
    return *this;
}
MTHMAT043::PGMimageProcessor &MTHMAT043::PGMimageProcessor::operator=(PGMimageProcessor &&rhs)
{
    filedata=std::move(rhs.filedata);
    height = rhs.height;
    width = rhs.width;
    rhs.height =0;
    rhs.width =0;
    if (this != &rhs)
    {
        for (std::vector<std::shared_ptr<ConnectedComponent>>::iterator i = rhs.array->begin(); i != rhs.array->end(); i++)
        {
            array->push_back(std::move(*i));
        }
    }
    return *this;
}

// Methods
bool MTHMAT043::PGMimageProcessor::isValid(unsigned char **image, int height, int width, int x, int y, unsigned char threshold, int newC)
{
    if (x < 0 || x >= height || y < 0 || y >= width        // checks boundary
        || image[x][y] < threshold || image[x][y] == newC) //check if less than threshold or is equal to zero(already visited)
        return false;
    return true;
}
// cite for floodfill https://www.geeksforgeeks.org/flood-fill-algorithm/
void MTHMAT043::PGMimageProcessor::floodFill(unsigned char **image, int height, int width, int x, int y, unsigned char threshold, int newC, std::shared_ptr<MTHMAT043::ConnectedComponent> &comp)
{
    std::queue<std::pair<int, int>> queue;

    // Append the position of starting
    // pixel of the component
    std::pair<int, int> p(x, y);
    queue.push(p);

    // Color the pixel with the new color
    image[x][y] = newC; 

    // While the queue is not empty i.e. the
    // whole component having threshold color
    // is not colored with newC color
    while (queue.size() > 0)
    {
        // Dequeue the front node
        std::pair<int, int> currPixel = queue.front();
        queue.pop();

        int posX = currPixel.first;
        int posY = currPixel.second;

        // Check if the adjacent
        // pixels are valid
        if (isValid(image, height, width, posX + 1, posY, threshold,
                    newC))
        {
            // Color with newC
            // if valid and enqueue
            image[posX + 1][posY] = newC;
            p.first = posX + 1;
            p.second = posY;
            comp->addComponent(p); //add a valid pair to the component
            queue.push(p);
        }

        if (isValid(image, height, width, posX - 1, posY, threshold,
                    newC))
        {
            image[posX - 1][posY] = newC;
            p.first = posX - 1;
            p.second = posY;
            comp->addComponent(p);//add a valid pair to the component
            queue.push(p);
        }

        if (isValid(image, height, width, posX, posY + 1, threshold,
                    newC))
        {
            image[posX][posY + 1] = newC;
            p.first = posX;
            p.second = posY + 1;
            comp->addComponent(p); //add a valid pair to the component
            queue.push(p);
        }

        if (isValid(image, height, width, posX, posY - 1, threshold,
                    newC))
        {
            image[posX][posY - 1] = newC;
            p.first = posX;
            p.second = posY - 1;
            comp->addComponent(p);//add a valid pair to the component
            queue.push(p);
        }
    }
}

int MTHMAT043::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    int count = 0;//used as a components identifier
    //The for loops are used to pass each pixle to be checked check if it is greater or equal to the threshold value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j] >= threshold )
            {
                //make a pair of the coordinates that have a pixle that meets the threshold
                std::pair<int, int> item(i, j);
                std::shared_ptr<MTHMAT043::ConnectedComponent> component_shared(new MTHMAT043::ConnectedComponent);
                //set the id of a component
                component_shared->setComponentIdentifier(count);
                //add the first pair of the component to the component array
                component_shared->addComponent(item);
                //floodfill method will return component_shared with the rest of objects.
                floodFill(image, height, width, i, j, threshold, 0, component_shared);
                //set number of pixles
                component_shared->setNumberOfPixles(component_shared->getsize());
                //check if component size is greater or equal to the minimun component size before adding it to the array
                if (component_shared->getsize() >= minValidSize)
                {
                    array->push_back(component_shared);
                }
                //after nothing an identifier for a componet increament for the next component
                count++;
                
            }
        }
    }
    return array->size();
}

int MTHMAT043::PGMimageProcessor::filterComponentsBySize(int minSize, int MaxSize)
{
    // create a new vector to move components that are within the range of the min and max size
    std::shared_ptr<std::vector<std::shared_ptr<ConnectedComponent>>> tally = std::make_shared<std::vector<std::shared_ptr<ConnectedComponent>>>();
    //loop through the entire array
    for (std::vector<std::shared_ptr<ConnectedComponent>>::iterator i = array->begin(); i != array->end(); ++i)
    {       
        //check if the componet is within the valid size 
        if (i->get()->getsize() >= minSize && i->get()->getsize() <= MaxSize)
        {
            //move the component with valid size to this vector
            tally->push_back(std::move(*i));
        }
    }
    //make the vector with components with valid size to point to the vector with valid sizes.
    array.reset();
    array = tally;
    return array->size();
}

bool MTHMAT043::PGMimageProcessor::writeComoponents(const std::string &outFilename)
{
    //populate the image with black pixles
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = 0;
        }
    }
    std::ofstream output(outFilename, std::ios::binary);
    //iterate through the vector to access the components
    for (std::vector<std::shared_ptr<ConnectedComponent>>::iterator i = array->begin(); i != array->end(); ++i)
    {
        std::shared_ptr<ConnectedComponent> component = *i;
        //loop through the pairs in the vector of the component and access the first(x) and second(y)(array co-ordinate) 
        //change them to white pixles
        for (std::pair<int, int> data : i->get()->getComponentData())
        {
            image[data.first][data.second] = 255;
        }
    }
    // write to the image's first data lines of pgm image to the output file image
    for (const std::string &str : filedata)
    {
        size_t strSize = str.size();
        output.write(str.c_str(), strSize);
        output.put('\n');
    }
    //write the image the image to the output file
    for (int i = 0; i < height; i++)
    {
        output.write(reinterpret_cast<char *>(image[i]), width);
    }
    return true;
}

int MTHMAT043::PGMimageProcessor::getComponentCount(void)const
{
    //get the size of all the components that are stored in the array
    return array->size();
}

int MTHMAT043::PGMimageProcessor::getLargestSize(void) const
{
    
    if(array.get()->empty())
    {
        return 0;
    }
    //get the size of the first component
    int initial_large = array->at(0).get()->getsize();
    if(array->size()>1)
    {
        for(int i=0;i<array->size();i++)
        {
            //get the size of the next components 
            int temp = array->at(i+1).get()->getsize();
            //compare initial_large(var) and the temp(var) if the temp is larger than initial_large then 
            //replace the size of initial_large with temp
            if(temp>initial_large)
            {
                initial_large = temp;
            }
            //to ensure that we don't access memory that we don't have access to 
            if(i == array.get()->size()-2)
            {
                break;
            }
        }
    }
    return initial_large;
}
int MTHMAT043::PGMimageProcessor::getSmallestSize(void)const
{
    
    if(array.get()->empty())
    {
        return 0;
    }
    //get the size of the first component
    int initial_small = array->at(0).get()->getsize();
    if(array->size()>1)
    {
        for(int i=0;i<array->size();i++)
        {
            //get the size of the next components 
            int temp = array->at(i+1).get()->getsize();
            //compare initial_small(var) and the temp(var) if the temp is smaller than initial_small then 
            //replace the size of initial_small with temp
            if(temp<initial_small)
            {
                initial_small = temp;
            }
            //to ensure that we don't access memory that we don't have access to 
            if(i == array.get()->size()-2)
            {
                break;
            }
        }
    }
    return initial_small;
}

void MTHMAT043::PGMimageProcessor::printComponentData(std::shared_ptr<ConnectedComponent> & theComponent)const
{
    //call the print method in the component class
    theComponent->printData(theComponent);
}
int MTHMAT043::PGMimageProcessor::getHeight()
{
    return height;
}

int MTHMAT043::PGMimageProcessor::getWidth()
{
    return width;
}
unsigned char ** MTHMAT043::PGMimageProcessor::getImage()
{
    return image;
}
std::vector<std::string> MTHMAT043::PGMimageProcessor::getFiledata()
{
    return filedata;
}
void MTHMAT043::PGMimageProcessor::setHeight(int h)
{
    height = h;
}
void MTHMAT043::PGMimageProcessor::setWidth(int w)
{
    width =w;
}
void MTHMAT043::PGMimageProcessor::setImage(unsigned char ** img)
{
    image = img;
}
void MTHMAT043::PGMimageProcessor::setFiledata(std::vector<std::string> src)
{
    filedata = src;
}
void MTHMAT043::PGMimageProcessor::TestPgmImageReader(PGMimageProcessor & rhs, std::string filename)
{
    std::ifstream myfile(filename+".pgm", std::ios::binary);
    //check if file exist
    std::string line;
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
            rhs.setHeight(height);
            rhs.setWidth(width);
            myfile >> line >> std::ws;
            filedata.push_back(line);
            rhs.setFiledata(filedata);
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
            rhs.setImage(array_2d);
            myfile.close();
        }
    }
    
}

std::shared_ptr<std::vector<std::shared_ptr<MTHMAT043::ConnectedComponent>>> MTHMAT043::PGMimageProcessor::getArray()
{
    return array;
}