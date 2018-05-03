#ifndef _BSTLEAF_H_
#define _BSTLEAF_H_

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iterator>
namespace cop3530{

template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
class BSTLEAF {

public:
	struct Node {
		Node() :right(nullptr), left(nullptr) {}
		Node(K _key, V val) :key(_key), value(val), right(nullptr), left(nullptr){}
		K key;
		V value;
		Node * right;
		Node * left;
	};

	BSTLEAF() :root(nullptr) {};
	BSTLEAF(const BSTLEAF& orig) {};

	Node * find_node(K key, Node * node) {
		if (!node)
			return nullptr;
		else if (key == node->key)
			return node;
		else if (comp(key, node->key))
			return find_node(key, node->left);
		else
			return find_node(key, node->right);
	};
	void insert(K key, V value);
	void remove(K key);
	Node * remove_aux(Node * node, K key) {
		if (node == NULL) return node;

		if (comp(key, node->key))
			node->left = remove_aux(node->left, key);

		else if (key > node->key)
			node->right = remove_aux(node->right, key);

		else{
			// node with only one child or no child
			if (node->left == NULL){
				Node * temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == NULL){
				Node * temp = node->left;
				delete node;
				return temp;
			}
			Node * temp = successor(node->right);
			node->key = temp->key;
			node->right = remove_aux(node->right, temp->key);
		}
		return node;
	}
	int height(){
		return height_aux(root);
	}
	int balance(){
		return balance_aux(root);
	}
	int height_aux(Node* node) {
   if (node==nullptr)
       return 0;
   else{
       int l = height_aux(node->left);
       int r = height_aux(node->right);
       if (l > r)
           return(l+1);
       else return(r+1);
   }
	}
	int balance_aux(Node* node) {
   if (node==nullptr){}
	 else
	 	return(height(node->left) - height(node->right));
	}
	Node * successor(Node * node) {
		while (node->right)
			node = node->right;
		return node;
	};

	V* contains(K key);

	bool is_empty() { return (root ? false : true); }
	bool is_full() { return false; }
	bool is_leaf(Node * node) { return ((!node->right && !node->left) ? false : true); }
  void inorder(void){ if (root) print_inorder(root);};
	unsigned int size();
	void clear(Node * node);
	~BSTLEAF() { clear(root); }
public:

//--------------------------------------------------
// type aliases
//--------------------------------------------------
//using size_t = std::size_t; // you may comment out this line if your compiler complains
//using key_type = the key type template paramter name;
//using value_type = the value type template paramter name;
//using iterator = XXX_Iter<key_type, value_type>;
//using const_iterator = XXX_Iter<key_type, value_type const>;


private:

	Node * root;
	//typedef
	unsigned int size_aux(Node * node);
	void insert_at_leaf(K key, V val, Node *& node);
	void print_inorder(Node * root);

};
template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
void
BSTLEAF<K, V, comp, eq>::print_inorder(Node * node)
{
	if (node->left)
		print_inorder(node->left);
	std::cout << node->key << "," << node->value << "-";
	if (node->right)
		print_inorder(node->right);

}
//template <typename K, typename V, bool (*comp)(K,K), bool (*eq)(K,K)>
//struct BSTLEAF<K, V, bool (*comp)(K,K), bool (*eq)(K,K)>::Node


template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
V*
BSTLEAF<K, V, comp, eq>::contains(K key) {
	Node * temp = find_node(key, root);
	if (temp)
		return &(temp->value);
	else return nullptr;
};
//////////////////////////insert//////////////////////////
template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
void
BSTLEAF<K, V, comp, eq>::clear(Node * node)
{
	if (node == NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
}
//////////////////////////insert//////////////////////////
template <typename K, typename V, bool(* comp)(K, K), bool(* eq)(K, K)>
void
BSTLEAF<K, V, comp, eq>::insert_at_leaf(K key, V val, Node*& node)
{
	if (!node) {
		node = new Node;
		node->key = key;
		node->value = val;
		return;
	}
	if (comp(key, node->key))
		insert_at_leaf(key, val, node->left);
	else
		insert_at_leaf(key, val, node->right);
};
//////////////////////map ins////////////////////////////
template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
void
BSTLEAF<K, V, comp,eq>::insert(K key, V value) {
	Node * temp;
	if (temp = find_node(key,root))
		temp->value = value;
	else if (root)
		insert_at_leaf(key, value, root);
	else
		root = new Node(key, value);

}
template<typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
void
BSTLEAF<K, V, comp, eq>::remove(K key)
{
	if (is_empty())
		throw std::runtime_error("Error in BST::remove(). List is empty");
	else
		root = remove_aux( root, key);
}
//////////////////remove/////////////////////

//////////////////remove/////////////////////


///////////////clear////////////////

template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
unsigned int
BSTLEAF<K, V, comp, eq>::size()
{
	int size = 0;
	if (is_empty())
		return size;
	return size_aux(root);
}
template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
unsigned int
BSTLEAF<K, V,comp, eq>::size_aux(Node * node)
{
	if (!node)
		return 0;
	else
		return 1 + size_aux(node->left) + size_aux(node->right);
}
}
#endif
//end cop3530
