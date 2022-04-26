#include "Graph.h"

Graph::Graph(int N, string fName) : N(N)
{
	f.open(fName);
	f << "window.prog=`\n";
	visited.resize(N, false);
	edgesFrom.resize(N);
	dlina.resize(N);
}

Edge& Graph::AddEdge(int from, int to, int w) {
	Edge* e = new Edge();
	e->a = from;
	e->b = to;
	e->w = w;
	edges.push_back(e);
	edgesFrom[from].push_back(e);
	edgesFrom[to].push_back(e);

	return *e;
}

void Graph::SaveGraph() {
	for (int i = 0; i < N; i++) {
		f << i << endl;
	}
	for (Edge* r : edges) {
		f << *r << ",label=" << r->w << endl;
	}
	f << "draw\n";
}

int Graph::BFS(int start, int end)
{
	priority_queue<Point> q;
	Point go{ 0,start };
	q.push(go);
	while (!q.empty()) {
		if (visited[q.top().number]) {
			q.pop();
			continue;
		}
		f << q.top().number << ",color=lime\n";
		int z = q.top().number;
		q.pop();
		for (Edge* r : edgesFrom[z]) {
			int v = r->other(z);
			if (visited[v]) {
				f << "p,вершина " << z << " уже посещена\n";
				f << "w,1000\n";
				continue;
			}
			else {
				if (dlina[v] != 0 && dlina[v] < dlina[z] + r->w)
					continue;
				dlina[v] = dlina[z] + r->w;
				Point go{ dlina[v],v };
				q.push(go);
				f << "p,вершина " << z << " еще не посещена\n";
				f << *r << ",color=red\n";
				f << v << ",color=blue\n";
				f << "w,1000\n";
				f << v << ",shape=box,color=yellow,label=" << v << ";dist:" << dlina[v] << "\n";
			}
		}
		visited[z] = true;
		f << "p,Все ребра из вершины " << z << " просмотрены\n";
		f << z << ",color=green;white\n";
		f << "w,1000\n";
	}

	f << "p,Минималный путь до вершины " << end << " : " << dlina[end] << endl;
	return dlina[end];
}

Graph::~Graph() {
	f << "`";
	f.close();

	for (int i = 0; i < edges.size(); i++) {
		delete edges[i];
	}
}
