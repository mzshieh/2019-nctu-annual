#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-10;

struct simplex{
  int nv;
  vector<vector<double>> A;
  vector<double> b, c, x;
  simplex(int _nv) : nv(_nv), c(nv, 0), x(nv, 0){}
  void append(){
    A.push_back(vector<double>(nv, 0));
    b.push_back(0);
  }
  double operator()(){
    int n=A.size(), m=nv+1, r=n, s=m-1;
    vector<vector<double>> d(n+2, vector<double>(nv+2, 0));
    vector<int> ix(n+m);
    for(int i=0; i<n+m; i++) ix[i]=i;
    for(int j=0; j<m-1; j++) d[n][j]=c[j];
    for(int i=0; i<n; i++){
      for(int j=0; j<m-1; j++) d[i][j]=-A[i][j];
      d[i][m-1]=1; d[i][m]=b[i];
      if( d[r][m]>d[i][m] ) r=i;
    }
    for(d[n+1][m-1]=-1; ; ){
      if( r<n ){
        swap(ix[s], ix[r+m]);
        d[r][s]=1/d[r][s];
        for(int j=0; j<=m; j++) if( j!=s ) d[r][j]*=-d[r][s];
        for(int i=0; i<=n+1; i++) if( i!=r ){
          for(int j=0; j<=m; j++) if( j!=s ) d[i][j]+=d[r][j]*d[i][s];
          d[i][s]*=d[r][s];
        }
      }
      r=s=-1; double tmp;
      for(int j=0; j<m; j++) if( (s<0 || ix[s]>ix[j]) && (d[n+1][j]>EPS || (d[n+1][j]>-EPS && d[n][j]>EPS)) ) s=j;
      if( s<0 ) break;
      for(int i=0; i<n; i++) if( d[i][s]<-EPS )
        if( r<0 || (tmp=d[r][m]/d[r][s]-d[i][m]/d[i][s])<-EPS || (tmp<EPS && ix[r+m]>ix[i+m]) ) r=i;
      if( r<0 ) return -1;//not bounded
    }
    if( d[n+1][m]<-EPS ) return -2;//not executable
    double ans=0;
    for(int i=m; i<n+m; i++) if( ix[i]<m-1 ) ans+=c[ ix[i] ]*(x[ ix[i] ]=d[i-m][m]);
    return ans;
  }
};

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  simplex S(n+5);// ans kids chairs
  S.c[0]=1;

  for(int i=1; i<=4; i++)
  {
    S.append();
    S.A.back()[0]=1;
    S.A.back()[i+n]=-1;
  }

  vector<vector<int>> e;

  for(; m>0; m--)
  {
    int i, j, u, v;
    scanf("%d%d%d%d", &i, &u, &j, &v);
    S.append();
    S.A.back()[i]++;
    S.A.back()[j]--;
    S.A.back()[u+n]+=u>0;
    S.A.back()[v+n]-=v>0;
  }

  double ans=S();
  printf(ans==-1 || ans>EPS ? "YES\n" : "NO\n");
}
