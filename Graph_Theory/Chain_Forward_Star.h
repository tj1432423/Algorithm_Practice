#ifndef CHAIN_FORWARD_STAR_H
#define CHAIN_FORWARD_STAR_H

#include <vector>

using namespace std;

class Chain_Forward_Star //链式前向星
{
private:
    struct Edge
    {
        Edge(int _from = -1, int _to = -1, float _w = 0.0, int _next = -1) : from(_from), to(_to), w(_w), next(_next) {} //默认指向无效端点、无效边，默认权重为0
        int to;                                                                                                          //边的终点
        int w;                                                                                                           //边的权重
        int next;                                                                                                        //同一顶点的下一条边的边号
        int from;                                                                                                        //边的起点（标准的链式前向星无此属性,此属性的加入，可更方便于边的遍历）
    };

public:
    void add_edge(int from, int to, float w)
    {
        if (from >= head.size())
            head.resize(from + 1, -1); //对起点集进行扩容，新的起点指向的边的默认索引为-1，即不存在任何边
        if (to >= head.size())
            head.resize(to + 1, -1);                 //对起点集进行扩容，新的起点指向的边的默认索引为-1，即不存在任何边
        edges.emplace_back(from, to, w, head[from]); //新增一条边，边权为w   //该边的起点为from，终点为to  //把本起点当前指向的第一条边设置为本边的下一条边，
        head[from] = edges.size() - 1;               //当前边成为当前起点新的第一条边
    }

    int find_edge(int from, int to)
    {
        if (from >= head.size())
            return -1;
        for (int i = head[from]; i != -1; i = edges[i].next)
        {
            if (edges[i].to == to)
                return i;
        }
        return -1;
    }

    vector<Edge> edges; //所有边的集合
    vector<int> head;   //索引为顶点号，存的数据对应该顶点出发的第一条边的边号
};

#endif // defined CHAIN_FORWARD_STAR_H