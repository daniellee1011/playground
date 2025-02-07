// 1372. Longest ZigZag Path in a Binary Tree

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void dfs(struct TreeNode* node, int dir, int depth, int *maxLength) {
    if (!node) return;
    *maxLength = *maxLength > depth ? *maxLength : depth;
    dfs(node->left, -1, (dir == 1) ? depth + 1 : 1, maxLength);
    dfs(node->right, 1, (dir == -1) ? depth + 1 : 1, maxLength);
}

int longestZigZag(struct TreeNode* root) {
    int maxLength = 0;
    dfs(root, -1, 0, &maxLength);
    return maxLength;
}