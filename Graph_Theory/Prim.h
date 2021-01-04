#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include <queue>

#include "Chain_Forward_Star.h"

using namespace std;

class Prim //最小生成树的常用算法
{
public:
    Prim(const Chain_Forward_Star &grath)
    {
        //Prim算法是以点为对象，挑选与点相连的最短边来构成最小生成树。
        if (grath.edges.empty())
        {
            printf("Fetal Wrong !!! The grath is empty !!!\n");
            return;
        }
        cost=0;
        int start_point_index = grath.edges[0].from;                                             //任选一个根节点
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> q; //创建优先级队列，包含边的权值及对应的边号
        vis.resize(grath.head.size(), false);
        parent.resize(grath.head.size(), -1);
        vis[start_point_index] = true;
        for (int i = grath.head[start_point_index]; i != -1; i = grath.edges[i].next)
        {
            q.push(make_pair(grath.edges[i].w, i)); //将初始点周边的边推入优先级队列
        }
        while (q.size())
        {
            int opt_edg_index = q.top().second;
            q.pop();
            if (vis[grath.edges[opt_edg_index].to]) //如果该边边到达的点已经被访问过了，本次伸展无效
            {
                continue;
            }
            vis[grath.edges[opt_edg_index].to] = true;                               //标记本节点被访问
            parent[grath.edges[opt_edg_index].to] = grath.edges[opt_edg_index].from; //写入节点的父节点
            cost+=grath.edges[opt_edg_index].w;
            for (int i = grath.head[grath.edges[opt_edg_index].to]; i != -1; i = grath.edges[i].next)
            {
                q.push(make_pair(grath.edges[i].w, i)); //将边推入优先级队列
            }
        }
    }

public:
    vector<int> parent; //最小生成树的矩阵表示，索引为cur的节点的父节点的索引为p[cur]，默认值-1代表节点无父节点
    float cost;         //最小生成树的所有边的总和
private:
    vector<bool> vis; //该节点时候访问过
};

#endif // defined PRIM_H