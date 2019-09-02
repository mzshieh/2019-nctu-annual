#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long lld;
const lld INF=1LL<<60;


struct Edge
{
    int u, v, c1, c2;
    Edge(int _u=0, int _v=0, int _c1=0, int _c2=0):u(_u),v(_v),c1(_c1),c2(_c2)
    {
    }
};

void update(int &l, int &r, int c1, int c2)
{
    //fprintf(stderr, "%d %d\n", l, r);
    if( c2 < 0 )
        r = (l+r)/2;
    else
        l = (l+r)/2+1;
}

bool sol()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<Edge> edges;
    for(int t=0; t<m; t++)
    {
        int i, u, j, v;
        scanf("%d%d%d%d", &i, &u, &j, &v);
        int c[3]= {};
        c[v]++;
        c[u]--;
        edges.push_back(Edge(j, i, c[1]*n, c[2]));
    }

    n++;
    for(int i=1; i<n; i++)
        edges.push_back(Edge(0, i, 0, 0));
    m=edges.size();

    int l = 1, r = n*n;

    while(l<r)
    {
        lld mid = (l+r)/2;
        //fprintf(stderr, "mid=%d %d %lld\n",  l, r, mid);
        vector<lld> d(n, INF);
        vector<int> p(n, -1);
        d[0]=0;
        int ch=-1;
        for(int i=1; i<=n; i++)
            for(int j=0; j<m; j++)
            {
                Edge &e=edges[j];
                lld w=e.c1+e.c2*mid;
                if( d[e.v]>d[e.u]+w )
                {
                    d[e.v]=d[e.u]+w;
                    p[e.v]=j;
                    if(i==n){
                        ch=j;
                        break;
                    }
                }
            }

        if(ch==-1)
            return true;
        for(int i=0; i<n; i++)
          ch=p[edges[ch].u];
        int c[3]= {};
        for(int cur=ch; ; )
        {
            c[1]+=edges[cur].c1;
            c[2]+=edges[cur].c2;
            cur=p[edges[cur].u];
            if(cur==ch)
                break;
        }
        update(l, r, c[1], c[2]);
    }
    return false;
}

int main()
{
    printf("%s\n", sol()?"YES":"NO");
}
