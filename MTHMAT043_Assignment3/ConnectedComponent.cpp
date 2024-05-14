#include "ConnectedComponent.h"
//Class constructors
MTHMAT043::ConnectedComponent::ConnectedComponent(void)
{}
MTHMAT043::ConnectedComponent::~ConnectedComponent()
{}
MTHMAT043::ConnectedComponent::ConnectedComponent(const ConnectedComponent &rhs):componentIdentifier(rhs.componentIdentifier), numberOfPixles(rhs.numberOfPixles),componentData(rhs.componentData)
{
}
MTHMAT043::ConnectedComponent::ConnectedComponent(ConnectedComponent && rhs):componentIdentifier(std::move(rhs.componentIdentifier)), numberOfPixles(std::move(rhs.numberOfPixles)), componentData(std::move(rhs.componentData))
{
}
MTHMAT043::ConnectedComponent & MTHMAT043::ConnectedComponent::operator=(const ConnectedComponent &rhs)
{
    if(this!=&rhs)
    {
        componentIdentifier = rhs.componentIdentifier;
        numberOfPixles = rhs.numberOfPixles;
        componentData = rhs.componentData;
    }
    return *this;
}
MTHMAT043::ConnectedComponent & MTHMAT043::ConnectedComponent::operator=(ConnectedComponent &&rhs)
{
    if(this!=&rhs)
    {
        componentIdentifier = std::move(rhs.componentIdentifier);
        numberOfPixles = std::move(rhs.numberOfPixles);
        componentData = std::move(rhs.componentData);
    }
    return *this;
}
//method to add to the array
void MTHMAT043::ConnectedComponent::addComponent(std::pair<int,int> data)
{
    componentData.push_back(data);
}
//variables getter and setter methods
int MTHMAT043::ConnectedComponent::getsize()
{
    return componentData.size();
}

void MTHMAT043::ConnectedComponent::setNumberOfPixles(int pixleNo)
{
    numberOfPixles = pixleNo;
}
 
 void MTHMAT043::ConnectedComponent::setComponentIdentifier(int id)
 {
    componentIdentifier = id;
 }

int MTHMAT043::ConnectedComponent::getNumberOfPixles()
{
    return numberOfPixles;
}
 
 int MTHMAT043::ConnectedComponent::getComponentIdentifier()
 {
    return componentIdentifier;
 }
 std::vector< std::pair<int,int>> MTHMAT043::ConnectedComponent::getComponentData()
 {
    return componentData;
 }
//method to print out cmponent data
void  MTHMAT043::ConnectedComponent::printData(const std::shared_ptr<ConnectedComponent> &rhs)const
{
    std::cout << rhs->componentIdentifier << " " << rhs->numberOfPixles;
}