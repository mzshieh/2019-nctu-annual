#include<bits/stdc++.h>
#include"MillerRabin.hpp"

using namespace std;

template<typename Field, typename Mod>
Field pow(Field a, ll b, Mod mod, Field const& unit){
	if(b==0) return unit;
	if(b&1) return pow(a,b-1,mod,unit)*a%mod;
	return pow(a*a%mod,b/2,mod,unit);
}

inline ll inv(ll a, ll p){ return pow(a,p-2,p,1LL);}

struct Poly{
	ll p;
	vector<ll> a;
	inline int deg()const{return a.size()-1;}
	Poly(vector<ll>const& a, ll p): a(a), p(p){assert(a.size()>0);}
	friend Poly operator%(Poly const& l, Poly const& r){
		ll p = l.p; assert(l.p==r.p);
		Poly out = l;
		while(out.deg()>=r.deg()){
			int diff = out.deg()-r.deg();
			ll c = out.a.back()*inv(r.a.back(),p)%p;
			for(int i=0;i<r.a.size();++i)
				out.a[i+diff] = (out.a[i+diff]-c*r.a[i]%p+p)%p;
			if(out.deg()>0) out.a.pop_back();
			else break;
		}
		while(out.deg()>0 && out.a.back()%p == 0) out.a.pop_back();
		return out;
	}
	friend Poly gcd(Poly const& l, Poly const& r){
		if(l.a.size()==1 && l.a[0]==0) return r;
		return gcd(r%l,l);
	}
	friend Poly operator*(Poly const& l, Poly const& r){
		ll p = l.p; assert(l.p==r.p);
		Poly out({0},p);
		out.a.resize(l.deg()+r.deg()+1);
		for(int i=0;i<=l.deg();++i)
		for(int j=0;j<=r.deg();++j)
			out.a[i+j] = (out.a[i+j]+l.a[i]*r.a[j]%p)%p;
		while(out.a.size()>1 && out.a.back()%p == 0) out.a.pop_back();
		return out;

	}
};

int isIrr(Poly const& f){
	ll p = f.p;
	Poly&& g = pow(Poly({0,1},p),p,f,Poly({1},p));
	if(g.deg()<1) g.a.resize(2);
	g.a[1] = (g.a[1]+p-1)%p;
	while(g.deg()>0 && g.a.back()%p==0) g.a.pop_back();

	return gcd(g,f).deg()==0;

}

int main(int argc, char* argv[]){
	if(argc<4) return 1;
	srand(time(NULL));
	string in = argv[1], out = argv[2];
	fstream fin(in,ios::out);
	fstream fout(out,ios::out);

	ll T = atoi(argv[3]); fin << T <<"\n";
	
	function<void()> reducible = [&](){
		ll p = rand();
		while(!MillerRabin(p) || p<100000000LL) p = rand();
		ll b0 = rand()%p, b1 = rand()%p;
		if(b0>b1) swap(b0,b1); fout<<b0<<" "<<b1<<"\n";
		ll a0 = b0*b1%p, a1 = (b0+b1)%p;
		fin<<p<<" "<<a0<<" "<<a1<<"\n";
	};
	function<void()> repeated = [&](){
		ll p = rand();
		while(!MillerRabin(p)) p = rand();
		ll b0 = rand()%p;
		fout<<b0<<" "<<b0<<"\n";
		ll a0 = b0*b0%p, a1 = (b0+b0)%p;
		fin<<p<<" "<<a0<<" "<<a1<<"\n";

	};
	function<void()> irr = [&](){
		ll p = rand(); while(!MillerRabin(p)) p = rand();
		ll a0, a1;
		do a0=rand()%p, a1=rand()%p;
		while(!isIrr(Poly({a0,a1,1},p)));
		fout<<"-1\n";
		fin<<p<<" "<<a0<<" "<<a1<<"\n";
	};

	while(T--){
		if(T%3 == 0) reducible();
		else if(T%3 == 1) irr();
		else repeated();
	}
}
