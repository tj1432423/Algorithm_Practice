#include <iostream>

#include "../Graph_Theory/Adjacent_Matrix.h"
#include "../Graph_Theory/Adjacent_Table.h"
#include "../Graph_Theory/Bellman_Ford.h"
#include "../Graph_Theory/Chain_Forward_Star.h"
#include "../Graph_Theory/Differential_Constraints.h"
#include "../Graph_Theory/Dijkstra.h"
#include "../Graph_Theory/Hungary_Algorithm.h"
#include "../Graph_Theory/SPFA.h"
#include "../Graph_Theory/Kahn.h"
#include "../Graph_Theory/Key_Path_Algorithm.h"

using namespace std;

int main()
{
  printf("Hello word !!!\n");
  cout << "---------Build the Adjacent_Matrix Map-----------" << endl;
  Adjacent_Matrix adjacent_matrix(5, 5);
  adjacent_matrix.add_edge(1, 2, 1); // the first method to add edge
  adjacent_matrix.add_edge(1, 4, 1);
  adjacent_matrix.add_edge(2, 2, 1);
  adjacent_matrix.add_edge(3, 1, 1);
  adjacent_matrix.add_edge(3, 3, 1);
  adjacent_matrix[4][4] = 1; // the second method to add edge
  for (int i = 0; i < adjacent_matrix.row_num; i++)
  {
    for (int j = 0; j < adjacent_matrix.col_num; j++)
    {
      cout << adjacent_matrix[i][j] << "  ";
    }
    cout << endl;
  }

  cout << "---------------Hungary_Algorithm-------------------" << endl;
  Hungary_Algorithm hungary_algorithm(adjacent_matrix);
  for (int i = 0; i < hungary_algorithm.match_res.size(); i++)
  {
    cout << "The node " << hungary_algorithm.match_res[i].first << " match node " << hungary_algorithm.match_res[i].second << " ." << endl;
  }
  cout << "The max match num is " << hungary_algorithm.match_cnt << endl;

  cout << "---------Build the Adjacent_Table Map-----------" << endl;
  Adjacent_Table adjacent_table;
  adjacent_table.add_edge(1, 2, 1); // the first method to add edge
  adjacent_table.add_edge(1, 4, 1);
  adjacent_table.add_edge(2, 2, 1);
  adjacent_table.add_edge(3, 1, 1);
  adjacent_table.add_edge(3, 3, 1);
  adjacent_table[4][4] = 1; // the second method to add edge
  for (int i = 0; i < adjacent_table.row_num; i++)
  {
    for (auto end_point : adjacent_table[i])
    {
      cout << "The grath has a edge from " << i << " to " << end_point.first << " with weight " << end_point.second << " ." << endl;
    }
  }

  cout << "---------Build the Chain_Forward_Star Map-----------" << endl;
  Chain_Forward_Star grath;
  grath.add_edge(1, 2, 1.0);
  grath.add_edge(1, 3, 4.0);
  grath.add_edge(1, 4, 6.0);
  grath.add_edge(2, 4, 2.0);
  grath.add_edge(3, 4, 1.0);
  //grath.add_edge(4, 1, -5.0);  //negative_weight_loop
  for (int i = 0; i < grath.edges.size(); i++)
  {
    cout << "The grath has a edge from " << grath.edges[i].from << " to " << grath.edges[i].to << " with weight " << grath.edges[i].w << " ." << endl;
  }

  cout << "----------Bellman_Ford----------" << endl;
  Bellman_Ford bellman_ford(grath, 1);
  for (int i = 0; i < bellman_ford.dist.size(); i++)
  {
    cout << "the minimun dist from " << i << " to " << bellman_ford.start_index << " is " << bellman_ford.dist[i] << endl;
  }
  if (bellman_ford.negative_weight_loop)
    cout << "negative_weight_loop can be detected !!!" << endl;
  else
    cout << "negative_weight_loop can not be detected !!!" << endl;

  cout << "----------SPFA----------" << endl;
  SPFA spfa(grath, 1);
  for (int i = 0; i < spfa.dist.size(); i++)
  {
    cout << "the minimun dist from " << i << " to " << bellman_ford.start_index << " is " << bellman_ford.dist[i] << endl;
  }
  if (spfa.negative_weight_loop)
    cout << "negative_weight_loop can be detected !!!" << endl;
  else
    cout << "negative_weight_loop can not be detected !!!" << endl;

  cout << "----------Dijkstra----------" << endl;
  Dijkstra dijkstra(grath, 1);
  for (int i = 0; i < spfa.dist.size(); i++)
  {
    cout << "the minimun dist from " << i << " to " << bellman_ford.start_index << " is " << bellman_ford.dist[i] << endl;
  }

  cout << "----------Differential_Constraints----------" << endl;
  vector<pair<pair<int, int>, float>> constraints;
  constraints.push_back(make_pair(make_pair(1, 3), 3.0));
  constraints.push_back(make_pair(make_pair(2, 3), -2.0));
  constraints.push_back(make_pair(make_pair(1, 3), 1.0));
  //constraints.push_back(make_pair(make_pair(3, 1), -2.0));  //negative_weight_loop
  Differential_Constraints differential_constraints(constraints);
  if (differential_constraints.error_flag)
  {
    cout << "There is no result for this differential constraints problem !!!" << endl;
  }
  else
  {
    for (auto result : differential_constraints.results)
    {
      cout << "x[" << result.first << "] = " << result.second << endl;
    }
  }

  cout << "---------Build the Chain_Forward_Star Map-----------" << endl;
  Chain_Forward_Star grath2;
  grath2.add_edge(1, 2, 1.0);
  grath2.add_edge(2, 5, 4.0);
  grath2.add_edge(3, 2, 6.0);
  grath2.add_edge(4, 2, 2.0);
  grath2.add_edge(5, 6, 2.0);
  //grath2.add_edge(6, 1, 2.0);  //the loop
  for (int i = 0; i < grath2.edges.size(); i++)
  {
    cout << "The grath has a edge from " << grath2.edges[i].from << " to " << grath2.edges[i].to << " with weight " << grath2.edges[i].w << " ." << endl;
  }

  cout << "---------Kahn Test-----------" << endl;
  Kahn kahn(grath2);
  for (int i = 0; i < kahn.topology_list.size(); i++)
  {
    cout << "  ->  " << kahn.topology_list[i] << " ( " << kahn.topology_distance[kahn.topology_list[i]] << " ) ";
  }
  cout << endl;

  if (kahn.loop_judgement)
    cout << "There is a loop in the grath !!!" << endl;
  else
    cout << "There is no loop in the grath !!!" << endl;

  cout << "---------Build the Chain_Forward_Star Map-----------" << endl;
  Chain_Forward_Star grath3;
  grath3.add_edge(1, 2, 2.0);
  grath3.add_edge(1, 4, 1.0);
  grath3.add_edge(1, 5, 1.0);
  grath3.add_edge(5, 3, 1.0);
  grath3.add_edge(2, 3, 3.0);
  grath3.add_edge(4, 3, 8.0);
  grath3.add_edge(2, 4, 5.0);
  for (int i = 0; i < grath3.edges.size(); i++)
  {
    cout << "The grath has a edge from " << grath3.edges[i].from << " to " << grath3.edges[i].to << " with weight " << grath3.edges[i].w << " ." << endl;
  }

  cout << "--------Key_Path_Algorithm---------" << endl;
  Key_Path_Algorithm key_path_algorithm(grath3);
  for (int i = 0; i < key_path_algorithm.key_path.size(); i++)
  {
    cout << "  ->  " << key_path_algorithm.key_path[i] << " ( " << key_path_algorithm.earlist[key_path_algorithm.key_path[i]] << " , " << key_path_algorithm.latest[key_path_algorithm.key_path[i]] << " ) ";
  }
  cout << endl;

  cout << "this is the end" << endl;

  system("pause");

  return 0;
}