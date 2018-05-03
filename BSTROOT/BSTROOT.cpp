#include "BSTROOT.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

bool compare(int k1, int k2) { return(k1 < k2 ? true : false); }
bool eqal(int k1, int k2) { return(k1 == k2 ? true : false); }


SCENARIO( "Testing BSTROOT", "[BSTROOT]" ) {


		GIVEN( "An empty BSTROOT" ) {
		cop3530::BSTROOT<int, int, &compare, &eqal> rootTree;
		REQUIRE(rootTree.size() == 0);

		WHEN("10 elements are inserted randomly"){
			for (int i = rand() % 10; rootTree.size() != 10; i = rand() % 10)
				rootTree.insert(i, i);
			THEN("size will increase to 10")
				REQUIRE(rootTree.size() == 10);
			rootTree.inorder();
		}

		WHEN("Removing one elements at a time:"){
			for (int i = 0; i < 10; ++i) {
				if(rootTree.contains(i))
					rootTree.remove(i);

			}
			std::cout << std::endl;
				THEN("Size will go to 0")
					REQUIRE(rootTree.size() == 0);
				rootTree.inorder();
		}

		WHEN("Inserting random values from 0 - 100 until size is 50: "){
			for(int i = rand() % 100; rootTree.size() != 50; i = rand() % 100){
				std::cout << "Inserting: " << i << "-" << i << std::endl;
				rootTree.insert(i, i);
			}
				std::cout << std::endl;
				THEN("Size will go to 50")
					REQUIRE(rootTree.size() == 50);
				std::cout << "Printing tree in order:" << std::endl;
				rootTree.inorder();
		}
		WHEN("Looking up values for keys that exist: "){
			for(int i = 0; i < 100 ; ++i){
				if(rootTree.contains(i)){
					THEN("item is found")
						REQUIRE(*(rootTree.contains(i)) == i);
				}
			}
		}
		WHEN("Removing all elements from 0 to 99"){
			for(int i = 0; i < 100 ; ++i){
				if(rootTree.contains(i)){
					rootTree.remove(i);
					std::cout << "Just removed" << i << std::endl;
				}
				THEN("Size will go to 0")
					REQUIRE(rootTree.size() == 0);
			}
		}
		std::cout <<  std::endl;
		rootTree.inorder();
		std::cout << std::endl;
	}
}
