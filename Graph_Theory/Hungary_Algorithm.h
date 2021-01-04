#ifndef HUNGARY_ALGORITHM_H
#define HUNGARY_ALGORITHM_H

#include <vector>
#include "Adjacent_Matrix.h"

using namespace std;

class Hungary_Algorithm  //解决匹配问题的常用算法
{
public:
    Hungary_Algorithm(const Adjacent_Matrix &_Map)
    {
        //****************初始化**************//
        Map = _Map;
        M = Map.col_num;
        N = Map.row_num;
        p.resize(N, -1);
        vis.resize(N, false);
        //****************匹配**************//
        match_cnt = 0;
        for (int i = 0; i < M; i++)
        {
            vis = vector<bool>(N, false); //重置vis数组
            if (match(i))
                match_cnt++;
        }
        //****************结果重构**************//
        for (int i = 0; i < N; i++)
        {
            if (p[i] == -1)
                continue;
            match_res.emplace_back(make_pair(p[i], i));
        }
    }

private:
    bool match(int i)
    {
        for (int j = 0; j < N; j++)
            if (!vis[j] && Map[i][j]) //有边且未访问
            {
                vis[j] = true;                 //记录状态为访问过
                if (p[j] == -1 || match(p[j])) //如果暂无匹配，或者原来匹配的左侧元素可以找到新的匹配
                {
                    p[j] = i;    //当前左侧元素成为当前右侧元素的新匹配
                    return true; //返回匹配成功
                }
            }
        return false; //循环结束，仍未找到匹配，返回匹配失败
    }

public:
    vector<pair<int, int>> match_res; //最大匹配结果
    int match_cnt;                    //最大匹配数

private:
    Adjacent_Matrix Map; //邻接矩阵存图
    int M, N;            //M, N分别表示左、右侧集合的元素数量
    vector<int> p;       //记录当前右侧元素所对应的左侧元素
    vector<bool> vis;    //记录右侧元素是否已被访问过
};

#endif // defined HUNGARY_ALGORITHM_H