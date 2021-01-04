#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <vector>
#include <map>

#include "../Graph_Theory/Chain_Forward_Star.h"

using namespace std;

class Ford_Fulkerson //解决网络流问题的常用算法
{
public:
    Ford_Fulkerson(const Chain_Forward_Star &_grath, int _start_point_index, int _end_point_index) //复杂度O(m*f),m是边数，f是最大流
    {
        int max_point_index = 0;
        start_point_index = _start_point_index;
        end_point_index = _end_point_index;
        for (int i = 0; i < _grath.edges.size(); i++)
        {
            max_point_index = max(max_point_index, max(_grath.edges[i].from, _grath.edges[i].to));
            int tmp_index = grath.find_edge(_grath.edges[i].from, _grath.edges[i].to);
            if (tmp_index == -1)
            { //边是成对建立的，这条边没有，那么反向边也没有
                grath.add_edge(_grath.edges[i].from, _grath.edges[i].to, _grath.edges[i].w);
                grath.add_edge(_grath.edges[i].to, _grath.edges[i].from, 0.0); //在建边的同时，在反方向建一条边权为0的边
            }
            else
            {
                grath.edges[tmp_index].w = _grath.edges[i].w; //当前边已有，直接赋值，反向边不操作
            }
        }
        vis.resize(max_point_index + 1, false); //标志该点是否被访问

        max_flow = 0;
        while (1)
        {
            float cur_flow = dfs(start_point_index, inf);
            if (cur_flow < epsion)
                break;
            vis = vector<bool>(max_point_index + 1, false); //重置访问标志数组
            max_flow += cur_flow;
        }
    }

    float dfs(int cur_point_index, float flow)
    {
        if (cur_point_index == end_point_index) //递归基
        {
            return flow; // 到达终点，返回这条增广路的流量
        }
        vis[cur_point_index] = true;
        for (int eg = grath.head[cur_point_index]; eg != -1; eg = grath.edges[eg].next) //该起点出发的边的遍历
        {
            int to = grath.edges[eg].to;
            float vol = grath.edges[eg].w;
            float c;
            // 返回的条件是残余容量大于0、未访问过该点且接下来可以达到终点（递归地实现）
            // 传递下去的流量是边的容量与当前流量中的较小值
            if (vol > epsion && !vis[to] && (c = dfs(to, min(vol, flow))) > epsion)
            {
                grath.edges[eg].w -= c;
                grath.edges[eg ^ 1].w += c; // 这是链式前向星取反向边的一种简易的方法,我们的反向边都是紧接着正向边建立
                return c;
            }
        }
        return -1.0; // 无法到达终点
    }

public:
    Chain_Forward_Star grath;
    int start_point_index;
    int end_point_index;
    float max_flow;
    vector<bool> vis;
    const float epsion = 0.0001;
    const float inf = 1 / epsion;
};

#endif // defined FORD_FULKERSON_H