#ifndef EDMOND_KARP_H
#define EDMOND_KARP_H

#include <vector>
#include <queue>

#include "../Graph_Theory/Chain_Forward_Star.h"

using namespace std;

class Edmond_Karp  //解决网络流问题的常用算法
{
public:
    Edmond_Karp(const Chain_Forward_Star &_grath, int _start_point_index, int _end_point_index)   //复杂度O(n*m^2),n是点数，m是边数
    {
        max_point_index = 0;
        start_point_index = _start_point_index;
        end_point_index = _end_point_index;
        for (int i = 0; i < _grath.edges.size(); i++)
        {
            max_point_index = max(max_point_index, max(_grath.edges[i].from, _grath.edges[i].to)); //记录最大的点索引号
            grath.add_edge(_grath.edges[i].from, _grath.edges[i].to, _grath.edges[i].w);
            grath.add_edge(_grath.edges[i].to, _grath.edges[i].from, 0.0); //在建边的同时，在反方向建一条边权为0的边
                                                                           //对于本算法，就算两个节点之间存在正反两条边，也可以如此做，这两条边及其对应的反向边一共会建立四条边，不影响算法
        }
        flow.resize(max_point_index + 1, 0);
        max_flow = 0;
        while (bfs()) //使用BFS搜索流通道，返回true代表搜到了
        {
            max_flow += flow[end_point_index];
            for (int i = end_point_index; i != start_point_index; i = grath.edges[last[i] + 1].to) //通过后向指针，从汇点原路返回更新残余容量
            {
                grath.edges[last[i]].w -= flow[end_point_index];     //注意，这里的last[i]是从起点过来的，经过i的正向边，这条边的终点是i
                grath.edges[last[i] ^ 1].w += flow[end_point_index]; //反向边
            }
        }
    }

    bool bfs()
    {
        last = vector<int>(max_point_index + 1, -1); //重置后向指针（到达顶点cur经过的上一条边的索引）
        queue<int> q;
        q.push(start_point_index);
        flow[start_point_index] = inf;
        while (!q.empty())
        {
            int p = q.front();
            q.pop();
            if (p == end_point_index) // 到达汇点，结束搜索
                break;
            for (int eg = grath.head[p]; eg != -1; eg = grath.edges[eg].next)
            {
                int to = grath.edges[eg].to;
                float vol = grath.edges[eg].w;
                if (vol > 0 && last[to] == -1) // 如果残余容量大于0且未访问过（所以last保持在-1）
                {
                    last[to] = eg;
                    flow[to] = min(flow[p], vol);
                    q.push(to);
                }
            }
        }
        return last[end_point_index] != -1;
    }

public:
    Chain_Forward_Star grath;
    int start_point_index;
    int end_point_index;
    int max_point_index;
    float max_flow;

    vector<int> last;   //last[cur] 代表在搜索过程中，到达顶点cur经过的上一条边的索引，类似于后向指针，默认-1
    vector<float> flow; //flow[cur] 代表在搜索过程中，到达顶点cur对应的网络流

    const float epsion = 0.0001;
    const float inf = 1 / epsion;
};

#endif // defined EDMOND_KARP_H