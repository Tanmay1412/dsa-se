/*
🔘PROBLEM STATEMENT:
Construct an expression tree from a given prefix expression (e.g., +--a*bc/def),
perform postorder traversal (non-recursive), and delete the entire tree.
*/

#include <iostream>
#include <stack>
using namespace std;

// Define structure for expression tree node
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) {
        data = val;
        left = right = nullptr;
    }
};

// 🚧 Constructs an Expression Tree from a given Prefix expression
TreeNode* constructExpressionTree(const string& prefixExpression) {
    stack<TreeNode*> stk;

    // Traverse from right to left since it's prefix
    for (int i = prefixExpression.length() - 1; i >= 0; i--) {
        char ch = prefixExpression[i];

        // Create a new node
        TreeNode* newNode = new TreeNode(ch);

        if (isalnum(ch)) {
            // Operand: push onto stack
            stk.push(newNode);
        } else {
            // Operator: pop two nodes for children
            if (stk.size() < 2) {
                cerr << "Invalid prefix expression!" << endl;
                return nullptr;
            }
            newNode->left = stk.top(); stk.pop();
            newNode->right = stk.top(); stk.pop();
            stk.push(newNode); // Push current subtree back
        }
    }

    // Final node is the root of the tree
    if (stk.size() != 1) {
        cerr << "Invalid prefix expression!" << endl;
        return nullptr;
    }

    return stk.top();
}

// 🔁 Non-Recursive Post-order Traversal
void postOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    stack<TreeNode*> stk;
    TreeNode* current = root;
    TreeNode* lastVisited = nullptr;

    while (!stk.empty() || current != nullptr) {
        if (current != nullptr) {
            stk.push(current);
            current = current->left;
        } else {
            TreeNode* topNode = stk.top();

            // If right child exists and is unvisited
            if (topNode->right != nullptr && topNode->right != lastVisited) {
                current = topNode->right;
            } else {
                // Process current node
                cout << topNode->data << " ";
                lastVisited = topNode;
                stk.pop();
            }
        }
    }
}

// 🧹 Recursively Delete the Tree
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 🟩 Main function
int main() {
    // Example prefix expression
    string prefixExpression = "+--a*bc/def";

    // Build the expression tree
    TreeNode* root = constructExpressionTree(prefixExpression);

    // If tree was created successfully
    if (root) {
        cout << "Post-order traversal: ";
        postOrderTraversal(root); // Expected Output: a b c * - d e / f - +
        cout << endl;

        // Clean up
        deleteTree(root);
    } else {
        cout << "Expression tree could not be created due to invalid input.\n";
    }

    return 0;
}
