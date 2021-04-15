#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>

#include "word.h"

//forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

template <class DataType>
class treeNode {

	friend class binarySearchTree<DataType>;

	private:

		DataType key; 
		treeNode<DataType> *leftNode;
		treeNode<DataType> *rightNode;

	public:

		//constructors
		treeNode() {
			rightNode = nullptr;
			leftNode = nullptr;
		}
		treeNode(const DataType &nodeKey, treeNode *left, treeNode *right) {
			key = nodeKey;
			leftNode = left;
			rightNode = right;
		}
};

template <class DataType>
class binarySearchTree {

	private:

		treeNode<DataType> *root; 
		int numNodes;

	public:
		
		//constructors
		binarySearchTree();
		binarySearchTree(const binarySearchTree &other);

		//destructor
		virtual ~binarySearchTree();

		void destroy(treeNode<DataType>* &p);

		//the empty member function will return true if the binary tree is empty
		bool empty() const;

		//returns the number of items in the binary tree
		std::size_t size() const;

		//display the contents of the binary tree in order by key (inorder traversal) 
		//whatever is being stored in the binary will have to have overload the operator<< operator
		void print() const;
		
		//Display the contents of the binary tree for debugging purposes. 
		//Use whatever traversal algorithm makes sense to you. 
		//Make sure you output the left and right pointers from the treeNode. 
		//Do this for all nodes in the binary tree. 
		void debug(std::ostream &out) const;

		//The first parameter passed to the find member function is the item we are looking for. The second parameter is the address of a function that will be called if the searchItem is found in the binary tree collection. The found item is passed to the function. If the item is found, the function is called, and the find member function will return true. 
		//If the item is not found, the function is not called, and find returns false. 
		bool find(const DataType &searchItem, void(*foundNode)(const DataType&));

		static void processFound(const DataType &item);

		//The erase member function will remove the specified item from the binary tree (if it finds the entry in the tree) 
		//The erase member function will return true if the item was found and removed and false if it was not found. 
		bool erase(const DataType &deleteItem);

		//insert the item into the binary tree. if the entry already exists it should be replaced by the new one
		void insert(const DataType &newItem);

		//Insert the item into the binary tree. If the item already exists the duplicateItemFound function will be called. 
		//This is the function passed as the 2nd parameter to the insert function. Note this must either be a stand-alone function or a static member function. 
		//The signature of the function is as follows (the function name can be different):
		void insert(const DataType &newItem, void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem));

		//will get a modifiable version of the found item (existingItem) and a const reference to the new item. 
		//You can update the existingItem as needed in the update function. 
		static void update(DataType &existingItem, const DataType &newItem);

		//The traverse function will do an inorder traversal of the binary tree. 
		//For every item found it will call the itemFound function and pass it a const reference to the found item. 
		void traverse(void(*itemFound)(const DataType &foundItem)) const;



		void printTree(treeNode<DataType> *node) const;

		void copyTree(treeNode<DataType> *&newCopyTree, treeNode <DataType> *originalCopyTree);

		void deleteFromTree(treeNode<DataType>* &p);


		//inorder traversal for traverse member function
		void inorder(treeNode<DataType>* p, void(*visit) (const DataType& item)) const;
		
		void inorder2(treeNode<DataType>* p, std::ostream &outstream, void(*visit) (const treeNode<DataType>* node, std::ostream &out)) const;


};

//constructors
template <class DataType> 
binarySearchTree<DataType>::binarySearchTree() {

	root = nullptr;
	numNodes = 0;
}

//copy constructor
template <class DataType>
binarySearchTree<DataType>::binarySearchTree(const binarySearchTree &other) {

	//if empty just set root to empty
	if (other.root == nullptr) {
		root = nullptr;
	}
	//call the copyTree function
	else {
		copyTree(root, other.root);
		numNodes = other.numNodes;
	}

}

//destructor
template <class DataType> 
binarySearchTree<DataType>::~binarySearchTree() {

	while (!empty()) {
		deleteFromTree(root);
	}
	
}

//checks to see if the tree is empty or not
template <class DataType>
bool binarySearchTree<DataType>::empty() const {

	if (root == nullptr) {
		return true;
	}
	else {
		return false;
	}

}

//destroy the whole subtree
template <class DataType>
void binarySearchTree<DataType>::destroy(treeNode<DataType>* &p) {

	if (p != nullptr) {

		numNodes--;
		destroy(p->leftNode);
		destroy(p->rightNode);

		delete p;

		p = nullptr;
	}
}

template <class DataType> 
void binarySearchTree<DataType>::processFound(const DataType &item) {
}

//returns the numNodes
template <class DataType>
std::size_t binarySearchTree<DataType>::size() const {

	return numNodes;

}

//recursive copy of the tree
template <class DataType> 
void binarySearchTree<DataType>::copyTree(treeNode<DataType>* &newCopyTree, treeNode<DataType>* originalCopyTree) {

	//if empty
	if (originalCopyTree == nullptr) {
		newCopyTree == nullptr;
	}

	else {
		newCopyTree = new treeNode<DataType>;

		//copies the key 
		newCopyTree->key = originalCopyTree->key;

		//recursive calls to copy each subtree
		copyTree(newCopyTree->leftNode, originalCopyTree->leftNode);
		copyTree(newCopyTree->rightNode, originalCopyTree->rightNode);
	}

}

//print contents of the tree
template <class DataType>
void binarySearchTree<DataType>::print() const {

	if (root == nullptr) {
		return;
	}
	else {
		printTree(root);
	}

}

//to use in print function
template <class DataType>
void binarySearchTree<DataType>::printTree(treeNode<DataType> *node) const {
	
	if (node == nullptr) {
		return;
	}

	else {

		printTree(node->leftNode);
		std::cout << node->key << std::endl;
		printTree(node->rightNode);

	}
}

template <class DataType>
void binarySearchTree<DataType>::debug(std::ostream &out) const {

}

//returns true if the node was found, false if not found
template <class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem, void(*foundNode)(const DataType&)) {
	
	treeNode<DataType> *currentNode;

	bool found = false;

	//if tree is empty
	if (root == nullptr) {
		return found;
	}

	else {

		//start at the root
		currentNode = root;

		while (currentNode != nullptr) {

			//if the item searching for is greater than current, look right
			if (currentNode->key < searchItem) {

				//if the right doesn't exist, then it wasnt found
				if (currentNode->rightNode == nullptr) {
					return found;
				}
				//move on if the right does exist
				currentNode = currentNode->rightNode;

			}

			//if the key doesn't match the searchItem and the searchItem is less than the current, go left
			else if (currentNode->key > searchItem) {

				//if the left doesnt exist, then it wasnt found
				if (currentNode->leftNode == nullptr) {
					return found;
				}
				//else move on
				currentNode = currentNode->leftNode;
			}
			
			//if the searchItem key is same as currentNode key
			else {
				
				found = true;
				return found;
			}

		}
		return false;
	}


}

//deletes an item 
template <class DataType>
bool binarySearchTree<DataType>::erase(const DataType &deleteItem) {

	treeNode<DataType> *currentNode; 
	treeNode<DataType> *trailCurrentNode;
	bool found = false;

	//if the tree is empty
	if (root == nullptr) {
		return false;
	}

	//if the tree is not empty
	else {

		currentNode = root;
		trailCurrentNode = root;

		while (currentNode != nullptr && found == false) {

			if (currentNode->key == deleteItem) {
				found = true;
			}

			else {

				trailCurrentNode = currentNode;

				if (currentNode->key > deleteItem) {
					currentNode = currentNode->leftNode;
				}
				else {
					currentNode = currentNode->rightNode;
				}

			}

		}

		//if the loop ends and currentNode is nullptr (meaning it wasn't set to anything)
		if (currentNode == nullptr) {
			return false;
		}
		
		//if the item to be deleted was found
		else if (found == true) {

			if (currentNode == root) {
				deleteFromTree(root);
			}
			else {
				deleteFromTree(currentNode);
			}

			return true;

		}

		return false;
	}
}

//deletes an item
template <class DataType>
void binarySearchTree<DataType>::deleteFromTree(treeNode<DataType>* &p) {

	treeNode<DataType> *currentNode;
	treeNode<DataType> *trailCurrentNode; 
	treeNode<DataType> *temp;

	//if empty
	if (p == nullptr) {
		return;
	}
	
	//if the left and right nodes of p are nullptr
	else if (p->leftNode == nullptr && p->rightNode == nullptr) {

		//prep to be deleted 
		temp = p;

		//set p to nullptr
		p = nullptr;

		//actually delete the memory
		delete temp;
		numNodes--;

	}

	//if the leftNode is nullptr
	else if (p->leftNode == nullptr) {

		temp = p;
		p = temp->rightNode;
		delete temp;
		numNodes--;

	}

	//if the rightNode is nullptr
	else if (p->rightNode == nullptr) {

		temp = p;
		p = temp->leftNode;
		delete temp;
		numNodes--;

	}

	//if neither the left nor the right are empty
	else {


		currentNode = p->leftNode;
		trailCurrentNode = nullptr;
		
		//loop through until you cant go right anymore in the tree
		while (currentNode->rightNode != nullptr) {

			trailCurrentNode = currentNode; 
			currentNode = currentNode->rightNode; 

		}

		//set the key to the key found in the node
		p->key = currentNode->key;

		if (trailCurrentNode == nullptr) {
			p->leftNode = currentNode->leftNode;
		}
		else {
			trailCurrentNode->rightNode = currentNode->leftNode;
		}

		delete currentNode;
	}

	numNodes--;
}

//insert a node
template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem) {

	treeNode<DataType> *currentNode; 

	treeNode<DataType> *newNode; 
	newNode = new treeNode<DataType>;
	newNode->key = newItem;
	newNode->leftNode = nullptr;
	newNode->rightNode = nullptr;

	//if inserting into an empty tree
	if (root == nullptr) {

		root = newNode;
		numNodes++;
		return;
	}

	else {

		currentNode = root;

		while (currentNode != nullptr) {
			
			//if the newItem's key is more than the currentNode's key, look right
			if (currentNode->key < newItem) {

				//if right doesn't exist (meaning its already the right most), then insert it here
				if (currentNode->rightNode == nullptr) {
					currentNode->rightNode = newNode; 
					numNodes++;
					break;
				}

				//else move on to the next right
				currentNode = currentNode->rightNode;
			}

			//if the newItem's key is less than the currentNode's key, go left
			else if (currentNode->key > newItem) {

				//if left doesnt exist (meaning its already the right most), then insert it here
				if (currentNode->leftNode == nullptr) {
					currentNode->leftNode = newNode;
					numNodes++;
					break;
				}
				//else move on to the next left
				currentNode = currentNode->leftNode;
			}

			//if the newItem's key matches the currentNode's key, then just update it
			else if (currentNode->key == newItem) {
				
				update(currentNode->key, newItem);
				break;
			}

		}//end while loop once it inserts the newNode and moves onto the end (nullptr)
	}
}

//insert a node
template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem, void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {

	treeNode<DataType> *currentNode; 
	treeNode<DataType> *trailCurrentNode;

	treeNode<DataType> *newNode;
	newNode = new treeNode<DataType>;
	newNode->key = newItem; 
	newNode->rightNode = nullptr;
	newNode->leftNode = nullptr; 


	//if tree is empty
	if (root == nullptr) {
		root = newNode;
	}

	else {
		
		currentNode = root;
		trailCurrentNode = currentNode;

		while (currentNode != nullptr) {

			//if the newItem's key is found then just call the duplicateItemFound
			if (currentNode->key == newItem) {
				(*duplicateItemFound)(currentNode->key, newItem);
				return;
			}

			//if the newItem's key is less tha the currentNode' key, go left
			else if (currentNode->key > newItem) {

				currentNode = currentNode->leftNode;
			}

			//if the newItem's key is more than the currentNode's key, go right
			else {
				
				currentNode = currentNode->rightNode;
			}

		}

		//currentNode keeps moving to the spot that newItem should be inserted in until it reaches the end


		//then you can insert it using the trailCurrentNode which stored the original currentNode
		if (trailCurrentNode->key > newItem) {
			trailCurrentNode->leftNode = newNode;
			numNodes++;
		}
		else {
			trailCurrentNode->rightNode = newNode;
			numNodes++;
		}


	}


}

//updates the data of a node
template <class DataType>
void binarySearchTree<DataType>::update(DataType &existingItem, const DataType &newItem) {

	existingItem = newItem;

}

//uses inorder traversal to go through the tree, each node once
template <class DataType>
void binarySearchTree<DataType>::traverse(void(*itemFound)(const DataType &foundItem)) const {
	
	inorder(root, itemFound);

}

//inorder traversal is left, visit the root, then right
template <class DataType>
void binarySearchTree<DataType>::inorder(treeNode<DataType>* p, void(*visit) (const DataType& item)) const {

	if (p != nullptr) {

		inorder(p->leftNode, *visit);
		(*visit)(p->key);
		inorder(p->rightNode, *visit);

	}

}

template <class DataType>
void binarySearchTree<DataType>::inorder2(treeNode<DataType>* p, std::ostream &outstream, void(*visit) (const treeNode<DataType>* node, std::ostream &out)) const {

	if (p != nullptr) {

		inorder2(p->leftNode);
		(*visit)(p, outstream);
		inorder2(p->rightNode);

	}

}
#endif 