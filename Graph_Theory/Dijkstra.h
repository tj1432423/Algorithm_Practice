#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Chain_Forward_Star.h"
#include <vector>
#include <queue>

class Dijkstra  //最短路径问题常用算法
{
public:
    Dijkstra(const Chain_Forward_Star &grath, int _start_index)
    {
        //grath = _grath;
        start_index = _start_index;
        int n = grath.head.size();
        dist.resize(n, Bis_Dist);
        dist[start_index] = 0;
        vis.resize(n, false);
        Q.push(make_pair(0, start_index));
        while (!Q.empty())
        {
            int p = Q.top().second;
            Q.pop();
            if (vis[p])
                continue;
            vis[p] = true;
            for (int e = grath.head[p]; e != -1; e = grath.edges[e].next)
            {
                int to = grath.edges[e].to;
                dist[to] = min(dist[to], dist[p] + grath.edges[e].w);
                if (!vis[to])
                    Q.push(make_pair(dist[to], to));
            }
        }
    }

public:
    vector<float> dist;
    int start_index;

private:
    //Chain_Forward_Star grath;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    vector<bool> vis;
    const float Bis_Dist = 99999.9;
};

#endif // defined DIJKSTRA_H