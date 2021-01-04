#ifndef DINIC_H
#define DINIC_H

#include <vector>
#include <queue>

#include "../Graph_Theory/Chain_Forward_Star.h"

using namespace std;

class Dinic  //解决网络流问题的常用算法
{
public:
    Dinic(const Chain_Forward_Star &_grath, int _start_point_index, int _end_point_index) //复杂度O(m*n^0.5),n是点数，m是边数
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
        max_flow = 0;
        while (bfs())
        {
            cur = grath.head; // 这里相当于是在每次while (bfs()){}的循环执行之前，将cur重新初始化
            max_flow += dfs(start_point_index, inf);
        }
    }

    bool bfs() // BFS分层，预处理出源点到每个点的距离，每次循环都要预处理一次，因为有些边可能容量变为0不能再走
    {
        lv = vector<int>(max_point_index + 1, -1);
        lv[start_point_index] = 0; //起始点的层数是0
        queue<int> q;
        q.push(start_point_index);
        while (!q.empty())
        {
            int p = q.front();
            q.pop();
            for (int eg = grath.head[p]; eg != -1; eg = grath.edges[eg].next)
            {
                int to = grath.edges[eg].to;
                float vol = grath.edges[eg].w;
                if (vol > 0 && lv[to] == -1)
                {
                    lv[to] = lv[p] + 1;
                    q.push(to);
                }
            }
        }
        return lv[end_point_index] != -1; // 如果汇点未访问过说明已经无法达到汇点，此时返回false
    }

    float dfs(int p, int flow)
    {
        if (p == end_point_index)
            return flow;
        int rmn = flow;                                                   // 剩余的流量
        for (int eg = cur[p]; eg != -1 && rmn; eg = grath.edges[eg].next) // 多路增广节省很多花在重复路线上的时间,如果已经没有剩余流量则退出
        {
            cur[p] = eg; // 更新当前点对应的、仍然有剩余容量的第一条边，这样一来，在下一层的dfs()中，从当前边开始筛选，
                         //如果当前边容量用完，下次for循环会继续更新当前点对应的、仍然有剩余容量的第一条边
            int to = grath.edges[eg].to, vol = grath.edges[eg].w;
            if (vol > 0 && lv[to] == lv[p] + 1) // 往层数高的方向增广
            {
                int c = dfs(to, min(vol, rmn)); // 尽可能多地传递流量
                rmn -= c;                       // 当前通道占用流量c,剩余流量减少
                grath.edges[eg].w -= c;         // 更新残余容量
                grath.edges[eg ^ 1].w += c;     // 再次提醒，链式前向星的构造方式要满足特定方式，才能这样求反向边
            }
        }
        return flow - rmn; // 返回传递出去的流量的大小
    }

public:
    Chain_Forward_Star grath;
    int start_point_index;
    int end_point_index;
    int max_point_index;
    float max_flow;

    vector<int> lv;  //lv是每个点的层数,默认-1
    vector<int> cur; //cur用于标记增广起点，cur[a] 表示从a点出发的第一条边的编号，
                     //这个编号与head不同，如果将链式前向星中同一个点出发的所有边的存储看作一个链表，
                     //head[a]中存储头指针，这个cur[a]存储的相当于链表的中间节点，
                     //cur[a]之前的是已经被访问过的不需要再访问的，cur[a]代表待访问的从a点出发的第一条边的编号

    const float epsion = 0.0001;
    const float inf = 1 / epsion;
};

#endif // defined EDMOND_KARP_H