#include "AVL.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

bool compare(int k1, int k2) { return(k1 < k2 ? true : false); };
bool eqal(int k1, int k2) { return(k1 == k2 ? true : false); };
#include <algorithm>

TEST_CASE("TestEmptyAVL")
{
    cop3530::AVL<int, int, &compare, &eqal> AVLTree;
    REQUIRE(AVLTree.size() == 0);
}

TEST_CASE("TestAVL with 10 elements")
{
    cop3530::AVL<int, int, &compare, &eqal> AVLTree2;
		for (int i = 0; AVLTree2.size() != 10; ++i){
			int j = rand() % 11;
			AVLTree2.insert(j, j);
		}
		REQUIRE(AVLTree2.size() <= 10);
}

TEST_CASE("TestAVL with 10 elements and removal")
{
    cop3530::AVL<int, int, &compare, &eqal> AVLTree3;
		for (int i = 0; i < 10; ++i){
			AVLTree3.insert(i, i);
		}
		REQUIRE(AVLTree3.size() == 10);
		AVLTree3.inorder();
		std::cout << "size is: " << AVLTree3.size() << std::endl;

		for (int i = 0; i < 10; ++i) {
				AVLTree3.remove(i);
		}
		std::cout<< std::endl << "size is after removal: " << AVLTree3.size() << std::endl;
		//REQUIRE(AVLTree3.size() == 0);
}
/*
SCENARIO( "Testing AVL", "[AVL]" ) {

		GIVEN( "An AVL with several elements" ) {
			cop3530::AVL<int, int, &compare, &eqal> AVLTree;
			for (int i = 0; AVLTree.size() != 10;  ++i){
				int j = rand() % 11;
				AVLTree.insert(j, j);
			}


			WHEN( "Removing elements one at a time:" ) {
				CHECK( AVLTree.size() == 10 );
				for (int i = 0; AVLTree.size() != 0; ++i) {
					AVLTree.remove(i);
				}
					THEN( "the size goes to 0" ) {
								REQUIRE( AVLTree.size() == 0 );
					}
			}


		}
}
*/
