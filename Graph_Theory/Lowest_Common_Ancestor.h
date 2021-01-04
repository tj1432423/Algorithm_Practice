#ifndef LOWEST_COMMON_ANCESTOR_H
#define LOWEST_COMMON_ANCESTOR_H

#include <vector>
#include <map>

#include "../Data_Structure/Binary_Tree_Node.h" 

using namespace std;

class Lowest_Common_Ancestor
{
public:
    Lowest_Common_Ancestor(TreeNode *root)
    {
        log2.resize(2, 0);
        dfs(root, 0);
        
    }

    TreeNode * find_lca(TreeNode *a, TreeNode *b){
        if (dep[a] > dep[b]) // 不妨设a的深度小于等于b
            swap(a, b);
        while (dep[a] != dep[b]) // 跳到深度相等为止
        {
            b = father[b][log2[dep[b] - dep[a]]]; // b不断往上跳
        }
        if (a == b)
        {
            return a;
        }
        for (int k = log2[dep[a]]; k >= 0; k--)
            if (father[a][k] != father[b][k])
                a = father[a][k], b = father[b][k];
        return father[a][0];
    }

    void dfs(TreeNode *root, int depth)
    {
        if (!root)
            return;
        dep[root] = depth;
        TreeNode *cur;
        if (root->left)
        {
            cur = root->left;
            father[cur][0] = root;
            if (debug_switch)
                printf("father[%d][%d] = %d \n", cur->val, 0, father[cur][0]->val);
            for (int i = 1; i <= log2_cal(depth + 1); i++)
            {
                father[cur][i] = father[father[cur][i - 1]][i - 1]; // 这个DP也参见ST表的笔记
                if (debug_switch)
                    printf("father[%d][%d] = %d \n", cur->val, i, father[cur][i]->val);
            }
            dfs(root->left, depth + 1);
        }
        if (root->right)
        {
            cur = root->right;
            father[cur][0] = root;
            if (debug_switch)
                printf("father[%d][%d] = %d \n", cur->val, 0, father[cur][0]->val);
            for (int i = 1; i <= log2_cal(depth + 1); i++)
            {
                father[cur][i] = father[father[cur][i - 1]][i - 1]; // 这个DP也参见ST表的笔记
                if (debug_switch)
                    printf("father[%d][%d] = %d \n", cur->val, i, father[cur][i]->val);
            }
            dfs(root->right, depth + 1);
        }
    }

    int log2_cal(int x) // Log2的预处理参见ST表的笔记
    {
        if (x >= log2.size())
        {
            int tmp_index = log2.size();
            log2.resize(x + 1);
            for (int i = tmp_index; i <= x; i++)
            {
                log2[i] = log2[i / 2] + 1;
            }
        }
        return log2[x];
    }

private:
    vector<int> log2;
    map<TreeNode *, int> dep;
    map<TreeNode *, map<int, TreeNode *>> father; //我们用一个father[i][k]存储 i 号点的 2^k 级祖先
    const bool debug_switch = false;
};

#endif // defined LOWEST_COMMON_ANCESTOR_H