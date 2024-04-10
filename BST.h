#ifndef UNTITLED2_BST_H
#define UNTITLED2_BST_H

#include "iostream"
#include "fstream"
#include "string"

using namespace std;


struct Node {
    int data;
    Node *left;
    Node *right;
    Node *previous;

    Node(int value) : data(value), right(nullptr), left(nullptr), previous(nullptr) {}

};

class BSTree {
    Node *root_of_tree;

    void printOrderly(Node *value) {
        if (value) {
            printOrderly(value->left);
            cout << value->data << endl;
            printOrderly(value->right);
        }
    }
    void saveTreeToFile(Node *node, ofstream &file) {
        if (node) {
            file << node->data << " ";
            saveTreeToFile(node->left, file);
            saveTreeToFile(node->right, file);
        }
    }
    Node *findNode(Node *root, int value) {
        if (root == nullptr || root->data == value)
            return root;

        if (root->data < value)
            return findNode(root->right, value);

        return findNode(root->left, value);
    }
    void distructor_clear(Node *value) {
        if (value) {
            distructor_clear(value->right);
            distructor_clear(value->left);
            distructor_clear(value->previous);
            delete (value);
        }
    }
    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    Node *deleteNode(Node *root, int value) {
        if (root == nullptr) return root;

        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
        else {
            if (root->left == nullptr) {
                Node *temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }


public:
    BSTree() : root_of_tree(nullptr) {}
    BSTree(initializer_list<int> list) : root_of_tree(nullptr) {
        for (int value: list) {
            add_element(value);
        }
    }
    bool add_element(int value) {
        Node *new_element = new Node(value);
        if (!root_of_tree) {
            root_of_tree = new_element;
            return true;
        }
        Node *previous_value = nullptr;
        Node *current_value = root_of_tree;
        while (current_value) {
            previous_value = current_value;
            if (value < current_value->data) {
                current_value = current_value->left;
            } else if (value > current_value->data) {
                current_value = current_value->right;
            } else {
                delete new_element;
                return false;
            }
        }
        new_element->previous = previous_value;
        if (value < previous_value->data) {
            previous_value->left = new_element;
        } else {
            previous_value->right = new_element;
        }
        return true;
    }
    bool delete_element(int value) {
        if (!find_element(value)) return false;
        root_of_tree = deleteNode(root_of_tree, value);
        return true;
    }
    bool find_element(int value) {
        return findNode(root_of_tree, value) != nullptr;
    }
    void print() {
        printOrderly(root_of_tree);
        cout << endl;
    }
    bool save_to_file(const string &path) {
        ofstream file(path);
        saveTreeToFile(root_of_tree, file);
        file.close();
        return true;
    }

    bool load_from_file(const string &path) {
        ifstream file(path);
        int value;
        while (file >> value) {
            add_element(value);
        }
        file.close();
        return true;
    }
    ~BSTree() {
        distructor_clear(root_of_tree);
    }
};
#endif
