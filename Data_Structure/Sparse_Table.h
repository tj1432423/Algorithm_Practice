#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <vector>

using namespace std;

class Sparse_Table
{
public:
    Sparse_Table(vector<float> &data)
    {
        n = data.size();
        log2.resize(n + 1, 0);
        for (int i = 2; i <= n; i++)
        {
            log2[i] = log2[i / 2] + 1;
        }

        f = vector<vector<float>>(n, vector<float>(log2[n] + 1, 999999999999));
        for (int i = 0; i < n; i++)
        {
            f[i][0] = data[i];
        }
        for (int i = 1; i <= log2[n]; i++)
        {
            for (int j = 0; j + bin(i) - 1 < n; j++)
            {
                f[j][i] = max(f[j][i - 1], f[j + bin(i - 1)][i - 1]);
            }
        }
    }

    float interval_max_num(int i, int j)
    {
        if(i>j){
            printf("Fatel error !!! The first index should smaller than the second index !!!\n");
        }
        int s = log2[j - i + 1];
        return max(f[i][s], f[j - bin(s) + 1][s]);
    }

private:
    int bin(int x)
    {
        return 1 << x;
    }

private:
    int n;
    vector<int> log2;
    vector<vector<float>> f;
};

#endif // defined SPARSE_TABLE_H