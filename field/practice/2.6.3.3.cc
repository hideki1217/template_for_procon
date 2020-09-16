//https://atcoder.jp/contests/abc110/tasks/abc110_d
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pint;
typedef pair<ll,ll> pll;
typedef pair<int,pint> ppint;
typedef pair<ll,pll> ppll;
typedef vector<int> vint;
typedef vector<ll> vll;

const double pi=3.141592653589793;
const int INF10 = 1000000001;
const ll INF15 = 1e15 +1;
const long long INF18 = 1e18 + 1;
const int mod = 1000000007;
//const int mod = 998244353;
const double EPS=0.00001;

#define rep(i, n) for (int i = 0; i < (ll)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (ll)(n); i++)
#define rep2(i,start,end) for(int i=(ll)start;i<=(ll)end;i++)
#define vrep(i, n) for(int i=(ll)n-1;i>=0;i--)
#define vrep1(i, n) for(int i=(ll)n;i>0;i--)
#define all(n) n.begin(),n.end()
#define pb push_back
#define debug(x) cerr << #x <<": " << x << '\n'
#define arep(it,a) for(auto it : a )

struct edge{
    edge(int s,int e,long long c){
        to=e;from=s;cost=c;
    }
    edge(int i,long long c=1){
        edge(-1,i,c);
    }
    int from;
    int to;
    long cost;
};
typedef vector<edge> edges;

//bを何回足せばaを超えるか(O(a/b))
//a+b-1/bとすればよし

//2進数表示したときの最高桁(O(log n))
int bi_max(long n){
    int m = 0;
    for (m; (1 << m) <= n; m++);
    m = m - 1;
    return m;
}
//bi_eに二進数表示したやつを代入(O(log^2 n))
//bitset<N> a(n)でnの二進数表示が得られて、a[i]=0or1でi番目のfragが立ってるかわかる
//x^n mod m (nが負の時は０)(O(log n))
long myPow(long x, long n, long m=mod){
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    if (n % 2 == 0)
        return myPow(x * x % m, n / 2, m);
    else
        return x * myPow(x, n - 1, m) % m;
}
// auto mod int
// https://youtu.be/L8grWxBlIZ4?t=9858
// https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
// https://youtu.be/8uowVvQ_-Mo?t=1329 : division
struct mint{
    ll x; // typedef long long ll;
    mint(ll x = 0) : x((x % mod + mod) % mod) {}
    mint &operator= (const mint &a) { x=a.x; return *this; }
    mint operator-() const { return mint(-x); }
    mint &operator+=(const mint a)
    {
        if ((x += a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator-=(const mint a)
    {
        if ((x += mod - a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator*=(const mint a)
    {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const { return mint(*this) += a; }
    mint operator-(const mint a) const { return mint(*this) -= a; }
    mint operator*(const mint a) const { return mint(*this) *= a; }
    mint pow(ll t) const
    {
        if (!t)
            return 1;
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1)
            a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod - 2); }
    mint &operator/=(const mint a) { return *this *= a.inv(); }
    mint operator/(const mint a) const { return mint(*this) /= a; }
    mint& operator++(int) { return *this += mint(1); }
    mint& operator--(int) { return *this -= mint(1); }
    bool operator!=(const int a) { return this->x!=a; }
    bool operator==(const int a) { return this->x==a; }
};
istream &operator>>(istream &is, const mint &a) { return is >> a.x; }
ostream &operator<<(ostream &os, const mint &a) { return os << a.x; }
// combination mod prime
// https://www.youtube.com/watch?v=8uowVvQ_-Mo&feature=youtu.be&t=1619
struct combination{
    vector<mint> fact, ifact;
    combination(int n) : fact(n + 1), ifact(n + 1)
    {
        assert(n < mod);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; --i)
            ifact[i - 1] = ifact[i] * i;
    }
    mint operator()(int n, int k)
    {
        if (k < 0 || k > n)
            return 0;
        return fact[n] * ifact[k] * ifact[n - k];
    }
    mint parm(int n,int k){
        if (k < 0 || k > n)
            return 0;
        return fact[n] * ifact[n-k];
    }
};
template<class T>
bool maxin (T &a,T b){if(a<b){a=b;return 1;}return 0;}
template<class T>
bool minin (T &a,T b){if(a>b){a=b;return 1;}return 0;}
template<class M,class N> 
common_type_t<M,N> mygcd(M a,N b){
    a=abs(a);b=abs(b);
    if(a < b) return mygcd(b, a);
    M r;
    while ((r=a%b)) {
        a = b;
        b = r;
    }
    return b;
}
template<class M,class N>
common_type_t<M,N> mylcm(M a,N b){
    return (a/mygcd(a,b))*b;
}
struct PTable{
    int n;
    vector<int> table;
    PTable(int n):n(n){
        calc();
    }
    void calc(){
        table.resize(n+1,1);
        for(int i=2;i<=n;i++){
            if(table[i]!=1)continue;
            for(int j=i;j<=n;j+=i){
                table[j]=i;
            }
        }
    }
    //aの最大の素因数を返して、aを割る
    int operator()(int &a){
        int x=table[a];
        a/=table[a];
        return x;
    }
    //素因数分解::pfact(数字,いれもの)->{{素因数,個数}}
    vector<pair<int,int>> pfact(int a,vector<pair<int,int>> b){
        int mem=0,cou=0;
        while(1){
            if(table[a]==1){
                b.push_back({mem,cou});
                break;
            }
            if(mem==table[a])cou++;
            else{
                if(cou!=0)b.push_back({mem,cou});
                mem=table[a];
                cou=1;
            }
            a/=table[a];
        }
        return b;
    }
};
const int N_MAX=110005;
int n,m;
mint ans=1;

void Main(){
    int x=0,y=INF10,z=1;
    //入力
    cin>>n>>m;
    //処理
    combination c(N_MAX);
    vector<pint> mem;
    x=sqrt(m)+1;
    rep2(i,2,x){
        if(m%i==0){
            int cou=0;
            do{
                m/=i,cou++;
            }while(m%i==0);
            mem.pb({i,cou});
        }
    }
    if(m!=1)mem.pb({m,1});
    arep(s,mem){
        debug(s.first);
        debug(s.second);
        ans*=c(s.second+n-1,n-1);
    }
    //出力
    cout << ans <<endl;
}

int main(){
    cin.tie(nullptr);
    cout<<fixed<<setprecision(12);
    Main();
}