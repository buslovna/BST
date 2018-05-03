#ifndef _BSTROOT_H_
#define _BSTROOT_H_

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iterator>

namespace cop3530 {

	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	class BSTROOT {

	public:
		BSTROOT() :root(nullptr) {}
		BSTROOT(const BSTROOT& orig) {}
		struct Node {
			Node() :right(nullptr), left(nullptr) {}
			Node(K _key, V val) :key(_key), value(val), right(nullptr), left(nullptr) {}
			K key;
			V value;
			Node * right;
			Node * left;
		};
		unsigned int size();

		Node * insert_at_root(K key, V val, Node * node) {
			if (node == nullptr) return new Node(key, val);
			if (comp(key, node->key)) {
				node->left = insert_at_root(key, val, node->left);
				node = rotate_right(node);
			}
			else {
				node->right = insert_at_root(key, val, node->right);
				node = rotate_left(node);
			}
			return node;
		};

		Node * insert_at_leaf(K key, V val, Node * node) {
			if (!node) {
				node = new Node;
				node->key = key;
				node->value = val;
				return node;
			}
			if (comp(key, node->key))
				return insert_at_leaf(key, val, node->left);
			else
				return insert_at_leaf(key, val, node->right);
		}


		Node * rotate_right(Node * node) {
			Node * temp = node->left;
			node->left = temp->right;
			temp->right = node;
			return temp;
		};
		Node * rotate_left(Node * node)
		{
			Node * temp = node->right;
			node->right = temp->left;
			temp->left = node;
			return temp;
		};

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

		Node * successor(Node * node) {
			while (node->right)
				node = node->right;
			return node;
		};

		V* contains(K key) {
			Node * temp = find_node(key, root);
			if (temp)
				return &(temp->value);
			else return nullptr;
		}

		void inorder(void) { if (root) print_inorder(root); };
		bool is_empty() { return (root ? false : true); }
		bool is_leaf(Node * node) { return ((!node->right && !node->left) ? false : true); }
		bool compare(K k1, K k2) { return(k1 < k2 ? true : false); }
		void clear(Node * node);
		~BSTROOT() { clear(root); }

	private:
		Node * root;
		//typedef
		void print_inorder(Node * root);
		unsigned int size_aux(Node * node);

	};
	//////////////////////////insert//////////////////////////
	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	void
		BSTROOT<K, V, comp, eq>::clear(Node * node)
	{
		if (node == NULL)
			return;
		clear(node->left);
		clear(node->right);
		delete node;
	}
	//////////////////right rotate//////////////////
	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	void
		BSTROOT<K, V, comp, eq>::print_inorder(Node * node)
	{
		if (node->left)
			print_inorder(node->left);
		std::cout << node->key << "," << node->value << "-";
		if (node->right)
			print_inorder(node->right);

	}
	//////////////////left rotate//////////////////

	///////////////////////////insert at root////////////////

	///////////////////////////insert////////////////////////
	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	void
		BSTROOT<K, V, comp, eq>::insert(K key, V value) {
		Node * temp;
		if (temp = find_node(key, root))
			temp->value = value;
		else
			root = insert_at_root(key, value, root);
	}
	///////////////clear////////////////

	//////////////////remove/////////////////////

	//////////////////remove/////////////////////
	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	void
		BSTROOT<K, V, comp, eq>::remove(K key) {
		if (is_empty())
			throw std::runtime_error("Error in BST::remove(). List is empty");
		else
			root = remove_aux(root, key);
	}

	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	unsigned int
		BSTROOT<K, V, comp, eq>::size() {
		int size = 0;
		if (is_empty())
			return size;
		return size_aux(root);
	}
	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	unsigned int
		BSTROOT<K, V, comp, eq>::size_aux(Node * node)
	{
		if (!node)
			return 0;
		else
			return 1 + size_aux(node->left) + size_aux(node->right);
	}


}//end cop3530
#endif
