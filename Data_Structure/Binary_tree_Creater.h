#ifndef BINARY_TREE_CREATER_H
#define BINARY_TREE_CREATER_H

#include <vector>
#include <sstream>
#include <string>

#include "Binary_Tree_Node.h"

using namespace std;

class Binary_tree_Creater
{
public:
    Binary_tree_Creater(vector<string> &data)
    {
        int n = data.size();
        nodes.resize(n);
        for (int i = 0; i < n; i++)
        {
            if (data[i] == "Null" || data[i] == "null")
                nodes[i] = 0;
            else
                nodes[i] = new TreeNode(str2num(data[i]));
        }
        for (int i = 0; i < n; i++)
        {
            if (!nodes[i])
                continue;
            if (2 * i + 1 < n)
                nodes[i]->left = nodes[2 * i + 1];
            if (2 * i + 2 < n)
                nodes[i]->right = nodes[2 * i + 2];
        }
        if (n)
            root = nodes[0];
        else
            root = 0;
    }

private:
    string num2str(int i)
    {
        stringstream ss;
        ss << i;
        return ss.str();
    }

    int str2num(string s)
    {
        int num;
        stringstream ss(s);
        ss >> num;
        return num;
    }

public:
    TreeNode *root;
    vector<TreeNode *> nodes;
};

#endif // defined BINARY_TREE_CREATER_H