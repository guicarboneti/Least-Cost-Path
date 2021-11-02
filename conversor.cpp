#include <bits/stdc++.h>

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

#define N 200

typedef struct conexao {
    int a, b;   // sedes a e b;
    int c;      // custo de transmissão na conexão
} conexao;

vector<vector<ii>> graph(N);
vector<bool> visited(N);

bool dfs(int inicio, int fim) {
    stack<int> s;
    s.push(inicio);
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (u == fim) {
            return true; // Achou o vertice do fim
        }

        for (ii v : graph[u]) {
            if (!visited[v.fi]) {
                visited[v.fi] = true;
                s.push(v.fi);
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, c; 
    cin >> n >> c;

    int inicio, fim, dem;
    cin >> inicio >> fim >> dem;

    vector<conexao> arestas(N);

    // cout << n << esp << c << endl;

    // Lê todas as arestas
    while (c--) {
        int a, b, custo;
        cin >> a >> b >> custo;

        graph[a].push_back(make_pair(b, custo));
        graph[b].push_back(make_pair(a, custo));
    }

    // Confere se existe ao menos um caminho entre inicio e fim
    if (!dfs(inicio, fim)) {
        cout << "Não existe caminho possível entre as sedes " << inicio << " e " << fim << endl;
    }

    // Gera a equação a ser minimizada
    cout << "min: 0 ";
    for (int i = 1; i <= n; i++) {
        if (i == fim) {
            continue;
        }

        for (ii col : graph[i]) {
            if (col.fi == inicio) {
                continue;
            }

            cout << " + " << col.se*dem << "x" << i << 0 << col.fi;
        }
    }
    cout << ";" << endl;

    // 
    // Gera as restrições

    // Vértice inicial
    cout << "0";
    for (ii col : graph[inicio]) {
        cout << " + x" << inicio << 0 << col.fi;
    }
    cout << " = 1;" << endl;
    
    // Vértices intermediários
    for (int i = 1; i <= n; i++) {
        if (i == inicio || i == fim || graph[i].size() == 0) {
            continue;
        }

        cout << "0";
        for (ii col : graph[i]) {
            if (col.fi != inicio) {
                cout << " + x" << i << 0 << col.fi;
            }
        }
        for (ii col : graph[i]) {
            if (col.fi != fim) {
                cout << " - x" << col.fi << 0 << i;
            }
        }
        
        cout << " = 0;" << endl;
    }

    // Vértice final
    cout << "0";
    for (ii col : graph[fim]) {
        cout << " + x" << col.fi << 0 << fim;
    }
    cout << " = 1;" << endl;

    // Define as variáveis como inteiras
    vector<string> var;
    
    for (int i = 1; i < n; i++) {
        for (ii col : graph[inicio]) {
            var.push_back("x" + to_string(i) + to_string(0) + to_string(col.fi));
        }
    }

    cout << "int ";
    for (int i = 0; i < var.size() - 1; i++) {
        cout << var[i] << ", ";
    }
    cout << var[var.size()-1] << ";" << endl;
    
    return 0;
}