#include "BSTRAND.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

bool compare(int k1, int k2) { return(k1 < k2 ? true : false); }
bool eqal(int k1, int k2) { return(k1 == k2 ? true : false); }


SCENARIO( "Testing BSTRAND", "[BSTRAND]" ) {


		GIVEN( "An empty BSTRAND" ) {
		cop3530::BSTRAND<int, int, &compare, &eqal> randTree;
		REQUIRE(randTree.size() == 0);

		WHEN("10 elements are inserted randomly"){
			for (int i = rand() % 10; randTree.size() != 10; i = rand() % 10)
				randTree.insert(i, i);
			THEN("size will increase to 10")
				REQUIRE(randTree.size() == 10);
			randTree.inorder();
		}

		WHEN("Removing one elements at a time:"){
			for (int i = 0; i < 10; ++i) {
				if(randTree.contains(i))
					randTree.remove(i);

			}
			std::cout << std::endl;
				THEN("Size will go to 0")
					REQUIRE(randTree.size() == 0);
				randTree.inorder();
		}

		WHEN("Inserting random values from 0 - 100 until size is 50: "){
			for(int i = rand() % 100; randTree.size() != 50; i = rand() % 100){
				std::cout << "Inserting: " << i << "-" << i << std::endl;
				randTree.insert(i, i);
			}
				std::cout << std::endl;
				THEN("Size will go to 50")
					REQUIRE(randTree.size() == 50);
				std::cout << "Printing tree in order:" << std::endl;
				randTree.inorder();
		}
		WHEN("Looking up values for keys that exist: "){
			for(int i = 0; i < 100 ; ++i){
				if(randTree.contains(i)){
					THEN("item is found")
						REQUIRE(*(randTree.contains(i)) == i);
				}
			}
		}
		WHEN("Removing all elements from 0 to 99"){
			for(int i = 0; i < 100 ; ++i){
				if(randTree.contains(i)){
					randTree.remove(i);
					std::cout << "Just removed" << i << std::endl;
				}
				THEN("Size will go to 0")
					REQUIRE(randTree.size() == 0);
			}
		}
		std::cout <<  std::endl;
		randTree.inorder();
		std::cout << std::endl;
	}
}
