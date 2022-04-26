﻿#include <iostream>
#include "Graph.h"
#include <thread>
using namespace std;

int main()
{
	Graph g(8, "../../../vis/commands.js");
	g.AddEdge(0, 1, 1);
	g.AddEdge(0, 2, 10);
	g.AddEdge(3, 2, 1);
	g.AddEdge(1, 3, 5);
	g.AddEdge(4, 3, 1);
	g.AddEdge(4, 6, 1);
	g.AddEdge(0, 5, 7);
	g.AddEdge(1, 6, 1);
	g.AddEdge(5, 7, 4);

	g.SaveGraph();
	cout << g.BFS(0, 4) << endl;
	return 0;
}
