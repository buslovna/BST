#include "BSTLEAF.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

bool compare(int k1, int k2) { return(k1 < k2 ? true : false); }
bool eqal(int k1, int k2) { return(k1 == k2 ? true : false); }


SCENARIO( "Testing BSTLeaf", "[BSTLeaf]" ) {


		GIVEN( "An empty BSTLeaf" ) {
		cop3530::BSTLEAF<int, int, &compare, &eqal> leafTree;
		REQUIRE(leafTree.size() == 0);

		WHEN("10 elements are inserted randomly"){
			for (int i = rand() % 10; leafTree.size() != 10; i = rand() % 10)
				leafTree.insert(i, i);
			THEN("size will increase to 10")
				REQUIRE(leafTree.size() == 10);
			leafTree.inorder();
		}

		WHEN("Removing one elements at a time:"){
			for (int i = 0; i < 10; ++i) {
				if(leafTree.contains(i))
					leafTree.remove(i);

			}
			std::cout << std::endl;
				THEN("Size will go to 0")
					REQUIRE(leafTree.size() == 0);
				leafTree.inorder();
		}

		WHEN("Inserting random values from 0 - 100 until size is 50: "){
			for(int i = rand() % 100; leafTree.size() != 50; i = rand() % 100){
				std::cout << "Inserting: " << i << "-" << i << std::endl;
				leafTree.insert(i, i);
			}
				std::cout << std::endl;
				THEN("Size will go to 50")
					REQUIRE(leafTree.size() == 50);
				std::cout << "Printing tree in order:" << std::endl;
				leafTree.inorder();
		}

		WHEN("Looking up values for keys that exist: "){
			for(int i = 0; i < 100 ; ++i){
				if(leafTree.contains(i)){
					THEN("item is found")
						REQUIRE(*(leafTree.contains(i)) == i);
				}
			}
		}
		WHEN("Removing all elements from 0 to 99"){
			for(int i = 0; i < 100 ; ++i){
				if(leafTree.contains(i)){
					leafTree.remove(i);
					std::cout << "Just removed" << i << std::endl;
				}
				THEN("Size will go to 0")
					REQUIRE(leafTree.size() == 0);
			}
		}
		std::cout <<  std::endl;
		leafTree.inorder();
		std::cout << std::endl;
	}
}
