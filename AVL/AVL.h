#ifndef _AVL_H_
#define _AVL_H_

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iterator>

namespace cop3530 {

	template <typename K, typename V, bool(*comp)(K, K), bool(*eq)(K, K)>
	class AVL {
		struct Node {
			int height;
			K key;
			V value;
			Node* left;
			Node* right;

			Node(K _key, V _val) :key(_key), value(_val), left(nullptr), right(nullptr)
				, height(1) {}
		};
	private:
		Node* root;
	public:
		AVL() :root(nullptr) {}

		AVL(const AVL &orig) {
			root = orig.root;
		}

		AVL& operator=(AVL orig) {                             //copy-assignment operator
			std::swap(root, orig.root);
			return *this;
		}

		AVL(AVL && orig) noexcept : root(orig.root) {     //move constructor
			orig.root = nullptr;
		}

		AVL& operator= (AVL&& orig) noexcept {                 //move assignment operator
			clear();
			root = orig.root;
			orig.root = nullptr;
			return *this;
		}
		int height(){
			return height_aux(root);
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
		~AVL() {
			clear(root);
			root = nullptr;
		}

		K max(K key1, K key2) { return comp(key1, key2) ? key2 : key1; }

		Node * rotate_right(Node * node) {
			Node * temp = node->left;
			node->left = temp->right;
			temp->right = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			temp->height = max(height(temp->left), height(temp->right)) + 1;
			return temp;
		};
		Node * rotate_left(Node * node) {
			Node * temp = node->right;
			node->right = temp->left;
			temp->left = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			temp->height = max(height(temp->left), height(temp->right)) + 1;
			return temp;
		};

		void insert(K key, V value) {
			if (!root){
				root = new Node(key, value);
			}
			else {
				root = insert_at_avl(root, key, value);
			}
		}

		void remove(K key) {
			if (is_empty())
				throw std::runtime_error("Error in BST::remove(). List is empty");
			else
					root = remove_aux(root, key);
		}

		V* contains_aux(K key) {
			Node * temp = find_node(key,root);
			if (temp)
				return &(temp->value);
			else return nullptr;
		}

		bool contains(K key) {
			if (contains_aux(key)) {
				return true;
			}
			return false;
		}

		bool is_empty() {
			if (!root)
				return true;
			return false;
		}

		bool is_full() { return false; }

		int size() { return size_aux(root); }
		int size_aux(Node * node){
			if (!node)
    		return 0;
  		else
    		return(1 + size_aux(node->left) + size_aux(node->right));
	}

		unsigned int balance() { return balance(root); }
		void inorder() { if (root) print_inorder(root); }

	private:
		void print_inorder(Node * node) {
			if (node->left)
				print_inorder(node->left);
			std::cout << node->key << "," << node->value << "-";
			if (node->right)
				print_inorder(node->right);

		}
		Node * successor(Node * node) {
			while (node->right)
				node = node->right;
			return node;
		};

		Node* insert_at_avl(Node* node, K key, V value) {
			if (!node)
				return new Node(key, value);
			if (comp(key, node->key))
				node->left = insert_at_avl(node->left, key, value);
			else if (key > node->key)
				node->right = insert_at_avl(node->right, key, value);
			else // Equal keys are not allowed in BST
				return node;

			node->height = max(height(node->left), height(node->right)) + 1;
			int bal = balance(node);


			if ((bal < -1) && (key > node->right->key))
				return rotate_left(node);
			if ((bal > 1) && (comp(key, node->left->key)))
				return rotate_right(node);

			if ((bal < -1) && (comp(key, node->right->key))) {
				node->right = rotate_right(node->right);
				return rotate_left(node);
			}
			if ((bal > 1) && (key > node->left->key)) {
				node->left = rotate_left(node->left);
				return rotate_right(node);
			}

			return node;
		}
		/////remove///////
		Node* remove_aux(Node* node, K key) {
			if (node == nullptr) return node;

			if (comp(key, node->key))
				node->left = remove_aux(node->left, key);

			else if (key > node->key)
				node->right = remove_aux(node->right, key);

				else{
	        // node with only one child or no child
	        if( (node->left == nullptr) || (node->right == nullptr) )
	        {
	           Node * temp = node->left ? node->left : node->right;
	            if (temp == nullptr) {
	                temp = node;
	                node = nullptr;
	            }
	            else{ // One child case
	             node->key = temp->key;
							 node->value = temp->value;
							 node->height = temp->height; // Copy the contents of
	             }              // the non-empty child
	            delete temp;

	        }
	        else
	        {
	            Node * temp = successor(node->right);
	            node->key = temp->key;
	            node->right = remove_aux(node->right, temp->key);
	        }
	    }
	    if (node == NULL)
	      return node;

	    node->height = 1 + max(height(node->left),
	                           height(node->right));

	    int bal = balance(node);

	    // If this node becomes unbalanced, then there are 4 cases

	    // Left Left Case
	    if (bal > 1 && balance(node->left) >= 0)
	        return rotate_right(node);

	    // Left Right Case
	    if (bal > 1 && balance(node->left) < 0)
	    {
	        node->left =  rotate_left(node->left);
	        return rotate_right(node);
	    }
				// RR
	    if (bal < -1 && balance(node->right) <= 0)
	        return rotate_left(node);

	    // Right Left Case
	    if (bal < -1 && balance(node->right) > 0)
	    {
	        node->right = rotate_right(node->right);
	        return rotate_left(node);
	    }

	    return node;
	}

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

		void clear(Node* node) {
			if (node == NULL)
				return;
			clear(node->left);
			clear(node->right);
			delete node;
		}

		unsigned int height(Node* node) {
			if (!node) {
				return 0;
			}
			return node->height;
		}

		int balance(Node* node) {
			if (!node) {
				return 0;
			}
			return height(node->left) - height(node->right);
		}

	};


}
#endif //AVL H
