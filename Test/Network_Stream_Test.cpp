#include <iostream>

#include "../Network_Stream/Ford_Fulkerson.h"
#include "../Graph_Theory/Chain_Forward_Star.h"
#include "../Network_Stream/Edmond_Karp.h"
#include "../Network_Stream/Dinic.h"

using namespace std;

int main()
{
    printf("Hello word !!!\n");
    Chain_Forward_Star grath;
    grath.add_edge(1, 3, 2);
    grath.add_edge(1, 2, 3);
    grath.add_edge(2, 3, 2);
    grath.add_edge(2, 4, 3);
    grath.add_edge(4, 3, 2);

    cout << "--------Ford_Fulkerson------------" << endl;
    Ford_Fulkerson ford_fulkerson(grath, 1, 3);
    cout << "The max flow is " << ford_fulkerson.max_flow << endl;
    cout << "--------Edmond_Karp------------" << endl;
    Edmond_Karp edmond_karp(grath, 1, 3);
    cout << "The max flow is " << edmond_karp.max_flow << endl;
    cout << "--------Dinic------------" << endl;
    Dinic dinic(grath, 1, 3);
    cout << "The max flow is " << dinic.max_flow << endl;

    cout << "--------------------" << endl;
    cout << "this is the end" << endl;

    system("pause");
    return 0;
}