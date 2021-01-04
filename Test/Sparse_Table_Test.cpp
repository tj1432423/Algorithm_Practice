#include <iostream>

#include "../Data_Structure/Sparse_Table.h"

using namespace std;

int main()
{
    printf("Hello word !!!\n");
    vector<float> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Sparse_Table sparse_table(nums);
    for (int j = 0; j < nums.size(); j++)
    {
        for (int i = 0; i <= j; i++)
        {
            cout << "The max num between index " << i << " and index " << j << " is " << sparse_table.interval_max_num(i, j) << " ." << endl;
        }
    }

    cout << "--------------------" << endl;
    cout << "this is the end" << endl;

    system("pause");
    return 0;
}