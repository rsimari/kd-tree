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

	SECTION("NN search w/ kd_tree.size() == 1") {
		k.insert(v);
		vector<int> c;
		c.push_back(2); c.push_back(3);
		vector<int> d = k.nearest_neighbor(v);
		REQUIRE(d[0] == v[0]);
		REQUIRE(d[1] == v[1]);
	}

	SECTION("NN search w/ recursing to a leaf and back to root, leaf is NN") {
		vector<int> c;
		c.push_back(4); c.push_back(5); 
		k.insert(c); // root

		c[0] = 2; c[1] = 6; // left
		k.insert(c);

		c[0] = 6; c[1] = 5; // right
		k.insert(c);

		c[0] = 3; c[1] = 3; // left, left
		k.insert(c);

		c[0] = 2; c[1] = 8; // left, right
		k.insert(c);

		c[0] = 3; c[1] = 1; // should be closest to 3,3 ?
		vector<int> d = k.nearest_neighbor(c);

		REQUIRE(d[0] == 3);
		REQUIRE(d[1] == 3);
	}
}

