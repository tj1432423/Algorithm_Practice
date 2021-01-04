#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

using namespace std;

/*****Definition for a binary tree node*****/
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif // defined BINARY_TREE_NODE_H