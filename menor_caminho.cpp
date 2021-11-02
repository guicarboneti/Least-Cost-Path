#include <bits/stdc++.h>

#define EPS 1E-6
#define MOD 1000000007
#define inf 0x3f3f3f3f
#define llinf 0x3f3f3f3f3f3f3f3f

#define fi first
#define se second
#define pb push_back
#define ende '\n'
#define esp ' '

#define all(x) (x).begin(), (x).end()
#define mset(x, y) memset(&x, (y), sizeof(x))

using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define N 11234
#define oo llinf

typedef pair<int, ll> edge;

vector<ll> d(N, oo), vis(N);
vector<vector<edge>> graph(N);

void dijkstra(int src)
{
    priority_queue<edge, vector<edge>, greater<edge>> Q;
    d[src] = 0;
    Q.push({0, src});
    while (!Q.empty())
    {
        auto [c, u] = Q.top();
        Q.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;
        for (auto [v, w] : graph[u])
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                Q.push({d[v], v});
            }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, c;
    cin >> n >> c;
    
    int start, end, dem;
    cin >> start >> end >> dem;

    while (c--) {
        int a, b, custo;
        cin >> a >> b >> custo;

        graph[a].push_back(make_pair(b, custo));
        graph[b].push_back(make_pair(a, custo));
    }

    dijkstra(start);

    cout << d[end] * dem << ende;

    return 0;
}