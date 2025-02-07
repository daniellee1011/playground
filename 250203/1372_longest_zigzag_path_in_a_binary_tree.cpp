// 1372. Longest ZigZag Path in a Binary Tree

#include <iostream>
#include <algorithm>
#include <queue>

using namespace::std;

// Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int longestZigZag(TreeNode* root) {
        int maxLength = 0;
        dfs(root, -1, 0, maxLength);
        return maxLength;
    }

    void dfs(TreeNode* node, int dir, int depth, int &maxLength) {
        if (!node) return;
        maxLength = max(maxLength, depth);
        dfs(node->left, -1, (dir == 1) ? depth + 1 : 1, maxLength);
        dfs(node->right, 1, (dir == -1) ? depth + 1 : 1, maxLength);
    }
};

// Inefficient, but pass all test cases
class _Solution {
public:
    int longestZigZag(TreeNode* root) {
        int result = 0;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            result = max(result, helper(node, -1, 0));
            result = max(result, helper(node, 1, 0));
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return result;
    }

    int helper(TreeNode* node, int dir, int depth) {
        if (!node->left && !node->right) {
            return depth;
        }
        if (dir == -1 && node->right) { // From left to right
            return helper(node->right, 1, depth + 1);
        } else if (dir == 1 && node->left) { // From right to left
            return helper(node->left, -1, depth + 1);
        }
        return depth;
    }
};