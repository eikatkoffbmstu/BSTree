#include "BST.h"

int main() {
    BSTree tree = {11, 100, 50, 25, 110, 200};
    tree.print();
    tree.find_element(50);
    tree.delete_element(50);
    tree.print();
}
