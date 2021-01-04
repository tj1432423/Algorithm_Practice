#ifndef DIFFERENTIAL_CONSTRAINS_H
#define DIFFERENTIAL_CONSTRAINS_H

#include "SPFA.h"
#include <vector>
#include <map>

using namespace std;

class Differential_Constraints
{
public:
    Differential_Constraints(const vector<pair<pair<int, int>, float>> &constraints)
    {
        //*************输入示例************//
        // x1-x2<=3;
        // x2-x3<=-1;
        // x1-x3<=1;
        //
        // vector<pair<pair<int, int>, float>> constraints;
        // constraints.push_back(make_pair(make_pair(1, 3), 3));
        // constraints.push_back(make_pair(make_pair(2, 3), -2));
        // constraints.push_back(make_pair(make_pair(1, 3), 1));
        //
        //*************主程序************//
        Chain_Forward_Star grath;
        error_flag = false;
        for (int i = 0; i < constraints.size(); i++)
        {
            grath.add_edge(constraints[i].first.second, constraints[i].first.first, constraints[i].second);
            results[constraints[i].first.first] = 0;
            results[constraints[i].first.second] = 0;
        }
        for (auto &result : results)
        {
            grath.add_edge(0, result.first, 0.0);
        }
        SPFA spfa(grath, 0);
        if (spfa.negative_weight_loop)
        {
            error_flag = true;
            return;
        }
        for (auto &result : results)
        {
            result.second = spfa.dist[result.first];
        }
    }

public:
    map<int, float> results;
    bool error_flag;
};

#endif // defined DIFFERENTIAL_CONSTRAINS_H