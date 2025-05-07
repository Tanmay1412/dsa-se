/*
🔘PROBLEM STATEMENT:- 
Given sequence k = k1 <k2 < ... <kn of n sorted keys, with a
search probability pi for each key ki . Build the Binary search tree that has
the least search cost given the access probability for each key?
*/ 

/*
#️⃣Quick Revision Notes:-

🔹Optimal Binary Search Tree :- 

*/

#include <iostream>
#include <limits.h>
using namespace std;

// Tree node definition
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        left = right = NULL;
    }
};

// Utility function to get sum of frequencies from index i to j
int sum(int freq[], int i, int j) {
    int total = 0;
    for (int k = i; k <= j; k++)
        total += freq[k];
    return total;
}

// Function to construct the tree using root table
Node* buildOptimalTree(int keys[], int rootIndex[][100], int i, int j) {
    if (i > j)
        return NULL;

    int r = rootIndex[i][j];
    Node* node = new Node(keys[r]);

    node->left = buildOptimalTree(keys, rootIndex, i, r - 1);
    node->right = buildOptimalTree(keys, rootIndex, r + 1, j);

    return node;
}

// Builds the optimal BST using DP and returns its root
Node* optimalBST(int keys[], int freq[], int n) {
    int cost[100][100] = {0};
    int rootIndex[100][100] = {0};

    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
        rootIndex[i][i] = i;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            int fsum = sum(freq, i, j);

            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) + fsum;

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    rootIndex[i][j] = r;
                }
            }
        }
    }

    return buildOptimalTree(keys, rootIndex, 0, n - 1);
}

// Inorder traversal of the tree
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

int main() {
    int k;
    cout << "Enter number of keys: ";
    cin >> k;

    int keys[100], freq[100];

    cout << "Enter " << k << " keys in sorted order: ";
    for (int i = 0; i < k; i++)
        cin >> keys[i];

    cout << "Enter corresponding " << k << " frequencies: ";
    for (int i = 0; i < k; i++)
        cin >> freq[i];

    Node* root = optimalBST(keys, freq, k);

    cout << "Inorder traversal of the Optimal BST: ";
    inorder(root);
    cout << endl;

    return 0;
}

