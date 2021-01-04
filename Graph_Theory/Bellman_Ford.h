#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "Chain_Forward_Star.h"
#include <vector>

class Bellman_Ford  //最短路径问题常用算法
{
public:
    Bellman_Ford(const Chain_Forward_Star &grath, int _start_index)
    {
        //grath = _grath;
        start_index = _start_index;
        int n = grath.head.size();
        dist.resize(n, Bis_Dist);
        dist[start_index] = 0;

        for (int k = 1; k <= (n - 1); k++)
        { //遍历n-1遍
            for (int i = 0; i < grath.edges.size(); i++)
            {
                dist[grath.edges[i].to] = min(dist[grath.edges[i].to], dist[grath.edges[i].from] + grath.edges[i].w);
            }
        }

        negative_weight_loop = negative_weight_loop_detection(grath);
    }

private:
    bool negative_weight_loop_detection(const Chain_Forward_Star &grath)
    {
        vector<float> tmp_dist(dist);
        for (int i = 0; i < grath.edges.size(); i++)
        {
            dist[grath.edges[i].to] = min(dist[grath.edges[i].to], dist[grath.edges[i].from] + grath.edges[i].w);
        }
        return !(dist == tmp_dist);
    }

public:
    vector<float> dist;
    bool negative_weight_loop;
    int start_index;

private:
    //Chain_Forward_Star grath;
    const float Bis_Dist = 99999.9;
};

#endif // defined BELLMAN_FORD_H