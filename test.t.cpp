#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
// #include "kdtree.cpp"
#include "class.cpp"

TEST_CASE( "stupid/1=2", "Prove that one equals 2" ){
    test c;
    // assert
    REQUIRE( c.add() == 1 );
}