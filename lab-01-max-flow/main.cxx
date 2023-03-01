#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph
{
    int _n;
    
    // bandwidth matrix
    vector<vector<int>> _c; 
public:
    Graph(int n): _n(n)
    {
        _c.resize(n);
        for (auto& row : _c)
            row.resize(n);
    }

    void setBandwidth(int a, int b, int v)
    {
        _c[a - 1][b - 1] = v;
    }

    int findMaxFlow(int s, int t) 
    {
        s -= 1; t -= 1;

        int maxFlow = 0;

        while (true) 
        {
            vector<int> path;
        
            const bool hasPath = bfs(s, t, path);
            if (!hasPath)
                break;

            int augFlow = int(1e9);
            
            int p = t;
            while (p != s)
            {
                augFlow = min(augFlow, _c[path[p]][p]);
                p = path[p];
            }

            p = t;
            while (p != s)
            {
                _c[path[p]][p] -= augFlow;
                _c[p][path[p]] += augFlow;

                p = path[p];
            }

			printPath(s, t, path);

            print();

            maxFlow += augFlow;
        }

        return maxFlow;
    }

    bool bfs(int s, int t, vector<int>& path) 
    {
        path.resize(_n, -1);

        vector<bool> used(_n, false);
        queue<int> q;

        used[s] = true;
        q.push(s);

        while(!q.empty()) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < _n; i++)
            {
                if (!used[i] && _c[v][i] > 0) {
                    path[i] = v;
                    used[i] = true;
                    q.push(i);
                }
            }
        }

        return used[t];
    }

	void printPath(int s, int t, vector<int>& rpath)
	{
		vector<int> path;
		
		int p = t;
		path.push_back(p + 1); // ( ... + 1 ) cause I want start from 1 
		while (p != s) {
			path.push_back(rpath[p] + 1); // ( ... + 1 ) cause I want start from 1 
			p = rpath[p];
		}
		reverse(path.begin(), path.end());


		cout << "path: ";

		cout << path[0];
		for (int i = 1; i < path.size(); ++i)
			cout << " -> " << path[i];

		cout << endl;

	}

    void print()
    {
        for(auto& row : _c) {
            for (auto v : row)
                cout << setw(3) << v;
            cout << endl; 
        }

        cout << endl;
    }
};

int main()
{
    int n = 0, m = 0, s = 0, t = 0;
    cin >> n >> m >> s >> t;
    

    Graph graph(n);
    for (int i = 0; i < m; i++) 
    {
        int a = 0, b = 0, v = 0;
        cin >> a >> b >> v;
        graph.setBandwidth(a, b, v);
    }

    graph.print();

    int maxFlow = graph.findMaxFlow(s, t);
    cout << "max flow = " << maxFlow << endl;
}
