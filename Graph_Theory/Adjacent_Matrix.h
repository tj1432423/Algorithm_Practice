#ifndef ADJACENT_MATRIX_H
#define ADJACENT_MATRIX_H

#include <vector>

using namespace std;

class Adjacent_Matrix
{
public:
    Adjacent_Matrix(int _col_num = 0, int _row_num = 0)
    {
        col_num = _col_num;
        row_num = _row_num;
        mat = vector<vector<float>>(col_num, vector<float>(col_num));
    }
    void add_edge(int from, int to, float w)
    {
        mat[from][to] = w;
    }

    vector<float> &operator[](int from)
    {
        return mat[from];
    }

public:
    int col_num;
    int row_num;

private:
    vector<vector<float>> mat;
};

#endif // defined ADJACENT_MATRIX_H