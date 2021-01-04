#include <iostream>

#include "../Data_Structure/Binary_tree_Creater.h"
#include "../Graph_Theory/Lowest_Common_Ancestor.h"

using namespace std;

int main()
{
    printf("Hello word !!!\n");
    vector<string> nums = {"1", "2", "3", "4", "5", "Null", "6", "7", "Null", "8", "Null", "Null", "Null", "Null", "Null", "Null", "Null", "Null", "Null", "9"};
    Binary_tree_Creater b_tree(nums);

    //Lowest_Common_Ancestor lca(b_tree.root, b_tree.nodes[7], b_tree.nodes[19]);
    Lowest_Common_Ancestor lca(b_tree.root);
    

    cout << "The value of lowest_common_ancestor is " << lca.find_lca(b_tree.nodes[0], b_tree.nodes[19])->val << endl;

    cout << "--------------------" << endl;
    cout << "this is the end" << endl;

    system("pause");
    return 0;
}