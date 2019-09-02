#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int main()
{
  int n,m;
  scanf("%d %d", &n, &m);
  vector<vector<int>> e(2*n+2);
  vector<int> ind(2*n+2);
  for(int i,u,j,v; m > 0; m--)
  {
    scanf("%d %d %d %d", &i, &u, &j, &v);
    if( 2*i+u == 2*j+v )
      continue;
    e[2*i+u].push_back(2*j+v);
    ind[2*j+v]++;
  }

  for(int i = 1; i <= n; i++)
  {
    e[2*i].push_back(2*i+1);
    ind[2*i+1]++;
  }
  queue<int> Q;

  for(int i = 1; i <= n; i++)
    if( ind[2*i] == 0 )
      Q.push(2*i);

  int cnt = 0;
  for(; !Q.empty(); Q.pop())
  {
    int top = Q.front();
    cnt++;
    for(int v : e[top])
      if( --ind[v] == 0 )
        Q.push(v);
  }

  puts(cnt == 2*n ? "YES" : "NO");
  return 0;
}
