#ifndef YACRAFT_DATATYPES_BIARRAY
#define YACRAFT_DATATYPES_BIARRAY

#include <iostream>

template<class Type>
struct BiArrayNode {
	Type* value = nullptr;
	BiArrayNode* left = nullptr;
	BiArrayNode* right = nullptr;
};

template<class Type>
class BiArray {
private:
	BiArrayNode<Type>* root;

	BiArrayNode<Type>* traverse(int index) {
		BiArrayNode<Type>* current = root;
		while (index != 0) {
			if (index > 0) {
				--index;
				if (current->right == nullptr) {
					current->right = new BiArrayNode<Type>;
				}
				current = current->right;
			}
			else if (index < 0) {
				++index;
				if (current->left == nullptr) {
					current->left = new BiArrayNode<Type>;
				}
				current = current->left;
			}
		}
		return current;
	}
public:
	BiArray() {
		root = new BiArrayNode<Type>;
	}

	Type& get(int index) {
		return *traverse(index)->value;
	}

	void set(int index, Type value) {
		BiArrayNode<Type>* node = traverse(index);
		if(node->value == nullptr){
			node->value = new Type;
		}
		*node->value = value;
	}

	void set(int index, Type* ptr){
		BiArrayNode<Type>* node = traverse(index);
		node->value = ptr;
	}

	template<class... Args>
	void initSet(int index, Args... args) {
		traverse(index)->value = new Type(args...);
	}

	bool isExist(int index) {
		BiArrayNode<Type>* current = root;
		while (index != 0) {
			if (index > 0) {
				--index;
				if (current->right == nullptr) {
					return false;
				}
				current = current->right;
			}
			else if (index < 0) {
				++index;
				if (current->left == nullptr) {
					return false;
				}
				current = current->left;
			}
		}
		return current->value != nullptr;
	}
};

#endif