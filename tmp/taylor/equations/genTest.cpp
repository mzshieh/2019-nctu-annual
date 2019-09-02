#include<bits/stdc++.h>
#include"MillerRabin.hpp"

using namespace std;

#define ll long long

ll pow(ll a, int b, ll mod){
	if(b==0) return 1LL;
	if(b&1) return pow(a,b-1,mod)*a%mod;
	return pow(a*a%mod,b/2,mod);
}

inline ll inv(ll a, ll p){return pow(a,p-2,p);}

void dump(vector<vector<ll> >const& A){
	for(int i=0;i<A.size();++i){
		for(int j=0;j<A[i].size();++j)
			cout << A[i][j]<<" ";
		cout <<"\n";
	}
	cout <<"\n";
}

int invertible(vector<vector<ll> >A, ll p){
	ll n = A.size();
	for(int t=0;t<n;++t){
		// find good pvt
		int flag = 0;
		for(int i=t;i<n;++i)
			if(A[i][t]%p != 0){
				for(int j=t;j<n;++j)
					swap(A[t][j],A[i][j]);
				flag = 1;
				break;
			}
		if(!flag) return 0;
		for(int i=t+1;i<n;++i){
			ll c = A[i][t]*inv(A[t][t],p)%p;
			for(int j=t;j<n;++j)
				A[i][j] = (A[i][j]+p-c*A[t][j]%p)%p;
		}
	}
	return 1;
}

int main(int argc, char* argv[]){
	if(argc<4) return 1;
	srand(time(NULL));
	string in = argv[1], out = argv[2];
	fstream fin(in,ios::out);
	fstream fout(out,ios::out);
	ll n = atoi(argv[3]);
	ll p; do p = rand()%20; while(p<3 || !MillerRabin(p));
	ll k=2, pk=p*p; do pk*=p, ++k; while(pk*p<(1LL<<31));
	fin<<p<<" "<<n<<" "<<k<<"\n";
	vector<vector<ll> > A(n,vector<ll>(n));
	do{
		for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			A[i][j] = rand()%p;
	}while( !invertible(A,p) );
	vector<ll> x(n), b(n,0LL);
	for(int i=0;i<n;++i) x[i] = rand()%pk;
	for(int i=0;i<n;++i){
		if(i) fout<<" ";
		fout<<x[i];
	}fout<<"\n";



	for(int i=0;i<n;++i)
	for(int j=0;j<n;++j)
		b[i]=(b[i]+A[i][j]*x[j]%pk)%pk;

	for(int i=0;i<n;++i){
		if(i) fin<<" ";
		fin<<b[i];
	} fin<<"\n";
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(j) fin<<" ";
			fin<<A[i][j];
		}
		fin<<"\n";
	}

	return 0;
}
