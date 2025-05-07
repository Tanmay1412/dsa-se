#include <iostream>
#include <string>
using namespace std;

// 🌲 Node structure for AVL Tree
class Node {
public:
    string keyword;   // Keyword in the dictionary
    string meaning;   // Associated meaning
    int height;       // Height of the node (for balancing)
    Node* left;       // Left child
    Node* right;      // Right child

    Node(string key, string value) {
        keyword = key;
        meaning = value;
        height = 1; // Leaf node starts with height 1
        left = right = NULL;
    }
};

// 📚 AVL Tree class for dictionary operations
class AVLTree {
private:
    Node* root; // Root of the AVL tree

    // 🔢 Utility to get height of node
    int getHeight(Node* node) {
        return (node == NULL) ? 0 : node->height;
    }

    // ⚖️ Utility to calculate balance factor
    int getBalanceFactor(Node* node) {
        return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    // 🔁 Left rotation to balance tree
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    // 🔁 Right rotation to balance tree
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    // ➕ Recursive function to insert a node and balance AVL tree
    Node* insert(Node* node, string key, string value) {
        if (node == NULL)
            return new Node(key, value);

        if (key < node->keyword)
            node->left = insert(node->left, key, value);
        else if (key > node->keyword)
            node->right = insert(node->right, key, value);
        else {
            // If keyword exists, just update its meaning
            node->meaning = value;
            return node;
        }

        // Update current node height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Balance the tree
        int balance = getBalanceFactor(node);

        // Handle 4 imbalance cases

        // Left-Left
        if (balance > 1 && key < node->left->keyword)
            return rotateRight(node);

        // Right-Right
        if (balance < -1 && key > node->right->keyword)
            return rotateLeft(node);

        // Left-Right
        if (balance > 1 && key > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left
        if (balance < -1 && key < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // 🔍 Find node with minimum keyword value (used in deletion)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    // ➖ Delete node and maintain AVL balance
    Node* deleteNode(Node* root, string key) {
        if (root == NULL)
            return root;

        // Perform normal BST deletion
        if (key < root->keyword)
            root->left = deleteNode(root->left, key);
        else if (key > root->keyword)
            root->right = deleteNode(root->right, key);
        else {
            // Node with one or no child
            if (root->left == NULL || root->right == NULL) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else {
                    *root = *temp; // Copy data
                }

                delete temp;
            } else {
                // Node with two children
                Node* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        // If tree had only one node
        if (root == NULL)
            return root;

        // Update height
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Balance tree
        int balance = getBalanceFactor(root);

        // Left-Left
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);

        // Right-Right
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);

        // Left-Right
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right-Left
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // 📈 Display dictionary in ascending order
    void displayAscendingOrder(Node* node) {
        if (node != NULL) {
            displayAscendingOrder(node->left);
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            displayAscendingOrder(node->right);
        }
    }

    // 📉 Display dictionary in descending order
    void displayDescendingOrder(Node* node) {
        if (node != NULL) {
            displayDescendingOrder(node->right);
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            displayDescendingOrder(node->left);
        }
    }

    // 🔍 Search for a keyword and count comparisons
    Node* search(Node* node, string key, int& comparisons) {
        if (node == NULL || node->keyword == key) {
            comparisons++;
            return node;
        }

        comparisons++;
        if (key < node->keyword)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

public:
    // 🌱 Constructor
    AVLTree() {
        root = NULL;
    }

    // 🧠 Add or update a keyword
    void addKeyword(string key, string value) {
        root = insert(root, key, value);
        cout << "✅ Keyword added or updated successfully." << endl;
    }

    // 🗑️ Delete a keyword
    void deleteKeyword(string key) {
        root = deleteNode(root, key);
        cout << "🗑️ Keyword deleted successfully." << endl;
    }

    // 📜 Display in ascending order
    void displayAscending() {
        if (root == NULL) {
            cout << "⚠️ The dictionary is empty." << endl;
            return;
        }
        cout << "📜 Dictionary in Ascending Order:" << endl;
        displayAscendingOrder(root);
    }

    // 📜 Display in descending order
    void displayDescending() {
        if (root == NULL) {
            cout << "⚠️ The dictionary is empty." << endl;
            return;
        }
        cout << "📜 Dictionary in Descending Order:" << endl;
        displayDescendingOrder(root);
    }

    // 🔍 Search for a keyword and show comparison count
    int findKeyword(string key) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);

        if (result != NULL) {
            cout << "🔍 Keyword: " << result->keyword << ", Meaning: " << result->meaning << endl;
            cout << "📊 Total Comparisons: " << comparisons << endl;
        } else {
            cout << "❌ Keyword not found." << endl;
        }

        return comparisons;
    }
};

// 🟩 Main driver
int main() {
    AVLTree dictionary;

    // Add entries
    dictionary.addKeyword("Apple", "A fruit.");
    dictionary.addKeyword("Banana", "A curved fruit.");
    dictionary.addKeyword("Cat", "A furry animal.");

    cout << endl;
    dictionary.displayAscending();

    cout << endl;
    dictionary.displayDescending();

    cout << endl;
    dictionary.findKeyword("Apple");

    cout << endl;
    dictionary.deleteKeyword("Banana");

    cout << endl;
    dictionary.displayAscending();

    return 0;
}
