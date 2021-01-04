#ifndef KAHN_H
#define KAHN_H

#include <vector>
#include <queue>
#include <map>

#include "Chain_Forward_Star.h"

using namespace std;

class Kahn
{
public:
    Kahn(const Chain_Forward_Star &grath) //拓扑排序问题常用算法
    {
        topology_distance.resize(grath.head.size(),-1);
        for (int i = 0; i < grath.edges.size(); i++)
        {
            deg[grath.edges[i].to]++;
            deg[grath.edges[i].from]++;
            deg[grath.edges[i].from]--;
        }
        queue<int> q;
        point_num = 0;
        for (auto point : deg)
        {
            point_num++;
            if (point.second == 0)
            {
                q.push(point.first);
                topology_distance[point.first] = 0;
            }
        }
        while (!q.empty())
        {
            int t = q.front();
            q.pop();
            topology_list.push_back(t);
            for (auto i = grath.head[t]; i != -1; i = grath.edges[i].next)
            {
                deg[grath.edges[i].to]--;
                topology_distance[grath.edges[i].to] = max(topology_distance[grath.edges[i].to], topology_distance[t] + grath.edges[i].w);
                if (deg[grath.edges[i].to] == 0)
                { // 出现了新的入度为0的点
                    q.push(grath.edges[i].to);
                }
            }
        }
        loop_judgement = topology_list.size() != point_num;
    }

public:
    vector<int> topology_list;       //拓扑排序结果
    vector<float> topology_distance; //对应AOE网中事件的最早发生时间，常用于关键路径算法
    bool loop_judgement;

private:
    map<int, int> deg;
    int point_num;
};

#endif // defined KAHN_H