#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long lld;

const lld INF=(1LL<<62)-1;

lld gcd(lld a, lld b)
{
    return a%b==0?b:gcd(b, a%b);
}

struct Frac
{
    lld p, q;
    Frac(lld _p=1, lld _q=1):p(_p),q(_q)
    {
        lld g=gcd(p, q);
        p/=g;
        q/=g;
    }
    bool operator<(Frac r)
    {
        return p*r.q<r.p*q;
    }
    bool operator<=(Frac r)
    {
        return p*r.q<=r.p*q;
    }
    Frac max(Frac r)
    {
        return *this<r?r:*this;
    }
    Frac min(Frac r)
    {
        return *this<r?*this:r;
    }
};

struct Edge
{
    int u, v, c1, c2;
    Edge(int _u=0, int _v=0, int _c1=0, int _c2=0):u(_u),v(_v),c1(_c1),c2(_c2)
    {
    }
};

bool update(Frac &l, Frac &r, int c1, int c2)
{
    if(c1==0 || c2==0)
        return c1+c2>=0;
    else if(c1*c2>0)
        return c1>0;
    else
    {
        Frac f(abs(c1), abs(c2));
        if(c2>0)
            l=l.max(f);
        else
            r=r.min(f);
        return true;
    }
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
        edges.push_back(Edge(j, i, c[1], c[2]));
    }

    n++;
    for(int i=1; i<n; i++)
        edges.push_back(Edge(0, i, 0, 0));
    m=edges.size();

    Frac l(1, n-1), r(n-1, 1);

    for(int i=0; i<m; i++)
    {
        Edge &e=edges[i];
        if(e.u!=e.v)
            continue;
        if(!update(l, r, e.c1, e.c2))
            return false;
        swap(edges[i], edges.back());
        edges.pop_back();
        i--;
    }
    m=edges.size();

    while(l<=r)
    {
        Frac mid(l.p*r.q+r.p*l.q, l.q*r.q*2);
        //fprintf(stderr, "mid=%lld/%lld\n",  mid.p, mid.q);
        vector<lld> d(n, INF);
        vector<int> p(n, -1);
        d[0]=0;
        int ch=-1;
        for(int i=1; i<=n; i++)
            for(int j=0; j<m; j++)
            {
                Edge &e=edges[j];
                lld w=e.c1*mid.q+e.c2*mid.p;
                if(d[e.u]!=INF && (d[e.v]==INF || d[e.v]>d[e.u]+w))
                {
                    d[e.v]=d[e.u]+w;
                    p[e.v]=j;
                    if(i==n)
                        ch=j;
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
        if(!update(l, r, c[1], c[2]))
            return false;
    }
    return false;
}

int main()
{
    printf("%s\n", sol()?"YES":"NO");
}
