#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "kdtree.cpp"

TEST_CASE("Constructor Tests", "[kdtree]") {
	kd_tree k(2);
	REQUIRE(k.dimension() == 2);

	kd_tree j(-1);
	REQUIRE(k.dimension() == 2);

	kd_tree l(0);
	REQUIRE(k.dimension() == 2);	
}

TEST_CASE( "Insert Tests", "[kdtree::insert]" ){
    kd_tree k(2);
    vector<int> v;
    REQUIRE(v.size() == 0);
    v.push_back(4);
    v.push_back(5);

    SECTION("Insert w/ correct dimensions and ints") {
    	k.insert(v);
    	REQUIRE(k.size() == 1);
    }

    SECTION("Insertion of 1 element w/ wrong dimensions (3)") {
    	v.push_back(3);
    	k.insert(v);
    	REQUIRE(k.size() == 0);
    }

    SECTION("Insert empty vector") {
    	v.clear();
    	k.insert(v);
    	REQUIRE(k.size() == 0);
    }

    SECTION("Multiple Inserts") {
     	k.insert(v); // inserts on root
     	v[0]=6;
     	k.insert(v); // inserts on right
     	v[1]=5;
     	v[0]=2;
     	k.insert(v); // inserts on left
     	REQUIRE(k.size() == 3);
    }

}

TEST_CASE("NN Algorithm Tests", "[kdtree::nearest_neighbor]") {
	kd_tree k;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);

	SECTION("Empty tree") {
		vector<int> c = k.nearest_neighbor(v);
		REQUIRE(c.size() == 0);
	}
}

