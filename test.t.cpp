#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "kdtree.cpp"

TEST_CASE("Constructor Tests", "[kdtree]") {
	kd_tree <int> k(2);
	REQUIRE(k.dimension() == 2);

	kd_tree <int> j(-1);
	REQUIRE(k.dimension() == 2);

	kd_tree <int> l(0);
	REQUIRE(k.dimension() == 2);
}

TEST_CASE( "Insert Tests", "[kdtree::insert]" ){
    kd_tree <int> k(2);
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

TEST_CASE("Search Tests", "[kdtree::search]") {
	kd_tree <int> k(2);
	vector<int> s;
	s.push_back(5);
	s.push_back(4);
	vector<int> s2;
	s2.push_back(2);
	s2.push_back(2);

	SECTION("Empty Tree") {
		kd_node<int> *result = k.search(s);
		REQUIRE(result == 0);
	}

	vector<int> v;
	v.push_back(2);
	v.push_back(4);
	vector<int> v1;
	v1.push_back(5);
	v1.push_back(4);

	k.insert(v);
	k.insert(v1);

	SECTION("No match - same first term") {
		kd_node<int> *result = k.search(s2);

		REQUIRE(result == 0);
	}

	SECTION("No match - no matching terms") {
		vector<int> s3;
		s3.push_back(17);
		s3.push_back(18);
		kd_node<int> *result = k.search(s3);

		REQUIRE(result == 0);
	}

	SECTION("Match - leaf node") {
		kd_node<int> *result = k.search(s);

		REQUIRE(result->values[0] == 5);
		REQUIRE(result->values[1] == 4);
	}

	SECTION("Match - root node") {
		kd_node<int> *result = k.search(v);

		REQUIRE(result->values[0] == 2);
		REQUIRE(result->values[1] == 4);
	}
}

TEST_CASE("NN Algorithm Tests", "[kdtree::nearest_neighbor]") {
	kd_tree<int> k;
	vector<int> v;
	v.push_back(1);
	v.push_back(2);

	SECTION("Empty tree") {
		kd_node<int> *c = k.nearest_neighbor(v);
		REQUIRE(c == 0);
	}


	SECTION("NN vector search w/ kd_tree.size() == 1") {
		k.insert(v);
		vector<int> c;
		c.push_back(2); c.push_back(3);
		kd_node<int> *d = k.nearest_neighbor(c);
		REQUIRE(d->values[0] == v[0]);
		REQUIRE(d->values[1] == v[1]);
	}

	SECTION("NN vector search where NN node itself") {
		kd_node<int> *d = k.nearest_neighbor(v);
		REQUIRE(d == 0);
	}

	SECTION("NN vector search where leaf is NN") {
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
		kd_node<int> *d = k.nearest_neighbor(c);

		REQUIRE(d->values[0] == 3);
		REQUIRE(d->values[1] == 3);

	}

	SECTION("NN vector search where root is NN") {
		vector<int> c;
		c.push_back(1); c.push_back(2);
		k.insert(c);

		c[0] = 4; c[1] = 2; // right
		k.insert(c);

		c[0] = 8; c[1] = 5; // right, right
		k.insert(c);

		c[0] = 9; c[1] = 10; // right, right, right
		k.insert(c);

		c[0] = 9; c[1] = 2; // right, right, right, left
		k.insert(c);

		c[0] = 3; c[1] = 3; // right, right, left
		k.insert(c);

		c[0] = 1; c[1] = 1;
		kd_node<int> *d = k.nearest_neighbor(c); // should be 1,2

		REQUIRE(d->values[0] == 1);
		REQUIRE(d->values[1] == 2);
	}

	SECTION("NN vector search where NN is non leaf or root") {
		vector<int> c;
		c.push_back(1); c.push_back(2);
		k.insert(c);

		c[0] = 4; c[1] = 2; // right
		k.insert(c);

		c[0] = 8; c[1] = 5; // right, right
		k.insert(c);

		c[0] = 9; c[1] = 10; // right, right, right
		k.insert(c);

		c[0] = 9; c[1] = 2; // right, right, right, left
		k.insert(c);

		c[0] = 3; c[1] = 3; // right, right, left
		k.insert(c);

		c[0] = 7; c[1] = 5;
		kd_node<int> *d = k.nearest_neighbor(c); // should be 8,5

		REQUIRE(d->values[0] == 8);
		REQUIRE(d->values[1] == 5);
	}

	SECTION("NN vector search switching subtrees from left to right") {
		vector<int> c;
		c.push_back(4); c.push_back(5);
		k.insert(c); // root

		c[0] = 2; c[1] = 6; // left
		k.insert(c);

		c[0] = 5; c[1] = 10; // right
		k.insert(c);

		c[0] = 4; c[1] = 1; // right, left
		k.insert(c);

		c[0] = 3; c[1] = 3; // left, left
		k.insert(c);

		c[0] = 2; c[1] = 8; // left, right
		k.insert(c);

		c[0] = 3; c[1] = 1; // should be closest to 4,1
		kd_node<int> *d = k.nearest_neighbor(c);

		REQUIRE(d->values[0] == 4);
		REQUIRE(d->values[1] == 1);
	}

	SECTION("NN node search switching subtrees from left to right") {
		vector<int> c;
		c.push_back(4); c.push_back(5);
		k.insert(c); // root

		c[0] = 2; c[1] = 6; // left
		k.insert(c);

		c[0] = 5; c[1] = 10; // right
		k.insert(c);

		c[0] = 4; c[1] = 1; // right, left
		k.insert(c);

		c[0] = 3; c[1] = 3; // left, left
		k.insert(c);

		c[0] = 2; c[1] = 8; // left, right
		k.insert(c);
		kd_node<int> *res = k.search(c);

		kd_node<int> *d = k.nearest_neighbor(res);

		REQUIRE(d->values[0] == 2);
		REQUIRE(d->values[1] == 6);
	}

}
