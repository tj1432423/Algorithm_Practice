#ifndef SPFA_H
#define SPFA_H

#include "Chain_Forward_Star.h"
#include <vector>
#include <queue>

using namespace std;

class SPFA  //最短路径问题常用算法
{
public:
    SPFA(const Chain_Forward_Star &grath, int _start_index)
    {
        //grath = _grath;
        start_index = _start_index;
        int n = grath.head.size();
        dist.resize(n, Bis_Dist);
        dist[start_index] = 0;
        inqueue.resize(grath.head.size(), false);
        enter_queue_times.resize(grath.head.size(), 0);
        negative_weight_loop = false;
        Q.push(start_index);
        inqueue[start_index] = true;
        enter_queue_times[start_index]++;
        while (!Q.empty())
        {
            int p = Q.front();
            Q.pop();
            inqueue[p] = false;
            for (int e = grath.head[p]; e != -1; e = grath.edges[e].next)
            {
                int to = grath.edges[e].to;
                if (dist[to] > dist[p] + grath.edges[e].w)
                {
                    dist[to] = dist[p] + grath.edges[e].w;
                    if (!inqueue[to])
                    {
                        inqueue[to] = true;
                        enter_queue_times[start_index]++;
                        if (enter_queue_times[start_index] > n)
                        {
                            negative_weight_loop = true;
                            return;
                        }
                        Q.push(to);
                    }
                }
            }
        }
    }

public:
    vector<float> dist;
    int start_index;
    bool negative_weight_loop;

private:
    //Chain_Forward_Star grath;
    queue<int> Q;
    vector<bool> inqueue;
    vector<int> enter_queue_times;
    const float Bis_Dist = 99999.9;
};

#endif // defined SPFA_H