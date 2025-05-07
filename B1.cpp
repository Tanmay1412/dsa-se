/*
🔘PROBLEM STATEMENT:-
Construct a Binary Search Tree (BST) and implement the following operations:
- Insert a new node
- Find the number of nodes in the longest path from root (i.e., tree height)
- Find the minimum data value in the BST
- Convert the tree to its mirror (swap left and right pointers)
- Search for a value in the BST
*/

#include <iostream>
using namespace std;

// Node structure for BST
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// 🌳 In-order Traversal (Left, Root, Right)
void traversal(Node* root) {
    if (root == NULL) return;

    traversal(root->left);
    cout << root->data << " ";
    traversal(root->right);
}

// 🔧 Insert a new node into BST
Node* insert(Node* root, int x) {
    if (root == NULL) {
        return new Node(x);
    }
    else if (x >= root->data) {
        root->right = insert(root->right, x);
    }
    else {
        root->left = insert(root->left, x);
    }
    return root;
}

// 📏 Find height of the tree (longest path from root to leaf)
int height(Node* root) {
    if (root == NULL) return 0;

    int left_subtree = height(root->left);
    int right_subtree = height(root->right);
    return 1 + max(left_subtree, right_subtree); // add 1 for current node
}

// 🔽 Find minimum value in BST (always in left-most node)
int minimum(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty!" << endl;
        return -1;
    }
    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// 🔁 Convert BST to its mirror image (swap left and right pointers at every node)
void mirror(Node* root) {
    if (root == NULL) return;

    mirror(root->left);
    mirror(root->right);
    swap(root->left, root->right);
}

// 🔍 Search for a value in BST
void search(Node* root, int key, bool &present) {
    if (root == NULL) return;

    if (root->data == key) {
        present = true;
    }
    else if (key < root->data) {
        search(root->left, key, present);
    }
    else {
        search(root->right, key, present);
    }
}

int main() {
    Node* root = NULL;
    int n;

    cout << "Enter the number of nodes to be inserted in the BST: ";
    cin >> n;

    // Insert elements into BST
    for (int i = 0; i < n; i++) {
        int element;
        cout << "Enter the data value for NODE " << i + 1 << ": ";
        cin >> element;
        root = insert(root, element);  // must assign to root in case of initial NULL
    }

    cout << "\n=========================================\n";

    cout << "In-order Traversal of the BST (Sorted Order): ";
    traversal(root);
    cout << "\n";

    cout << "=========================================\n";
    cout << "Height of the tree (Longest path from root): " << height(root) << endl;

    cout << "=========================================\n";
    cout << "Minimum value in BST: " << minimum(root) << endl;

    cout << "=========================================\n";
    int key;
    cout << "Enter a value to search in BST: ";
    cin >> key;
    bool present = false;
    search(root, key, present);
    if (present) {
        cout << "✅ Key is present in BST." << endl;
    } else {
        cout << "❌ Key not found in BST." << endl;
    }

    cout << "=========================================\n";
    cout << "Mirroring the BST...\n";
    mirror(root);
    cout << "In-order Traversal after Mirroring: ";
    traversal(root);
    cout << endl;

    return 0;
}
