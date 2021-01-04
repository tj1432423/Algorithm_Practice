#include <iostream>

#include "../Graph_Theory/Prim.h"
#include "../Graph_Theory/Kruskal.h"

using namespace std;

int main()
{
    printf("Hello word !!!\n");
    Chain_Forward_Star grath;
    grath.add_edge(0, 1, 4);
    grath.add_edge(0, 2, 3);
    grath.add_edge(0, 5, 1);
    grath.add_edge(2, 5, 5);
    grath.add_edge(1, 3, 7);
    grath.add_edge(5, 3, 3);
    grath.add_edge(5, 4, 2);
    grath.add_edge(4, 3, 9);

    grath.add_edge(1, 0, 4);
    grath.add_edge(2, 0, 3);
    grath.add_edge(5, 0, 1);
    grath.add_edge(5, 2, 5);
    grath.add_edge(3, 1, 7);
    grath.add_edge(3, 5, 3);
    grath.add_edge(4, 5, 2);
    grath.add_edge(3, 4, 9);

    cout << "--------Prim------------" << endl;
    Prim prim(grath);
    cout << "The Min_Cost is " <<prim.cost<< endl;
    for (int i = 0; i < prim.parent.size(); i++)
    {
        printf("p[%d] = %d \n", i, prim.parent[i]);
    }

    cout << "--------Kruskal------------" << endl;
    Kruskal kruskal(grath);
    cout << "The Min_Cost is " <<kruskal.cost<< endl;
    for (int i = 0; i < kruskal.parent.size(); i++)
    {
        printf("p[%d] = %d \n", i, kruskal.parent[i]);
    }
    cout << "--------------------" << endl;
    cout << "this is the end" << endl;

    system("pause");
    return 0;
}