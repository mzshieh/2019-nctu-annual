#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int INF = (1 << 30) - 1;

struct edge
{
    int u, v, w;

    edge(int _u = 0, int _v = 0, int _w = 0)
    {
        u = _u, v = _v, w = _w;
    }
};

bool sol()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<edge> edges;
    for(int t=0; t<m; t++)
    {
        int i, u, j, v;
        scanf("%d%d%d%d", &i, &u, &j, &v);
        edges.push_back(edge(j, i, v-u));
    }

    n++;
    for(int i=1; i<n; i++)
        edges.push_back(edge(0, i, 0));
    m=edges.size();

    for(int i=0; i<m; i++)
        if(edges[i].u==edges[i].v)
        {
            if(edges[i].w<0)
                return false;
            swap(edges[i], edges.back());
            edges.pop_back();
            i--;
						m--;
        }
    m=edges.size();

    vector<int> d(n, INF);
    d[0]=0;
    for(int i=1; i<=n; i++)
        for(edge &e: edges)
            if(d[e.u]!=INF && (d[e.v]==INF || d[e.v]>d[e.u]+e.w))
            {
                d[e.v]=d[e.u]+e.w;
                if(i==n)
                    return false;
            }
    return true;
}

int main()
{
    printf("%s\n", sol()?"YES":"NO");
}
