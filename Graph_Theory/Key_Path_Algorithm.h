#ifndef KEY_PATH_ALGORITHM_H
#define KEY_PATH_ALGORITHM_H

#include <vector>
#include <queue>
#include <map>

#include "Chain_Forward_Star.h"
#include "Kahn.h"

using namespace std;

class Key_Path_Algorithm
{
public:
    Key_Path_Algorithm(const Chain_Forward_Star &grath) //AOE网关键路径算法
    {
        Kahn kahn(grath);
        topology_list = kahn.topology_list;
        earlist = kahn.topology_distance;

        latest.resize(earlist.size(), inf);
        latest[topology_list.back()] = earlist[topology_list.back()];
        for (int i = topology_list.size() - 2; i >= 0; i--)
        {
            int tmp_index = topology_list[i];
            for (int i = grath.head[tmp_index]; i != -1; i = grath.edges[i].next)
            {
                latest[tmp_index] = min(latest[tmp_index], latest[grath.edges[i].to] - grath.edges[i].w);
            }
        }
        for (int i = 0; i < topology_list.size(); i++)
        {
            if (abs(earlist[topology_list[i]] - latest[topology_list[i]]) < epsion)
            {
                key_path.push_back(topology_list[i]);
            }
        }
    }

    float abs(float _x)
    {
        return _x > 0 ? _x : -_x;
    }
    vector<int> topology_list; //存储每个事件（节点）的拓扑排序结果
    vector<float> earlist;     //存储每个事件（节点）的最早开始时间
    vector<float> latest;      //存储每个事件（节点）的最晚发生时间
    vector<int> key_path;      //存储每个事件（节点）的拓扑排序结果

    const float epsion = 0.0001;
    const float inf = 1 / epsion;
};

#endif // defined KEY_PATH_ALGORITHM_H_H