#include <iostream>
#include <vector>
#include <forward_list>
#include <unordered_map>
using namespace std;

template<typename T>
class Graph {
private :
    struct Vertex {
        forward_list<T> vertex;
        bool color;
    };
    typedef unordered_map<T, Vertex> adjList;
    adjList Adj;
public :
    void insertEdge(T x, T y) {Adj[x].vertex.push_front(y);}
    void deleteEdge(T x, T y) {Adj[x].vertex.remove(y);}
    void BFS(T s);
    void DFS();
};

template<typename T>
void Graph<T>::BFS(T s) {
    vector<T> que;
    for (auto i : Adj)
        i.second.color = false;
    Adj[s].color = true;
    cout << s << ends;
    que.insert(que.begin(), s);
    while (!que.empty()) {
        T u = que.back();
        que.pop_back();
        for (auto i : Adj[u].vertex)
            if (Adj[i].color == false) {
                Adj[i].color = true;
                cout << i << ends;
                que.insert(que.begin(), i);
            }
    }
}

template<typename T>
void Graph<T>::DFS() {
    vector<T> stk;
    for (auto i : Adj)
        i.second.color = false;
    for (auto u : Adj)
        if (u.second.color == false) {
            T v = u.first;
            while (1) {
                if (Adj[v].color == false) {
                    cout << v << ends;
                    Adj[v].color = true;
                }
                auto p = Adj[v].vertex.begin();
                for ( ; p != Adj[v].vertex.end(); ++p)
                    if (Adj[*p].color == false) {
                        stk.push_back(v);
                        v = *p;
                        break;
                    }
                if (p == Adj[v].vertex.end() && !stk.empty()) {
                    v = stk.back();
                    stk.pop_back();
                }
                else if (stk.empty()) break;
            }
        }
}

int main(void) {
    Graph<char> mygraph;
    char a[] = {'u', 'u', 'x', 'v', 'y', 'w', 'w', 'z' },
         b[] = {'x', 'v', 'v', 'y', 'x', 'y', 'z', 'z' };
    for (int i = 7; i >= 0; --i) {
        mygraph.insertEdge(a[i], b[i]);
    }

    mygraph.DFS();
    return 0;
}
