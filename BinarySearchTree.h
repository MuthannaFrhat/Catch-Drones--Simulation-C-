#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <sstream>
#include <iomanip>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T* data;
        Node* left;
        Node* right;

        Node(T* value) : data(value), left(nullptr), right(nullptr) {}
        ~Node()=default;
    };
public:
    Node* root;
    std::string formatDouble(double value) const;
    void insert(Node*& node, T* value);
    T* search(Node* node, int id) const;
    T* search( int id) const;
    T* findMin(Node* node) const;
    T* findMax(Node* node) const;
    void remove(Node*& node, int id);
    void clear(Node*& node);
    void print(Node* node) const;
    int size(Node* node) const;
    void inOrderTraversalAndPrint(Node* node, std::ofstream& out) const;
    void inOrderTraversalAndPrint( std::ofstream& out) const;



    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    void insert(T* value) { insert(root, value); }

    T* findMin() const { return findMin(root); }
    T* findMax() const { return findMax(root); }
    void remove(int id) { remove(root, id); }
    void clear() { clear(root); }
    void print() const { print(root); }
    int size() const { return size(root); }
};
//this to print the tree in the requested format
template<typename T>
std::string BinarySearchTree<T>::formatDouble(double value) const {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;

    std::string result = stream.str();
    if (result.back() == '0') {
        result.pop_back();
        if (result.back() == '0') {
            result.pop_back();
        }
    }
    if (result.back() == '.') {
        result += '0';
    }
    return result;
}


//this function print the tree inOrder by ID of each drone
template <typename T>
void BinarySearchTree<T>::inOrderTraversalAndPrint(std::ofstream& out) const {
    // Start the traversal from the root node
    inOrderTraversalAndPrint(this->root, out);
}

//  helper function for in-order traversal
template <typename T>
void BinarySearchTree<T>::inOrderTraversalAndPrint(Node* node, std::ofstream& out) const {
    if (node == nullptr) return;

    // Traverse the left subtree
    inOrderTraversalAndPrint(node->left, out);

    // Print the current node (drone) data
    out << node->data->getType() << " "
        << formatDouble(node->data->getPosition().x) << " "
        << formatDouble(node->data->getPosition().y) << std::endl;

    // Traverse the right subtree
    inOrderTraversalAndPrint(node->right, out);
}


//insert T object to the tree
template <typename T>
void BinarySearchTree<T>::insert(Node*& node, T* value) {

        if (!node) {
            node = new Node(value);  // Node is nullptr, create a new node
        } else if (value->getId() < node->data->getId()) {
            insert(node->left, value);
        } else if (value->getId() > node->data->getId()) {
            insert(node->right, value);
        }

}

//search for object by id in the tree
template <typename T>
T* BinarySearchTree<T>::search(int id) const {
    return search(root, id);  // Call the recursive helper function starting from the root
}

//  helper function for search
template <typename T>
T* BinarySearchTree<T>::search(Node* node, int id) const {
    if (!node) {
        return nullptr;  // ID not found
    }

    if (id < node->data->getId()) {
        return search(node->left, id);  // Search in the left subtree
    } else if (id > node->data->getId()) {
        return search(node->right, id);  // Search in the right subtree
    } else {
        return node->data;  // ID found, return the drone data
    }
}


//search for the min object by ID in the tree and return it
template <typename T>
T* BinarySearchTree<T>::findMin(Node* node) const {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node->data;
}


//search for the max object in the tree by ID and then return it
template <typename T>
T* BinarySearchTree<T>::findMax(Node* node) const {
    if (!node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node->data;
}


//delete object from the tree by ID
template <typename T>
void BinarySearchTree<T>::remove(Node*& node, int id) {
    if (!node) return;

    if (id < node->data->getId()) {
        remove(node->left, id);
    } else if (id > node->data->getId()) {
        remove(node->right, id);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            node = temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            node = temp;
        } else {
            Node* temp = node->right;
            while (temp->left) temp = temp->left;
            delete node->data;
            node->data = temp->data;
            remove(node->right, temp->data->getId());
        }
    }
}


//clear the tree
template <typename T>
void BinarySearchTree<T>::clear(Node*& node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}


//
template <typename T>
void BinarySearchTree<T>::print(Node* node) const {
    if (node) {
        print(node->left); // Inorder traversal: first visit the left subtree

        // Print the drone type and position (x, y) from the drone's position
        std::cout << node->data->getType() << " "  // Print drone type
                  << node->data->getPosition().x << " "  // Print position.x
                  << node->data->getPosition().y << std::endl;  // Print position.y

        print(node->right); // Then visit the right subtree
    }
}


//return size of the tree
template <typename T>
int BinarySearchTree<T>::size(Node* node) const {
    if (!node) return 0;
    return 1 + size(node->left) + size(node->right);
}

#endif // BINARYSEARCHTREE_H
