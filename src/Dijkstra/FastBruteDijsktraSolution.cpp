#include <bits/stdc++.h>

namespace FastBruteForce {
  template< typename T >
  class Dijkstra {
  private:
  public:
    int n, s;
    std::vector< std::vector< std::pair< int, T > > > g;
    std::vector< T > dis;
    std::vector< int > dad;
    Dijkstra(){};
    Dijkstra(int _n, int _s) {
      n = _n;
      s = _s;
      g.resize(n, std::vector< std::pair<int, T > >());
      dis.resize(n, std::numeric_limits< T > :: max());
      dis[s] = 0;
      dad.resize(n, -1);
    }
    void addEdge(int x, int y, T w) {
      g[x].emplace_back(std::make_pair(y, w));
    }
    void preRun(int _s) {
      s = _s;
      dad.assign(n, -1);
      std::priority_queue< std::pair<T, int> > q;
      dis[s] = 0;
      q.push(std::make_pair(-dis[s], s));
      while(!q.empty()) {
        std::pair< T, int > foo = q.top(); q.pop();
        int x = foo.second;
        T c = -foo.first;
        if(dis[x] != c) continue;
        for(auto p : g[x]) {
          int y = p.first;
          T w = p.second;
          if(dis[y] > dis[x] + w) {
            dis[y] = dis[x] + w;
            dad[y] = x;
            q.push(std::make_pair(-dis[y], y));
          }
        }
      }
    }
    void addEdgeDynamic(int _x, int _y, int _w) {
      g[_x].emplace_back(std::make_pair(_y, _w));
      std::priority_queue< std::pair<T, int> > q;
      q.push(std::make_pair(-dis[_x], _x));
      while(!q.empty()) {
        std::pair< T, int > foo = q.top(); q.pop();
        int x = foo.second;
        T c = -foo.first;
        if(dis[x] != c) continue;
        for(auto p : g[x]) {
          int y = p.first;
          T w = p.second;
          if(dis[y] > dis[x] + w) {
            dis[y] = dis[x] + w;
            dad[y] = x;
            q.push(std::make_pair(-dis[y], y));
          }
        }
      }
    }
  };
};

using namespace std;

int main() {
  int n, m, s; scanf("%d %d %d", &n, &m, &s);
  FastBruteForce::Dijkstra< long long > g(n, s - 1);
  for(int i = 0; i < m; ++i) {
    int x, y, w; scanf("%d %d %d", &x, &y, &w); 
    g.addEdgeDynamic(x - 1, y - 1, w);
  }
  int q; scanf("%d", &q);
  for(int i = 0; i < q; ++i) {
    int a, b, c, x; scanf("%d %d %d %d", &a, &b, &c, &x);
    g.addEdgeDynamic(a - 1, b - 1, c);
    printf("%lld\n", g.dis[x - 1]);
  }
  return 0;
}