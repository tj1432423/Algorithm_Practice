#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <queue>

#include "Chain_Forward_Star.h"

using namespace std;

class Kruskal //最小生成树的常用算法
{
public:
    Kruskal(const Chain_Forward_Star &grath)
    {
        //Kruskal算法是以边为对象，不断地加入新的不构成环路的最短边来构成最小生成树。
        if (grath.edges.empty())
        {
            printf("Fetal Wrong !!! The grath is empty !!!\n");
            return;
        }
        cost=0;;
        parent.resize(grath.head.size(), -1);
        height.resize(grath.head.size(), 0); //默认值height[cur]=0代表叶节点
        source.resize(grath.head.size(), -1);
        for (int i = 0; i < grath.head.size(); i++) //并查集，初始化（按秩合并）
        {
            source[i] = i;
        }
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> q;
        for (int i = 0; i < grath.edges.size(); i++)
        {
            q.push(make_pair(grath.edges[i].w, i)); //把n条边按照从小到大的数据进行排列
        }
        while (q.size())
        {
            int cur_edge_index = q.top().second;
            q.pop();
            int cur_edge_from = grath.edges[cur_edge_index].from;
            int cur_edge_to = grath.edges[cur_edge_index].to;
            if (find(cur_edge_from) != find(cur_edge_to))
            {
                parent[cur_edge_to] = cur_edge_from;
                cost+=grath.edges[cur_edge_index].w;
                merge(cur_edge_from, cur_edge_to); //如果发现边的两个节点分别位于两棵树上，那么把两棵树合并成为一颗树
            }
            else
            {
                //如果树的两个节点位于同一棵树上，那么忽略这条边，继续运行
            }
        }
    }

    int find(int x) //并查集，合并（路径压缩）
    {
        if (x == source[x])
            return x;
        else
        {
            source[x] = find(source[x]); //父节点设为根节点
            return source[x];            //返回父节点
        }
    }

    void merge(int i, int j) //并查集，合并（路径压缩 , 按秩合并）
    {
        int x = find(i), y = find(j); //先找到两个根节点
        if (height[x] <= height[y])
            source[x] = y;
        else
            source[y] = x;
        if (height[x] == height[y] && x != y)
            height[y]++; //如果深度相同且根节点不同，则新的根节点的深度+1
    }

public:
    vector<int> parent; //最小生成树的矩阵表示，索引为cur的节点的父节点的索引为parent[cur]，默认值source[cur]=-1代表无父节点
    float cost; //最小生成树的所有边的总和
private:
    vector<bool> vis;   //该节点时候访问过
    vector<int> height; //索引为cur的节点的深度为height[cur]，默认值height[cur]=0代表叶节点
    vector<int> source; //索引为cur的节点的源头点的索引为source[cur]，默认值source[cur]=cur指向它自己，用于并查集
};

#endif // defined PRIM_H