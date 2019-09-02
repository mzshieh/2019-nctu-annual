#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct SCC{
  int n, d=0, cnt=0;
  vector<vector<int>> edg;
  vector<int> com, dfn, low;
  stack<int> S;
  SCC(int _n) : n(_n), edg(n+1), com(n+1, 0), dfn(n+1, 0), low(n+1){}
  void add(int u, int v){
    edg[u].push_back(v);
  }
  void dfs(int u){
    dfn[u]=low[u]=++d;
    S.push(u);
    for(int v : edg[u]){
      if( !dfn[v] ) dfs(v);
      if( !com[v] ) low[u]=min(low[u], low[v]);
    }
    if( dfn[u]==low[u] ){
      cnt++;
      for(int v; v=S.top(), S.pop(), com[v]=cnt, v!=u; );
    }
  }
  void operator()(){//0-base or 1-base
    for(int i=1; i<=n; i++) if( !dfn[i] ) dfs(i);
  }
};


int main()
{
  int n,m;
  scanf("%d %d", &n, &m);
  SCC scc(2*n);

  for(int i,u,j,v; m > 0; m--)
  {
    scanf("%d %d %d %d", &i, &u, &j, &v);
    scc.add(2*i-u, 2*j-v);
  }

  for(int i = 1; i <= n; i++)
    scc.add(2*i, 2*i-1);

  scc();
  bool ans = true;
  for(int i = 1; i <= n; i++)
    if( scc.com[2*i] == scc.com[2*i-1] )
      ans = false;

  puts(ans ? "YES" : "NO");
  return 0;
}
