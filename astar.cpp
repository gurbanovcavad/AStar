#include <bits/stdc++.h>

#define int long long
#define pi 3.14159265358979323846
using namespace std;
using ll = long long;
using ld = long double;
const int N = 2e5 + 5, M = 1e9 + 7, inf = 1e9;
const char nl = '\n';
// holds neighbors of a node with corresponding costs (g[u] -> {v, w} -> means u -> v with a w cost)
vector<array<int, 2>> graph[N];
// coordinates
int x[N], y[N], source, destination, n, m;
// holds current cost (the cost to reach that node -> f(n)) and a node, and I used a comparator so that the node with the smallest cost stands on the top of the queue 
priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q; 
// to find the path we keep track of nodes' parents 
int par[N];
// to find the distance to each node
int dis[N];
int expanded = 0, pushes = 1, max_frontier = 0;

int manhattan(int node) {
    return abs(x[destination] - x[node]) + abs(y[destination] - y[node]);
}

int euclidean(int node) {
    return (int) sqrt((x[destination] - x[node]) * (x[destination] - x[node]) + (y[destination] - y[node]) * (y[destination] - y[node]));
}

vector<int> astar(int mode) {
    // to prevent infinite run 
    bool vis[N];
    vector<int> path;
    // clear the priority queue 
    while(!q.empty()) q.pop();
    // initialize the queue with the source node
    int f = 0;
    if(mode == 1) f += manhattan(source);
    else if(mode == 2) f += euclidean(source);
    q.push({f, source});
    while(!q.empty()) {
        max_frontier = max(max_frontier, (int) q.size());
        // get the node with the smallest cost  
        int cur_node = q.top()[1], cost = q.top()[0]; q.pop();
        vis[cur_node] = 1, expanded++;
        // check if we have reached the destination node and create the path to that node
        if(cur_node == destination) {
            int u = destination;
            do {
                path.push_back(u);
                u = par[u];
            } while(u != source);
            path.push_back(source);
            reverse(path.begin(), path.end());
            return path;
        }
        // add neighbor nodes to the queue 
        for(auto &t: graph[cur_node]) {
            int to = t[0], w = t[1];
            if(vis[to]) continue;
            par[to] = cur_node;
            if(mode == 1) f += manhattan(to);
            else if(mode == 2) f += euclidean(to);
            dis[to] = dis[cur_node] + w;
            f = dis[to];
            q.push({f, to});
            pushes++;
        }
    }
    return {};
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    // get the input
    // n is the number of nodes
    int n = 0;
    string l;
    cin >> l;
    while(1) {
        // node's id, a = x_coordinate, b = y_coordinate
        int comma = 0, id, a, b;
        for(int i = 0, sz = l.size(); i < sz; i++) {
            if(l[i] == ',') comma++;
        }
        if(comma == 2 || l[0] == 'S') break;
        int cur = 0;
        for(int i = 0, sz = l.size(); i < sz; i++) {
            if(l[i] == ',') {
                id = cur;
                cur = 0;
                continue;
            }
            cur *= 10;
            cur += (l[i] - '0');
        }
        a = cur / 10, b = cur % 10;
        x[id] = a, y[id] = b;
        n = max(n, id);
        cin >> l;
    }
    while(l[0] != 'S') {
        int cur = 0;
        vector<int> edge;
        for(int j = 0, sz = l.size(); j < sz; j++) {
            if(l[j] == ',') {
                edge.push_back(cur);
                cur = 0;
                continue;
            }
            cur *= 10;
            cur += (l[j] - '0');
        }
        // add edges to the graph
        graph[edge[0]].push_back({edge[1], cur});
        graph[edge[1]].push_back({edge[0], cur});
        cin >> l;
    }
    source = 0, destination = 0;
    for(int i = 2, sz = l.size(); i < sz; i++) {
        source *= 10;
        source += (l[i] - '0');
    }
    cin >> l;
    for(int i = 2, sz = l.size(); i < sz; i++) {
        destination *= 10;
        destination += (l[i] - '0');
    }
    // 0 -> ucs mode, 1 -> Euclidean, 2 -> Manhattan 
    for(int mode = 0; mode < 3; mode++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        // fill parent array (par[i] = -1 means we haven't expanded i node)
        for(int i = 1; i <= n; i++) par[i] = -1;
        vector<int> path;
        if(source == destination) {
            path = {source};
            pushes = 0;
        } else {
            path = astar(mode);
        }
        // output
        cout << "MODE: " << (mode == 0 ? "UCS" : mode == 1 ? " A* Manhattan" : "A* Euclidean") << nl;
        cout << "Optimal cost: "; 
        if(path.empty()) cout << "NO PATH\n";
        else cout << dis[destination] << nl;
        if(!path.empty()) {
            cout << "Path: ";
            for(int i = 0, sz = path.size(); i < sz; i++) {
                cout << path[i] << ' ';
            }
            cout << nl;
        } 
        cout << "Expanded: " << expanded << nl;
        cout << "Pushes: " << pushes << nl;
        cout << "Max frontier: " << max_frontier << nl;
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = end_time - start_time;
        ld seconds = chrono::duration_cast<chrono::duration<double>>(duration).count();
        ll microseconds = duration.count();
        cout << "Runtime (s): " << seconds << nl;   
        cout << "Runtime (s * 10^-6): " << microseconds << nl << nl;   
    }
    return 0;
}