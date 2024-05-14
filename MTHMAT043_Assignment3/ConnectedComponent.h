#ifndef __CONNECTEDCOMP_H
#define __CONNECTEDCOMP_H
#include <vector>
#include <string>
#include <memory>
#include <iterator>
#include <fstream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <bits/stdc++.h>
#include <utility>
namespace MTHMAT043
{
    class ConnectedComponent
    {
        
        int componentIdentifier;
        int numberOfPixles;
        std::vector< std::pair<int,int>> componentData;
        public:
        //methods
        ConnectedComponent();
        ~ConnectedComponent();
        ConnectedComponent(const ConnectedComponent &rhs);//copy constructor
        ConnectedComponent(ConnectedComponent && rhs); //move Constructor
        ConnectedComponent & operator=(const ConnectedComponent &rhs); // copy assignment constructor
        ConnectedComponent & operator=(ConnectedComponent &&rhs); //move assignmrnt
        
        //add pairs to make a components
        void addComponent(std::pair<int,int> data);
        //getter methods
        int getsize();
        std::vector< std::pair<int,int>> getComponentData();
        void setNumberOfPixles(int pixleNo);
        void setComponentIdentifier(int id);
        int getNumberOfPixles(void);
        int getComponentIdentifier(void);
        //print out the component data
        void printData(const std::shared_ptr<ConnectedComponent> &rhs)const;
    };
    
}

#endif