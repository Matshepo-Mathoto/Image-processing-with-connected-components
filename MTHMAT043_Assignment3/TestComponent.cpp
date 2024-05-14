#define CATCH_CONFIG_MAIN// This tells catch to provide a main() function. Only do this in one cpp file
#include "catch.hpp"
#include  "ConnectedComponent.h"

TEST_CASE( "ConnectedComponent Class Unit Tests") {
    
    SECTION( "Default Constructor" ) {
        MTHMAT043::ConnectedComponent component;
        REQUIRE(component.getNumberOfPixles() == 0);
        REQUIRE(component.getComponentIdentifier() ==0);
        REQUIRE(component.getComponentData().empty() == true);
    }
    SECTION("Copy Constructor")
    {
        MTHMAT043::ConnectedComponent component;
        component.addComponent(std::pair(5,6));
        component.setComponentIdentifier(1);
        component.setNumberOfPixles(component.getComponentData().size());
        MTHMAT043::ConnectedComponent copyComponent(component);
        std::cout << copyComponent.getNumberOfPixles();
        REQUIRE(copyComponent.getNumberOfPixles() == component.getNumberOfPixles());
        REQUIRE(copyComponent.getComponentIdentifier() == component.getComponentIdentifier() );
        REQUIRE(copyComponent.getComponentData() == component.getComponentData());
    }
    SECTION("Copy Assignment Operator")
    {
        MTHMAT043::ConnectedComponent component;
        component.addComponent(std::pair(5,6));
        component.setComponentIdentifier(1);
        component.setNumberOfPixles(component.getComponentData().size());
        MTHMAT043::ConnectedComponent copyComponent;
        copyComponent = component;
        std::cout << copyComponent.getNumberOfPixles();
        REQUIRE(copyComponent.getNumberOfPixles() == component.getNumberOfPixles());
        REQUIRE(copyComponent.getComponentIdentifier() == component.getComponentIdentifier() );
        REQUIRE(copyComponent.getComponentData() == component.getComponentData());
    }
    SECTION("move Constructor")
    {
        MTHMAT043::ConnectedComponent component;
        component.addComponent(std::pair(5,6));
        component.setComponentIdentifier(1);
        component.setNumberOfPixles(1);
        std::vector< std::pair<int,int>> componentData = {std::pair(5,6)};
        MTHMAT043::ConnectedComponent copyComponent= std::move(component);
        REQUIRE(copyComponent.getNumberOfPixles() == 1);
        REQUIRE(copyComponent.getComponentIdentifier() == 1);
        REQUIRE(copyComponent.getComponentData() == componentData);
    }
    SECTION("move Assignment Operator")
    {
        MTHMAT043::ConnectedComponent component;
        component.addComponent(std::pair(5,6));
        component.setComponentIdentifier(1);
        component.setNumberOfPixles(1);
        MTHMAT043::ConnectedComponent copyComponent;
        copyComponent= std::move(component);
        REQUIRE(copyComponent.getNumberOfPixles() == 1);
        REQUIRE(copyComponent.getComponentIdentifier() == 1);
        std::vector< std::pair<int,int>> componentData = {std::pair(5,6)};
        REQUIRE(copyComponent.getComponentData() == componentData);
    }
}