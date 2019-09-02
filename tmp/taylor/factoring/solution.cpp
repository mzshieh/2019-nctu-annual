#include<bits/stdc++.h>

using namespace std;

#define ll long long


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


int main(){
	int T; cin>>T;
	srand(time(NULL));
	while(T--){
		ll p; cin>>p;
		Poly f({0,0,1},p), upoly({1},p);
		cin>>f.a[0]>>f.a[1];
		if(p==2){
			if(f.a[0]==0 &&f.a[1]==0) puts("0 0");
			else if(f.a[0]==0 &&f.a[1]==1) puts("0 1");
			else if(f.a[0]==1 &&f.a[1]==0) puts("1 1");
			else if(f.a[0]==1 &&f.a[1]==1) puts("-1");
			continue;
		}
		Poly&& repeat = gcd(f,Poly({f.a[1],2},p));
		if(repeat.deg()>0){
			assert(repeat.deg()==1);
			ll b = inv(repeat.a[1],p)*repeat.a[0]%p;
			cout << b << " " << b << "\n";
			continue;
		}

		int flag = 0;
		for(int i=0;i<100;++i){
			Poly g({rand()%p,1},p);
			Poly&& h = pow(g,(p-1)/2,f,upoly);
			h.a[0] = (h.a[0]+1) % p;
			h = gcd(h, f);
			if(h.deg()==1){
				ll b0 = h.a[0]*inv(h.a[1],p)%p;
				ll b1 = (f.a[1]-b0+p)%p;
				if(b0>b1) swap(b0,b1);
				if(f.a[0]!=b0*b1%p || f.a[1] != (b0+b1)%p) continue;

				cout << b0 << " " << b1 <<"\n";
				flag = 1;
				break;
			}
		}
		if(!flag) puts("-1");
	}
	return 0;
}
