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

TEST_CASE("kd_range object", "[kdtree::kd_range]") {
	vector<int> lower;
	lower.push_back(3);
	lower.push_back(10);
	vector<int> upper;
	upper.push_back(93);
	upper.push_back(50);

	SECTION("Constructor") {
			kd_range<int> r(lower, upper);

			REQUIRE(r.lower[0] == 3);
			REQUIRE(r.upper[0] == 93);
			REQUIRE(r.lower[1] == 10);
			REQUIRE(r.upper[1] == 50);
	}

	SECTION("Contains - Empty range with vector") {
		kd_range<int> r;
		bool res = r.contains(lower);

		REQUIRE(res == false);
	}

	SECTION("Contains - Empty range with kd_node") {
		kd_range<int> r;
		kd_node<int> *n = new kd_node<int>;
		n->values = lower;
		bool res = r.contains(n);

		REQUIRE(res == false);
	}

	SECTION("Contains - True - Vector") {
		kd_range<int> r(lower, upper);
		bool res = r.contains(lower);

		REQUIRE(res == true);
	}

	SECTION("Contains - True - KD_NODE") {
		kd_range<int> r(lower, upper);
		kd_node<int> *n = new kd_node<int>;
		n->values = upper;
		bool res = r.contains(n);

		REQUIRE(res == true);
	}

	SECTION("Contains - False - Vector") {
		kd_range<int> r(lower, upper);
		vector<int> v1;
		v1.push_back(100);
		v1.push_back(0);

		bool res = r.contains(v1);
		REQUIRE(res == false);
	}

	SECTION("Contains - False - KD_NODE") {
		kd_range<int> r(lower, upper);
		kd_node<int> *n = new kd_node<int>;
		vector<int> v1;
		v1.push_back(100);
		v1.push_back(0);
		n->values = v1;

		bool res = r.contains(n);
		REQUIRE(res == false);
	}


}

TEST_CASE("Range Search", "[kdtree::range]") {
	kd_tree<int> k;
	vector<int> lower;
	lower.push_back(1);
	lower.push_back(2);
	vector<int> upper;
	upper.push_back(4);
	upper.push_back(5);

	SECTION("Empty Tree") {
		vector<kd_node<int>*> res = k.range_search(lower, upper);
		REQUIRE(res.size() == 0);
	}

	SECTION("Single Result Vector") {
		k.insert(lower);
		k.insert(upper);

		lower[0] = 2;
		lower[1] = 3;

		upper[0] = 7;
		upper[1] = 10;

		vector<kd_node<int>*> res = k.range_search(lower, upper);

		REQUIRE(res.size() == 1);
		REQUIRE(res[0]->values[0] == 4);
		REQUIRE(res[0]->values[1] == 5);
	}

	SECTION("Single Result kd_range") {
		k.insert(lower);
		k.insert(upper);

		lower[0] = 2;
		lower[1] = 3;

		upper[0] = 7;
		upper[1] = 10;

		kd_range<int> r(lower, upper);
		vector<kd_node<int>*> res = k.range_search(r);

		REQUIRE(res.size() == 1);
		REQUIRE(res[0]->values[0] == 4);
		REQUIRE(res[0]->values[1] == 5);
	}

	SECTION("Single result on vector range boundary") {
		k.insert(lower);
		k.insert(upper);

		lower[0] = 2;
		lower[1] = 3;

		vector<kd_node<int>* > res = k.range_search(lower, upper);

		REQUIRE(res.size() == 1);
		REQUIRE(res[0]->values[0] == 4);
		REQUIRE(res[0]->values[1] == 5);

	}

	SECTION("No results with all coordinates out of vector range") {
		k.insert(lower);
		k.insert(upper);

		lower[0] = 7;
		lower[1] = 10;

		upper[0] = 10;
		upper[1] = 15;

		vector<kd_node<int>* > res = k.range_search(lower, upper);

		REQUIRE(res.size() == 0);
	}

	SECTION("No results with x-coordinate in vector range") {
		k.insert(lower);
		k.insert(upper);

		lower[0] = 3;
		lower[1] = 10;

		upper[0] = 10;
		upper[1] = 15;

		vector<kd_node<int>* > res = k.range_search(lower, upper);

		REQUIRE(res.size() == 0);
	}

	SECTION("Multiple results in vector range") {
		k.insert(lower);
		k.insert(upper);

		vector<int> v1;
		v1.push_back(14);
		v1.push_back(12);
		k.insert(v1);

		vector<int> v2;
		v2.push_back(8);
		v2.push_back(2);
		k.insert(v2);

		lower[0] = 1;
		lower[1] = 2;

		upper[0] = 10;
		upper[1] = 13;

		vector<kd_node<int>* > res = k.range_search(lower, upper);

		REQUIRE(res.size() == 3);
		cout << res[0]->values[0];
	}

	SECTION("Multiple results in kd_range") {
		k.insert(lower);
		k.insert(upper);

		vector<int> v1;
		v1.push_back(14);
		v1.push_back(12);
		k.insert(v1);

		vector<int> v2;
		v2.push_back(8);
		v2.push_back(2);
		k.insert(v2);

		lower[0] = 2;
		lower[1] = 2;

		upper[0] = 10;
		upper[1] = 13;

		kd_range<int> r(lower, upper);
		vector<kd_node<int>* > res = k.range_search(r);

		REQUIRE(res.size() == 2);
	}

}
