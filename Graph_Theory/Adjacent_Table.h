#ifndef ADJACENT_TABLE_H
#define ADJACENT_TABLE_H

#include <vector>
#include <map>

using namespace std;

class Adjacent_Table
{
public:
    Adjacent_Table()
    {
        row_num = 0;
    }
    void add_edge(int from, int to, float w)
    {
        if (from >= mat.size())
        {
            mat.resize(from + 1);
            row_num = from + 1;
        }

        mat[from][to] = w;
    }

    map<int, float> &operator[](int from)
    {
        if (from >= mat.size())
        {
            mat.resize(from + 1);
            row_num = from + 1;
        }

        return mat[from];
    }

public:
    int row_num;

private:
    vector<map<int, float>> mat;
};

#endif // defined ADJACENT_TABLE_H