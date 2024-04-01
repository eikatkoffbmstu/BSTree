#ifndef UNTITLED2_BST_H
#define UNTITLED2_BST_H

#include <iostream>

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

    void clear(Node *value) {
        if (value) {
            clear(value->right);
            clear(value->left);
            clear(value->previous);
            delete (value);
        }
    }

public:
    BSTree() : root_of_tree(nullptr) {} //конструктор без параметров
    BSTree(initializer_list<int> list) : root_of_tree(nullptr) {
        for (int value: list) {
            add_element(value);
        }
    } //конструктор с параметрами
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

    void print() {
        printOrderly(root_of_tree);
        cout << endl;
    }

    ~BSTree() {
        clear(root_of_tree);
    }
};



#endif
