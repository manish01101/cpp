#include<iostream>
#include<queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

int countNodes(struct Node* root) {
    //base case
    if (root == NULL)
        return 0;
    int ans = 1 + countNodes(root->left) + countNodes(root->right);
    return ans;
}

bool isCBT(struct Node* root, int index, int cnt) {
    if (root == NULL)
        return true;
    if (index >= cnt)
        return false;
    else {
        bool left = isCBT(root->left, 2 * index + 1, cnt);
        bool right = isCBT(root->right, 2 * index + 2, cnt);
        return (left && right);
    }
}
bool isMaxOrder(struct Node* root) {
    //leaf node
    if (root->left == NULL && root->right == NULL)
        return true;
    // only left child present
    if (root->right == NULL) {
        return (root->data > root->left->data);
    }
    // both left and right child present
    else {
        bool left = isMaxOrder(root->left);
        bool right = isMaxOrder(root->right);

        return (left && right && (root->data > root->left->data && root->data > root->right->data));
    }
}

bool isHeap(struct Node* root) {
    int index = 0;
    int totalCount = countNodes(root);
    if (isCBT(root, index, totalCount) && isMaxOrder(root)) {
        return true;
    }
    else
        return false;
}